#ifndef __24LC16B_H
#define __24LC16B_H

void init_24lc16b(void);

void _24lc16b_write_bytes_addr(long int addr, int length);

void _24lc16b_read_bytes_hex_dump(long int addr, int length);

#endif