
#include "ps2_port.h"
#include "uart.h"

#include <zneo.h>

#define PS2_BUFFER_SIZE 64
#define PS2_DATA        0x01
#define PS2_CLOCK       0x02

static unsigned char ps2_data;
static unsigned char ps2_buffer[PS2_BUFFER_SIZE];

static int parity;
static int read_pos = 0;
static int write_pos = 0;
static int current_bit = 0;

void interrupt ps2_port_read(void)
{
	//make sure the clock is low
	if(!(PDIN & PS2_CLOCK)) {
		uart_printf("PS2 interrupt when clock wasn't low.\n");
		return;
	}

	//start bit
	if(!current_bit) {
		//make sure it is low
		if(!(PDIN & PS2_DATA)) { 
			++current_bit;
			ps2_data = 0x00;
			parity = 1;
		}
	}
	//data bits
	else if(current_bit < 9) {
		if(PDIN & PS2_DATA) {
			ps2_data |= 1 << (current_bit - 1);
			parity = ~parity;
		}
		++current_bit;
	}
	//parity bit
	else if(current_bit == 9) {
		if(parity != (PDIN & PS2_DATA)) {
			uart_printf("PS2 received bad data. throwing out:%c\n", ps2_data);
			ps2_data = 0x00;
		}
	}
	//stop bit
	else {
		//make sure it is high
		if(PDIN & PS2_DATA) {
			if(ps2_data) {
				ps2_buffer[write_pos] = ps2_data;
				write_pos = (write_pos + 1) % PS2_BUFFER_SIZE;
			}
		}
		else {
			uart_printf("There is something wrong with the ps2_port signals.\n");
		}
		current_bit = 0;
	}
}

void init_ps2_port(void)
{
	PDDD |= PS2_CLOCK | PS2_DATA;

	//no alternate function
	PDAFH &= ~(PS2_CLOCK | PS2_DATA);
	PDAFL &= ~(PS2_CLOCK | PS2_DATA);

	PAIMUX |= PS2_CLOCK;
	PAIEDGE &= ~PS2_CLOCK;
	
	SET_VECTOR(P1AD, ps2_port_read);			
}

void ps2_enable(void)
{
	//enable with nominal priority
	IRQ1ENH |= PS2_CLOCK;
	IRQ1ENL &= ~PS2_CLOCK;
}

void ps2_disable(void)
{
	IRQ1ENH &= ~PS2_CLOCK;
	IRQ1ENL &= ~PS2_CLOCK;
}

unsigned char ps2_read_char(void)
{
	char c;

	if(read_pos == write_pos) {
		return 0x00;
	}

	c = ps2_buffer[read_pos];
	read_pos = (read_pos + 1) % PS2_BUFFER_SIZE;

	return c;
}
