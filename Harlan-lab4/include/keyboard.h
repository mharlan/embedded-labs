#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#define KEYBOARD_DISABLED 0
#define KEYBOARD_SCAN     1
#define KEYBOARD_TYPE     2

/*
	Initialize a PS/2 keyboard device.
 */
extern void init_keyboard(void);

/*
	Begin reading from the keyboard.
 */
extern void keyboard_read(int mode);

/*
	Disable the keyboard.
 */
extern void keyboard_disable(void);

#endif