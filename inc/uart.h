/**
 * 	@file		uart.h
 *	@author		Christian Matar
 *	@brief		UART header file
 */

#include "board.h"

#ifndef UART_H_
#define UART_H_

/**
 * 	@brief	Function initUART() initializes the UART with a baudrate
 * 			of 9600 and starts it.
 */
void UART_init (void);

/**
 * 	@brief	Function writeUART() sends data via the UART.
 */
void UART_write (uint32_t *data);

/**
 * 	@brief	Function readUART() reads data via the UART
 * 	@return	returns the received data, or zero.
 */
uint32_t UART_read (void);


#endif /* UART_H_ */
