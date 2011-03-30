#ifndef __SPI_H
#define __SPI_H

void init_spi();

void spi_enable(void);

void spi_disable(void);

void spi_transfer(unsigned char byte);

void spi_write(unsigned char addr, unsigned char data);

unsigned char spi_read(unsigned char addr);

#endif