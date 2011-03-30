#ifndef __I2C_H
#define __I2C_H

void init_i2c();

void i2c_wait_TDRE();

void i2c_wait_RDRF();

void i2c_clear();

void i2c_write_bytes(int n, ... );

void i2c_write_byte(unsigned char addr, unsigned char data);

void i2c_write_byte_no_stop(unsigned char addr, unsigned char data);

unsigned char i2c_read_byte(unsigned char addr);

#endif