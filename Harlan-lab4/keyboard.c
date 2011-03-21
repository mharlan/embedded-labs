
#include "keyboard.h"
#include "ps2_port.h"
#include "uart.h"
#include "speaker.h"

#include <string.h>

#define ASCII_BACKSPACE 0x08

#define NUM_KEYS   128

#define KEY_RELEASE   0xF0
#define KEY_EXTENDED  0xE0 

#define KEY_SHIFT     0x12
#define KEY_ENTER     0x5A
#define KEY_CTRL      0x14
#define KEY_BACKSPACE 0x66
#define KEY_ESCAPE    0x76

#define SHIFT_ADJ   0x20

static const char scancode_map[NUM_KEYS]= {
	'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
	'q','1','?','?','?','z','s','a','w','2','?','?','c','x','d','e','4','3','?','?',' ',
	'v','f','t','r','5','?','?','n','b','h','g','y','6','?','?','?','m','j','u','7','8',
	'?','?','?','k','i','o','0','9','?','?','?','?','l','?','p','?','?','?','?','?','?',
	'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
	'?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?','?',
	'?','?'
};

static unsigned int key_map[NUM_KEYS];

static int keyboard_mode;

void init_keyboard(void)
{
	init_ps2_port();

	memset(key_map, 0, NUM_KEYS);
}

void keyboard_read(int mode)
{
	unsigned char c;

	ps2_enable();
	play_note(4, "a", 1, 100);
	
	keyboard_mode = mode;
	while(keyboard_mode) {
		while(((c = ps2_read_char()) == 0) && keyboard_mode) { ; }
		
		//scan code mode
		if(keyboard_mode == KEYBOARD_SCAN) {
			uart_printf("0x%.2X ", (unsigned int)c);
		}
		//typing mode
		else if(keyboard_mode == KEYBOARD_TYPE) {
			if(c == KEY_RELEASE) {
				continue;
			}
			else if(c == KEY_EXTENDED) {
				continue;
			}
			//key release
			else if(key_map[c]) {
				key_map[c] = 0;
			}
			else {
				key_map[c] = 1;

				if(c == KEY_SHIFT) {
					continue;
				}
				else if(c == KEY_CTRL) {
					continue;
				}
				else if(c == KEY_BACKSPACE) {
					uart_putchar(ASCII_BACKSPACE);
				}
				else if(c == KEY_ENTER) {
					uart_putchar('\n');
				}
				else if(c == KEY_ESCAPE) {
					uart_putchar('\n');
					keyboard_mode = KEYBOARD_DISABLED;
					break;
				}
				else {
					if(key_map[KEY_CTRL]) {
						uart_printf("ctl-");
					}
					
					if(key_map[KEY_SHIFT]) {
						uart_putchar(scancode_map[c] - SHIFT_ADJ);
					}
					else {
						uart_putchar(scancode_map[c]);
					}
				}
			}
		}
	}
}

void keyboard_disable(void)
{
	ps2_disable();
	play_note(4, "b", 1, 100);

	keyboard_mode = KEYBOARD_DISABLED;
}