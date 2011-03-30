
#include "24lc16b.h"
#include "i2c.h"
#include "uart.h"
#include "delay.h"

#define CLEAR_UPPER   0x0F
#define DEVICE_WRITE  0xA0
#define DEVICE_READ (DEVICE_WRITE+1)
#define BLOCK_ADDR    0x0700
#define BLOCK_SHIFT   7

void init_24lc16b(void)
{
	init_i2c();
}

void _24lc16b_write_bytes_addr(long int addr, int length)
{
	unsigned char ctrl;
	int i;

	for(i = 0; i < length; ++i) {
		ctrl = (unsigned char)((BLOCK_ADDR & addr) >> BLOCK_SHIFT);
		ctrl |= DEVICE_WRITE;

		i2c_write_bytes(3, ctrl, addr, i);
		delay_ms(5);

		++addr;
	}
}

void _24lc16b_read_bytes_hex_dump(long int addr, int length)
{
	unsigned char ctrl;
	unsigned char data;
	int i;

	for(i = 0; i < length; ++i) {
		if((i % 8) == 0) {
			uart_printf("\n%.4X - ", addr);
		}

		ctrl = (unsigned char)((BLOCK_ADDR & addr) >> BLOCK_SHIFT);
		ctrl |= DEVICE_WRITE;

		i2c_write_byte(ctrl, addr);
		delay_ms(5);

		data = i2c_read_byte(ctrl+1);
		++addr;

		uart_printf("%.2X ", data);
	}

	uart_putchar('\n');
}
