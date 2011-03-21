#ifndef __UART_H
#define __UART_H

#define UART_EVEN "even"
#define UART_ODD  "odd"
#define UART_NONE "none"

#define UART_BIT7 "7"
#define UART_BIT8 "8"

/*
	Configure UART0.
 */
extern void init_uart(void);

/*
	Transmit one character over the uart.

	Returns 1 if the transfer buffer is full.
 */
extern int uart_putchar(char c);

/*
	Receive a single character.
 */
extern unsigned char uart_getchar(void);

/*
	Printf over the uart.
 */
extern void uart_printf(const char *format, ...);

/*
	Transfer a msg over the uart.
 */
extern void uart_transfer_msg(char *msg);

/*
	Return the baud rate of the uart.
 */
extern unsigned long uart_get_baudrate(void);

/*
	Set the buad rate of the uart.
 */
extern void uart_set_baudrate(unsigned long baud);

/*
	Set the uart parity.
 */
extern void uart_set_parity(const char *value);

/*
	Set the uart bits.
 */
extern void uart_set_bits(const char *value);

/*
	Pass a character to uart0 receive buffer.

	This method waits until the uart is ready to receive.
 */
extern void uart_dummy_receive(char c);

/*
	Disable the UART.
 */
extern void uart_disable(void);

/*
	Enable the UART.
 */
extern void uart_enable(void);

#endif