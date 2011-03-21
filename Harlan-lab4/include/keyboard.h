#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#define KEYBOARD_DISABLED 0
#define KEYBOARD_SCAN     1
#define KEYBOARD_TYPE     2

extern void init_keyboard(void);

extern void keyboard_read(int mode);

extern void keyboard_disable(void);

#endif