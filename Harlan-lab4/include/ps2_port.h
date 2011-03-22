#ifndef __PS2_PORT_H
#define __PS2_PORT_H

/*
	Initialize the PS/2 port driver.
 */
extern void init_ps2_port(void);

/*
	Enable PS/2 interrupts.
 */
extern void ps2_enable(void);

/*
	Disable PS/2 interrupts.
 */
extern void ps2_disable(void);

/*
	Read a byte from the ps2 buffer. Returns 0 if empty.
 */
extern unsigned char ps2_read_char(void);

#endif