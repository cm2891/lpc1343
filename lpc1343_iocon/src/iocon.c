/**
 * 	@file       iocon.c
 * 	@brief      Source file for LPC1343 IOCON
 * 	@author     Christian Matar
 */

#include "iocon.h"

void IOCON_init ( CHIP_IOCON_PIO_T 	pin
				, uint8_t 			func
				, uint8_t 			mode
				, Bool 				hysteresis
				, Bool 				od
				)
{
	LPC_IOCON->REG[pin] |=
			(((func << IOCON_FUNC_LSB) 			|
			  (mode << IOCON_MODE_LSB) 			|
			  (hysteresis << IOCON_HYS_LSB)		|
			  (od << IOCON_OD_LSB)) & IOCON_MASK);
}
