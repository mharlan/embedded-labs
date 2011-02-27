#include "uart.h"

#include <zneo.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define BUFFER_SIZE 512

#define FREQ         5529600UL  //use internal oscillator
#define DEFAULT_BAUD 57600UL    //our desired baud rate

//alternate function enable for PA for uart0
#define PORTA_UART_RXD	0x10	
#define PORTA_UART_TXD	0x20

#define UART_TXD_EN		0x80	//transmit enable
#define UART_RXD_EN		0x40	//receive enable

#define UART_TRAN_RDY 0x04

#define UART_IRQ_EN   0x18

#define UART_IRQ_TRAN 0x08
#define UART_IRQ_REC  0x10

static unsigned char trans_buffer[BUFFER_SIZE];
static unsigned char rec_buffer[BUFFER_SIZE];

static volatile int trans_buffer_size;
static volatile int rec_buffer_size;

static volatile int trans_buffer_current;
static volatile int rec_buffer_current;

static unsigned long baud_rate;

void interrupt uart_receive(void)
{
	int buffer_loc;
	unsigned char c;

	c = U0RXD;

	//so the echo is compatible with Windows, CR+LF
	if(c == '\r' || c == '\n') {
		c = '\n';
		uart_putchar('\r');
		uart_putchar('\n');	
	}
	//echo the character back
	else {
		uart_putchar(c);
	}

	if(rec_buffer_size < BUFFER_SIZE) {
		buffer_loc = (rec_buffer_current + rec_buffer_size) % BUFFER_SIZE;
		
		rec_buffer[buffer_loc] = c;
		++rec_buffer_size;
	}
}

void interrupt uart_transfer(void)
{
	if(trans_buffer_size) {
		U0TXD = trans_buffer[trans_buffer_current];

		trans_buffer_current = (trans_buffer_current + 1) % BUFFER_SIZE;
		trans_buffer_size--;
	}
}

/*
	Configure UART0.
 */
void init_uart(void)
{
	memset(rec_buffer, 0, BUFFER_SIZE);
	memset(trans_buffer, 0, BUFFER_SIZE);

	// Set the alternate function on port A
    // Enable UART0 TxD0/RxD0 pins (bits 4 & 5)
	PAAFH &= ~(PORTA_UART_TXD | PORTA_UART_RXD);
    PAAFL |= PORTA_UART_TXD | PORTA_UART_RXD;

    // Set the baud rate
    // BRG = freq/( baud * 16)
    U0BR = FREQ/((unsigned long)DEFAULT_BAUD * 16UL);
	baud_rate = DEFAULT_BAUD;

    // U0 control
    // Transmit enable, Receive Enable, No Parity, 1 Stop
    U0CTL0 = UART_RXD_EN | UART_TXD_EN;
    U0CTL1 = 0;

	//set nominal priority
	IRQ0ENH |= UART_IRQ_EN;
	IRQ0ENL &= ~UART_IRQ_EN;

	PAIMUX &= ~UART_IRQ_EN;		//Port A (0) for interrupts
	PAIEDGE &= ~UART_IRQ_EN;	//negedge (0) interrupt

	SET_VECTOR(UART0_RX, uart_receive);
	SET_VECTOR(UART0_TX, uart_transfer);
}

int uart_putchar(unsigned char c)
{
	int buffer_loc;

	if(c == '\n') {
		while(uart_putchar('\r')) { ; }
	}

	if(trans_buffer_size < BUFFER_SIZE) {
		DI();
		
		buffer_loc = (trans_buffer_current + trans_buffer_size) % BUFFER_SIZE;
		trans_buffer[buffer_loc] = c;
		trans_buffer_size++;

		//trigger the interrupt if already ready to transmit
		if((U0STAT0 & UART_TRAN_RDY) && 
		   ((IRQ0SET & UART_IRQ_TRAN) == 0)) {
			IRQ0SET |= UART_IRQ_TRAN;
		}

		EI();
	}
	else {
		return 1;
	}

	return 0;
}

unsigned char uart_getchar(void)
{
	unsigned char c;

	if(rec_buffer_size) {
		DI();

		c = rec_buffer[rec_buffer_current];
		rec_buffer_current = (rec_buffer_current + 1) % BUFFER_SIZE;
		rec_buffer_size--;

		EI();

		return c;
	}

	return 0;
}

void uart_printf(const char *format, ...)
{
	char buffer[BUFFER_SIZE];
	va_list args;
	int i;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	uart_transfer_msg(buffer);
}

void uart_transfer_msg(char *text)
{
	int i;
	char *msg;
	
	msg = text;
	for(i = 0; *msg && i < BUFFER_SIZE; i++) {
		while(uart_putchar(*msg)) { ; }	//wait if the buffer is full
		msg++;
	}
}

unsigned long uart_get_baud_rate(void)
{
	return baud_rate;
}
