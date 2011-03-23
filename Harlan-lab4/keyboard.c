
#include "keyboard.h"
#include "ps2_port.h"
#include "uart.h"
#include "speaker.h"
#include "scancodes.h"

#include <string.h>
#include <ctype.h>

#define KEY_RELEASE   0xF0
#define KEY_EXTENDED  0xE0 

#define KEY_LSHIFT    0x12
#define KEY_RSHIFT    0x59
#define KEY_ENTER     0x5A
#define KEY_CTRL      0x14
#define KEY_BACKSPACE 0x66
#define KEY_ESCAPE    0x76

static unsigned int key_map[NUM_KEYS];

static int keyboard_mode;

void init_keyboard(void)
{
	init_speaker();
	init_ps2_port();
}

void keyboard_read(int mode)
{
	unsigned char c;
	
	int release;
	int extended;

	ps2_enable();
	play_note(6, "a", 4, 100);
	
	release = 0;
	extended = 0;
	keyboard_mode = mode;
	memset(key_map, 0, NUM_KEYS);

	while(keyboard_mode) {
		while(((c = ps2_read_char()) == 0) && keyboard_mode) { ; }
		
		//scan code mode
		if(keyboard_mode == KEYBOARD_SCAN) {
			if(c == KEY_RELEASE) {
				release = 1;
			}
			else if(release) {
				key_map[c] = 0;
				release = 0;
			}
			else if(!key_map[c]) {
				key_map[c] = 1;
			}
			else {
				continue;
			}

			uart_printf("0x%.2X ", (unsigned int)c);
		}
		//typing mode
		else if(keyboard_mode == KEYBOARD_TYPE) {
			if(c == KEY_RELEASE) {
				release = 1;

				continue;
			}
			else if(c == KEY_EXTENDED) {
				extended = 1;

				continue;
			}
			//key release
			else if(release) {
				key_map[c] = 0;
				release = 0;
			}
			else {
				key_map[c] = 1;

				if(c == KEY_LSHIFT || c == KEY_RSHIFT) {
					continue;
				}
				else if(c == KEY_CTRL) {
					continue;
				}
				else if(c == KEY_ESCAPE) {
					break;
				}
				else {
					if(key_map[KEY_CTRL]) {
						uart_printf("ctl-");
					}
					
					if(key_map[KEY_LSHIFT] || key_map[KEY_RSHIFT]) {
						uart_putchar(scancode_shift_map[c]);
					}
					else {
						uart_putchar(scancode_map[c]);
					}
				}
			}
		}
	}

	keyboard_disable();
}

void keyboard_disable(void)
{
	if(keyboard_mode) {
		ps2_disable();
		play_note(6, "b", 4, 100);

		keyboard_mode = KEYBOARD_DISABLED;
		uart_putchar('\n');
	}
}
