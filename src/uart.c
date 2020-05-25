/**
 * 	@file		uart.c
 *	@author		Christian Matar
 *	@brief		UART source file
 */

#include "uart.h"

void UART_init (void)
{
	// initialize pins for RX (PIO1_6) and TX (PIO1_7)
	LPC_IOCON->REG[IOCON_PIO1_6] |= 1<<1 | 1<<4;
	LPC_IOCON->REG[IOCON_PIO1_6] &= ~(1<<3);

	LPC_IOCON->REG[IOCON_PIO1_7] |= 1<<1 | 1<<4;
	LPC_IOCON->REG[IOCON_PIO1_7] &= ~(1<<3);

	// power up UART
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1<<12;
	LPC_SYSCTL->USARTCLKDIV |= 1<<0;

	// set divisors for baudrate generator
	LPC_USART->DLL = 57;
	LPC_USART->DLM = 1;

	// enable UART FIFOs
	LPC_USART->FCR |= 1<<0 | 1<<1 | 1<<2 | 1<<6;

	LPC_USART->RS485CTRL |= 1<<1 | 1<<2 | 1<<4;

	// enable data receive interrupt
	LPC_USART->IER |= 1<<0;
	NVIC_EnableIRQ (UART0_IRQn);

}

void UART_write (uint32_t *data)
{

}

uint32_t UART_read (void)
{
	return 0;
}

/**
 * 	@brief	Function UART_IRQHandler() implements the UART interrupt handler.
 */
void UART_IRQHandler()
{

}
