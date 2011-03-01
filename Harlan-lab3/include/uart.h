#ifndef UART_H
#define UART_H

/*
	Configure UART0.
 */
void init_uart(void);

/*
	Transmit one character over the uart.

	Returns 1 if the transfer buffer is full.
 */
int uart_putchar(char c);

/*
	Receive a single character.
 */
unsigned char uart_getchar(void);

/*
	Printf over the uart.
 */
void uart_printf(const char *format, ...);

/*
	Transfer a msg over the uart.
 */
void uart_transfer_msg(char *msg);

/*
	Return the baud rate of the uart.
 */
unsigned long uart_get_baud_rate(void);

/*
	Pass a character to uart0 receive buffer.

	This method waits until the uart is ready to receive.
 */
void uart_dummy_receive(char c);

#endif