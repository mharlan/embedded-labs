#ifndef __25LC040A_H
#define __25LC040A_H

void init_25lc040a(void);

void _25lc040a_write_bytes_addr(long int addr, int length);

void _25lc040a_read_bytes_hex_dump(long int addr, int length);

#endif