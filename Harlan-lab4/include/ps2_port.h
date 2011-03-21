#ifndef _PS2_PORT_H
#define _PS2_PORT_H

extern void init_ps2_port(void);

extern void ps2_enable(void);

extern void ps2_disable(void);

extern unsigned char ps2_read_char(void);

#endif