
#include "spi.h"
#include "uart.h"
#include "delay.h"

#include <zneo.h>

#define READ  0x03
#define WRITE 0x02
#define WRDI  0x04
#define WREN  0x06
#define RDSR  0x05
#define WRSR  0x01

#define ADDR_MSB 0x0100

void init_25lc040a(void)
{
	init_spi();
}

void _25lc040a_write_bytes_addr(long int addr, int length)
{
	unsigned char ctrl;
	int i;
	
	for(i = 0; i < length; ++i) {
		spi_enable();
		spi_transfer(WREN);
		spi_disable();

		ctrl = (addr & ADDR_MSB) >> 5;
		ctrl |= WRITE;

		uart_printf("---ctrl:0x%.2X\n", ctrl);

		spi_enable();
		spi_transfer(ctrl);
		spi_write((unsigned char)addr, (unsigned char)i);
		spi_disable();

		delay_ms(5);

		++addr;
	}
}

void _25lc040a_read_bytes_hex_dump(long int addr, int length)
{
	unsigned char ctrl;
	unsigned char data;
	int i;
	
	for(i = 0; i < length; ++i) {
		if((i % 8) == 0) {
			uart_printf("\n%.4X - ", addr);
		}

		ctrl = (addr & ADDR_MSB) >> 5;
		ctrl |= READ;

		spi_enable();
		spi_transfer(ctrl);
		data = spi_read((unsigned char)addr);
		spi_disable();

		++addr;

		uart_printf("%.2X ", data);
	}

	uart_putchar('\n');
}
