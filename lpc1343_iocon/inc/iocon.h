/**
 * 	@file       iocon.h
 * 	@brief      Header file for LPC1343 IOCON
 * 	@author     Christian Matar
 */

#ifndef INC_IOCON_H_
#define INC_IOCON_H_

#include "board.h"

/** LSB of bitfield FUNC [2:0] */
#define IOCON_FUNC_LSB		(0U)
/** LSB of bitfield MODE [4:3] */
#define IOCON_MODE_LSB		(3U)
/** LSB of bit HYS [5:5] */
#define IOCON_HYS_LSB		(5U)
/** LSB for bit OD [10:10] */
#define IOCON_OD_LSB		(10U)
/** Bitmask for IOCON register. The layout is as follows:
 * 		[2:0]		FUNC
 * 		[4:3]		MODE
 * 		[5:5]		HYS
 * 		[9:6]		RESERVED
 * 		[10:10]		OD
 * 		[31:11]		RESERVED
 */
#define IOCON_MASK			((uint32_t)0x0000043F)

/** @brief Function IOCON_init configures a GPIO pin to the needed functionality.
 *  @param pin The GPIO pin, which shall be configured.
 *  @param func The functionality the GPIO pin shall execute.
 *	@param mode The mode the pin shall be set to.
 *	@param hysteresis Defines if hysteresis shall be used or not.
 *	@param od Defines if the pin shall have a GPIO or open-drain output.
 */
void IOCON_init ( CHIP_IOCON_PIO_T 	pin
				, uint8_t 			func
				, uint8_t 			mode
				, Bool 				hysteresis
				, Bool 				od
				);

#endif /* INC_IOCON_H_ */
