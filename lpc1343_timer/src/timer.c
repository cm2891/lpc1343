/**
 * 	@file       timer.c
 * 	@brief      16-bit/32-bit timer source file
 * 	@author     Christian Matar
 */

#include "timer.h"

Bool TIMER_init ( LPC_TIMER_T	*timer
				, uint32_t 		prescaler_val
				, uint32_t 		mcr_val
				, uint32_t 		*match_vals
				, uint32_t 		irq_prio
				, uint32_t 		ctcr_val
				, uint32_t 		pwmc_val
				)
{
	if(!timer || !match_vals)
		/* Invalid handles provided --> report error. */
		return FALSE;

	uint8_t 			enable_bit;
	LPC1343_IRQn_Type 	irq;
	uint8_t 			i;

	if (timer == LPC_TIMER16_0)
	{
		enable_bit 	= SYSCTL_CLOCK_CT16B0;
		irq 		= TIMER_16_0_IRQn;
	}
	else if (timer == LPC_TIMER16_1)
	{
		enable_bit 	= SYSCTL_CLOCK_CT16B1;
		irq 		= TIMER_16_1_IRQn;
	}
	else if (timer == LPC_TIMER32_0)
	{
		enable_bit 	= SYSCTL_CLOCK_CT32B0;
		irq 		= TIMER_32_0_IRQn;
	}
	else if (timer == LPC_TIMER32_1)
	{
		enable_bit 	= SYSCTL_CLOCK_CT32B1;
		irq 		= TIMER_32_1_IRQn;
	}
	else
	{
		/* The provided timer handle is none of the LPC timers --> report an error. */
		return FALSE;
	}

	/* Enable clock for timer. */
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << enable_bit;

	/* reset timer and release reset immediately */
	timer->TCR |= 1<<1;
	timer->TCR &= ~(1<<1);

	/* set prescaler value */
	timer->PR = prescaler_val;

	/* Set MR0, MR1, MR2 and MR3 */
	for (i = 0U; i < 4U; i++)
		timer->MR[i] = match_vals[i];

	/* Configure the match control register, which determines the the timer reaction,
	 * when the timer value matches the respective match register value.
	 * Possible reactions are:
	 * 		1. Generate an interrupt.
	 * 		2. Reset the TC and PC values.
	 * 		3. Stop the timer.
	 */
	timer->MCR = (mcr_val & TIMER_MCR_MASK);

	/* Set timer mode */
	timer->CTCR = (ctcr_val & TIMER_CTCR_MASK);

	/* Configure MR0 to be a PWM output. */
	timer->PWMC = (pwmc_val & TIMER_PWMC_MASK);

	/* Connect interrupts, if any are configured. */
	if (mcr_val & TIMER_MCR_IRQ_MASK)
	{
		NVIC_EnableIRQ (irq);
		NVIC_SetPriority (irq, irq_prio);
	}

	return TRUE;
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
