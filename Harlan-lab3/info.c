#include "info.h"
#include "uart.h"

#include <zneo.h>
#include <string.h>

#define FLASH_INFO_EN  0x80

#define PART_NUM_START 0x000040
#define PART_NUM_SIZE  20

const unsigned char part_num[PART_NUM_SIZE] _At PART_NUM_START;

/*
	Get access to the information section of the flash memory.
 */
void init_info(void)
{
	FCTL |= FLASH_INFO_EN;
}

/*
 	Displays various system information.
 */
void info_display(void)
{
	uart_printf("Uart0 Baud Rate: %u\n", uart_get_baud_rate());
	uart_printf("Part Number: %s\n", part_num);
	uart_printf("Compile Date: %s\nCompile Time: %s\n", __DATE__, __TIME__);
}

