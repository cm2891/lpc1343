/**
 * 	@file 		timer.h
 * 	@brief		16-bit/32-bit timer header file
 * 	@author		Christian Matar
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "gpio.h"
#include "board.h"

/** LPC_TIMER32_0 interrupt priority value. The lower the value, the more important the IRQ. */
#define TIMER32_0_IRQ_PRIO					((uint32_t)10)
/** LPC_TIMER32_1 interrupt priority value. The lower the value, the more important the IRQ. */
#define TIMER32_1_IRQ_PRIO					((uint32_t)11)
/** LPC_TIMER16_0 interrupt priority value. The lower the value, the more important the IRQ. */
#define TIMER16_0_IRQ_PRIO					((uint32_t)12)
/** LPC_TIMER16_1 interrupt priority value. The lower the value, the more important the IRQ. */
#define TIMER16_1_IRQ_PRIO					((uint32_t)13)

/**
 * Formula for calculating the corresponding prescaler value for a desired timer resolution:
 * PR = Tres * fper - 1
 * with fper = 72 MHz and Tres = 125 ns
 * PR = 125 * 10^-9 * 72 * 10^6 - 1 = 8
 *
 * The PWM signal will be LOW at the start of a PWM period and HIGH once it reaches the
 * duty cycle, defined by MR0 - MR2, until the end of the period.
 */
/** Sets the the resolution of the timer to 125 ns. */
#define TIMER_PRESCALER						((uint32_t)8)
/** We want a period of 20 µs = 50 kHz for every PWM. */
#define TIMER_MATCH_3_VAL					((uint32_t)160)
/** We want a duty cycle of 25% for LPC_TIMER32_0. */
#define TIMER32_0_MR0						((uint32_t)120)
/** We use MR1 of LPC_TIMER32_0 to start LPC_TIMER16_0 with a delay of 4 us. */
#define TIMER32_0_MR1						((uint32_t)32)
/** We use MR2 of LPC_TIMER32_0 to start LPC_TIMER32_1 with a delay of 9 us.*/
#define TIMER32_0_MR2						((uint32_t)72)
/** We want a duty cycle of 30% for LPC_TIMER32_1. */
#define TIMER32_1_MR0						((uint32_t)112)
/** We use MR1 of LPC_TIMER32_1 to start LPC_TIMER16_1 with a delay of 14 us.
 *  Since LPC_TIMER32_1 is already started with a delay of 9 us,
 *  we add an additional delay of 5 us.
 */
#define TIMER32_1_MR1						((uint32_t)40)
/** We want a duty cycle of 35% for LPC_TIMER16_0. */
#define TIMER16_0_MR0						((uint32_t)104)
/** We want a duty cycle of 30% for LPC_TIMER16_1. */
#define TIMER16_1_MR0						((uint32_t)112)
/** In case an MR is not used, we set its value to zero. */
#define TIMER_MR_NOT_USED					((uint32_t)0)

/** Mask for MCR */
#define TIMER_MCR_MASK						((uint32_t)0x00000FFF)
/** Mask for CTCR */
#define TIMER_CTCR_MASK						((uint32_t)0x0000000F)
/** Mask for PWMC */
#define TIMER_PWMC_MASK						((uint32_t)0x0000000F)
/** Mask to check if interrupts are enabled. */
#define TIMER_MCR_IRQ_MASK					((uint32_t)0x00000249)

/**
 * 	@brief	Function TIMER_init() initializes a 16-bit/32-bit PWM.
 * 	@param	timer indicates, which timer will be initialized.
 * 	@param	prescaler_val defines the prescaler value.
 * 	@param  mcr_val value to which the MCR register shall be set to.
 * 	@param	match_vals determines the values for the match registers 1, 2 and 3.
 * 	@param	irq_prio determines the interrupt priority.
 * 			If no IRQ via mcr_val is selected, this is ignored.
 * 	@param  ctcr_val determines the timer mode and the count input select.
 * 	@param  pwmc_val determines, which match register shall be used as PWM output.
 * 	@return Bool
 * 	@retval TRUE configuration success
 * 	@retval FALSE invalid parameter(s) provided
 */
Bool TIMER_init ( LPC_TIMER_T	*timer
				, uint32_t		prescaler_val
				, uint32_t		mcr_val
				, uint32_t		*match_vals
				, uint32_t		irq_prio
				, uint32_t		ctcr_val
				, uint32_t		pwmc_val
				);

/**
 * 	@brief	Function TIMER_start() starts 16-bit/32-bit PWM.
 * 	@param	timer indicates, which timer's PWM will be initialized.
 */
void TIMER_start (LPC_TIMER_T *timer);

/**
 * 	@brief	Function TIMER_stop() stops a 16-bit/32-bit PWM.
 * 	@param	timer indicates, which timer's PWM will be initialized.
 */
void TIMER_stop (LPC_TIMER_T *timer);

/**
 * 	@brief	Function TIMER_startAll() starts all four PWMs.
 */
void TIMER_startAll ();

/**
 * 	@brief	Function TIMER_stopAll() stops all four PWMs.
 */
void TIMER_stopAll ();

/**
 * 	@brief	Function TIMER_setDutyCycle() changes a timer's duty cycle.
 * 	@param	timer indicates, which timer's PWM will be initialized.
 * 	@param	match_reg determines the match register to be updated.
 * 			Supported values are: 0, 1 and 2.
 * 	@param	duty_cycle sets the PWM's duty cycle.
 * 			The value has to be a percentage value.
 */
void TIMER_setDutyCycle (LPC_TIMER_T *timer, uint8_t match_reg, double duty_cycle);


#endif /* TIMER_H_ */
