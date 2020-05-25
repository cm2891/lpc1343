/**
 * 	@file       timer.c
 * 	@brief      16-bit/32-bit timer source file
 * 	@author     Christian Matar
 */

#include <timer.h>

void TIMER_init (LPC_TIMER_T *timer, uint32_t prescaler_val, uint32_t *match_vals)
{
	if(!timer || !match_vals)
		return;

	uint8_t 			enable_bit;
	CHIP_IOCON_PIO_T 	iocon;
	LPC_GPIO_T 			*gpio = LPC_GPIO1;
	uint8_t 			pin;
	LPC1343_IRQn_Type 	irq;
	uint8_t 			func = IOCON_FUNC2;
	uint8_t 			i;
	/* Reset TC and PC once TC matches MR3. */
	uint32_t			MCR_val = (1<<10);
	uint32_t 			irq_prio;

	if (timer == LPC_TIMER16_0)
	{
		enable_bit 	= SYSCTL_CLOCK_CT16B0;
		iocon 		= IOCON_PIO0_8;
		gpio 		= LPC_GPIO0;
		pin 		= 8U;
		irq 		= TIMER_16_0_IRQn;
		irq_prio	= TIMER16_0_IRQ_PRIO;
	}
	else if (timer == LPC_TIMER16_1)
	{
		enable_bit 	= SYSCTL_CLOCK_CT16B1;
		iocon 		= IOCON_PIO1_9;
		pin 		= 9U;
		irq 		= TIMER_16_1_IRQn;
		func 		= IOCON_FUNC1;
		irq_prio	= TIMER16_1_IRQ_PRIO;
	}
	else if (timer == LPC_TIMER32_0)
	{
		enable_bit 	= SYSCTL_CLOCK_CT32B0;
		iocon 		= IOCON_PIO1_6;
		pin 		= 6U;
		irq 		= TIMER_32_0_IRQn;
		irq_prio	= TIMER32_0_IRQ_PRIO;
		/* Enable interrupt generation for MR1 and MR2. */
		MCR_val 	|= (1<<3 | 1<<6);
	}
	else if (timer == LPC_TIMER32_1)
	{
		enable_bit 	= SYSCTL_CLOCK_CT32B1;
		iocon 		= IOCON_PIO1_1;
		pin 		= 1U;
		irq 		= TIMER_32_1_IRQn;
		irq_prio	= TIMER32_1_IRQ_PRIO;
		func 		= IOCON_FUNC3;
		/* Enable interrupt generation for MR1. */
		MCR_val 	|= (1<<3);
	}
	else
	{
		return;
	}

	/* Enable clock for timer. */
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << enable_bit;

	/* Set GPIO function to PWM output and enable pull-up resistor. */
	LPC_IOCON->REG[iocon] = (func) | (IOCON_MODE_PULLUP);
	GPIO_SetDirection (gpio, pin, GPIO_DIR_OUTPUT);

	/* reset timer and release reset immediately */
	timer->TCR |= 1<<1;
	timer->TCR &= ~(1<<1);

	/* set prescaler value */
	timer->PR = prescaler_val;

	/* Set MR0, MR1, MR2 and MR3 */
	for ( i = 0U; i < 4U; i++ )
		timer->MR[i] = match_vals[i];

	/* Reset timer counter, when value of MR3 is matched.
	 * For TIMER32_0 enable MR1 and MR2 interrupt generation too,
	 * to start TIMER16_0 and TIMER32_0.
	 * For TIMER32_1 enable MR1 interrupt generation too,
	 * to start TIMER16_1.
	 * This interrupt controlled start of timers ensures the wished delays between them. */
	timer->MCR |= MCR_val;

	/* Set timer mode */
	timer->CTCR &= 0x0;

	/* Configure MR0 to be a PWM output. */
	timer->PWMC |= 1<<0;

	/* connect interrupts */
	NVIC_EnableIRQ (irq);
	NVIC_SetPriority (irq, irq_prio);
}

void TIMER_start (LPC_TIMER_T *timer)
{
	if(!timer)
		return;

	timer->TCR |= 1<<0;
}

void TIMER_stop (LPC_TIMER_T *timer)
{
	if (!timer)
		return;

	timer->TCR &= ~(1<<0);
}

void TIMER_startAll ()
{
	TIMER_start (LPC_TIMER16_0);
	TIMER_start (LPC_TIMER16_1);
	TIMER_start (LPC_TIMER32_0);
	TIMER_start (LPC_TIMER32_1);
}

void TIMER_stopAll ()
{
	TIMER_stop (LPC_TIMER16_0);
	TIMER_stop (LPC_TIMER16_1);
	TIMER_stop (LPC_TIMER32_0);
	TIMER_stop (LPC_TIMER32_1);
}

void TIMER_setDutyCycle (LPC_TIMER_T *timer, uint8_t match_reg, double duty_cycle)
{
	if (!timer || match_reg >= 3U)
		return;

	double percentage = (double) duty_cycle / 100;
	percentage = 1 - percentage;

	timer->MR[match_reg] = (uint32_t) timer->MR[3] * percentage;
}

/**
 * 	@brief	Function TIMER16_0_IRQHandler() implements
 * 			the interrupt handler for LPC_TIMER16_0.
 */
void TIMER16_0_IRQHandler ()
{
	NVIC_ClearPendingIRQ (TIMER_16_0_IRQn);
	/* Reset interrupt flags for MR3. */
	LPC_TIMER16_0->IR |= 1<<3;
}

/**
 * 	@brief	Function TIMER16_1_IRQHandler() implements
 * 			the interrupt handler for LPC_TIMER16_1.
 */
void TIMER16_1_IRQHandler ()
{
	NVIC_ClearPendingIRQ (TIMER_16_1_IRQn);
	/* Reset interrupt flags for MR3. */
	LPC_TIMER16_1->IR |= 1<<3;
}

/**
 * 	@brief	Function TIMER32_0_IRQHandler() implements
 * 			the interrupt handler for LPC_TIMER32_0.
 */
void TIMER32_0_IRQHandler ()
{
	/* Check interrupt source */
	if ( (LPC_TIMER32_0->IR & (1<<1)) == (1<<1) )
	{
		/* Start PWM for switch 4 */
		TIMER_start (LPC_TIMER16_1);
		/* Disable interrupt generation for MR1. */
		LPC_TIMER32_0->MCR &= ~(1<<3);
		/* Reset MR1 to zero. It is not needed anymore. */
		LPC_TIMER32_0->MR[1] = 0U;
		/* Clear interrupt flag for MR1 */
		LPC_TIMER32_0->IR |= (1<<1);
	}
	else if ( (LPC_TIMER32_0->IR & (1<<2)) == (1<<2) )
	{
		/* Start PWM for switch 2 */
		TIMER_start (LPC_TIMER32_1);
		/* Disable interrupt generation for MR2. */
		LPC_TIMER32_0->MCR &= ~(1<<6);
		/* Reset MR2 to zero. It is not needed anymore. */
		LPC_TIMER32_0->MR[2] = 0U;
		/* Clear interrupt flag for MR2 */
		LPC_TIMER32_0->IR |= (1<<2);
	}
	if ( (LPC_TIMER32_0->IR & (1<<3)) == (1<<3))
	{
		/* Clear interrupt flag for MR3 */
		LPC_TIMER32_0->IR |= (1<<3);
	}

	NVIC_ClearPendingIRQ (TIMER_32_0_IRQn);
}

/**
 * 	@brief	Function TIMER32_1_IRQHandler() implements
 * 			the interrupt handler for LPC_TIMER32_1.
 */
void TIMER32_1_IRQHandler ()
{
	if ((LPC_TIMER32_1->IR & (1<<1)) == (1<<1))
	{
		/* Start PWM for switch 3 */
		TIMER_start (LPC_TIMER16_0);
		/* Disable interrupt generation for MR1. */
		LPC_TIMER32_1->MCR &= ~(1<<3);
		/* Reset MR1 to zero. It is not needed anymore. */
		LPC_TIMER32_1->MR[1] = 0U;
		/* Clear interrupt flag for MR1 */
		LPC_TIMER32_1->IR |= (1<<1);
	}
	if ((LPC_TIMER32_1->IR & (1<<3)) == (1<<3))
	{
		/* Clear interrupt flag for MR3 */
		LPC_TIMER32_1->IR |= (1<<3);
	}

	NVIC_ClearPendingIRQ (TIMER_32_1_IRQn);
}
