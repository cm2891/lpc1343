/**
 * 	@file       ACSWITCH.c
 * 	@brief      Holds the main function
 * 	@author     Christian Matar
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "gpio.h"
#include "timer.h"

void initAll();

int main(void)
{

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
#endif

    /* Enable clock for GPIO (bit 6) and IOCON (bit 16). */
    LPC_SYSCTL->SYSAHBCLKCTRL |= (1 << 6) | (1 << 16);

    /* Initialize the timers */
	initAll();

	/* Start only LPC_TIMER32_0. The other timers will be started by interrupts
	 * of LPC_TIMER32_0 and LPC_TIMER32_1 in order to guarantee a certain delay
	 * between them.
	 */
	TIMER_start (LPC_TIMER32_0);

	while(1)
	{
		/* Loop forever */
	}
    return 0 ;
}

void initAll()
{
	/* The following arrays contain the values for each MR of the respective timer.
	 * See the definitions of the single MR values for further information. */
	uint32_t t32_0_vals[4U] = { TIMER32_0_MR0, TIMER32_0_MR1, TIMER32_0_MR2, TIMER_MATCH_3_VAL };
	uint32_t t32_1_vals[4U] = { TIMER32_1_MR0, TIMER32_1_MR1, TIMER_MR_NOT_USED, TIMER_MATCH_3_VAL };
	uint32_t t16_0_vals[4U] = { TIMER16_0_MR0, TIMER_MR_NOT_USED, TIMER_MR_NOT_USED, TIMER_MATCH_3_VAL };
	uint32_t t16_1_vals[4U] = { TIMER16_1_MR0, TIMER_MR_NOT_USED, TIMER_MR_NOT_USED, TIMER_MATCH_3_VAL };

	TIMER_init (LPC_TIMER16_0, TIMER_PRESCALER, t16_0_vals);
	TIMER_init (LPC_TIMER16_1, TIMER_PRESCALER, t16_1_vals);
	TIMER_init (LPC_TIMER32_0, TIMER_PRESCALER, t32_0_vals);
	TIMER_init (LPC_TIMER32_1, TIMER_PRESCALER, t32_1_vals);
}
