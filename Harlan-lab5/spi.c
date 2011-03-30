/* 
 * The beginings of an SPI Master library
 * February 26, 2009
 *
 * TODO:
 *  - Add error trapping
 *        data underrun, overrun, collision, slave abort
 *  - Add timeouts in the wait loops
 * 
 *  - Add SPI Slave functions
 *
 */

#include "spi.h"
#include "oscillator.h"

#include <zneo.h>
#include <stdlib.h>
 
// ESPI STATUS register definitions
#define ESPISTAT_TDRE             0x80
#define ESPISTAT_TUND             0x40
#define ESPISTAT_COL              0x20
#define ESPISTAT_ABT              0x10
#define ESPISTAT_ROVR             0x08
#define ESPISTAT_RDRF             0x04
#define ESPISTAT_TFST             0x02
#define ESPISTAT_SLAS             0x01

// ESPI CONTROL register definitions
#define ESPICTL_DIRQE             0x80
#define ESPICTL_ESPIEN_BLOCK      0x00
#define ESPICTL_ESPIEN_RECEIVE    0x01
#define ESPICTL_ESPIEN_TRANSMIT   0x40
#define ESPICTL_BRGCTK            0x20
#define ESPICTL_PHASE_1           0x10
#define ESPICTL_PHASE_0           0x00
#define ESPICTL_CLKPOL_1          0x08
#define ESPICTL_CLKPOL_0          0x00
#define ESPICTL_WOR               0x04
#define ESPICTL_MMEN              0x02

// ESPI MODE register definitions
#define ESPIMODE_SSMD_SPI         0x00
#define ESPIMODE_SSMD_LOOPBACK    0x20
#define ESPIMODE_SSMD_I2S         0x40
#define ESPIMODE_NUMBITS_8        0x00
#define ESPIMODE_NUMBITS_1        0x04
#define ESPIMODE_NUMBITS_2        0x08
#define ESPIMODE_NUMBITS_3        0x0C
#define ESPIMODE_NUMBITS_4        0x10
#define ESPIMODE_NUMBITS_5        0x14
#define ESPIMODE_NUMBITS_6        0x18
#define ESPIMODE_NUMBITS_7        0x1C
#define ESPIMODE_SSIO_INPUT       0x00
#define ESPIMODE_SSIO_OUTPUT      0x02
#define ESPIMODE_SSPO_LOW         0x00
#define ESPIMODE_SSPO_HIGH        0x01

void init_spi() 
{
    PCAF |= 0x3C;                 // Set AltFun bits 00111100 = 3C 
                                  // for MISO, MOSI, SS, SCLK

    ESPICTL = ESPICTL_ESPIEN_TRANSMIT + ESPICTL_ESPIEN_RECEIVE +
              ESPICTL_PHASE_0 + ESPICTL_CLKPOL_0 + ESPICTL_MMEN;  
        
    ESPIMODE = ESPIMODE_SSPO_LOW + ESPIMODE_SSIO_OUTPUT;   
       
    // Set the SPI baud rate slow so we can see it easily on an oscope
    // approx 1Kbit
    ESPIBR = get_osc_clock() / (2 * 1000);        
}

void spi_wait_TDRE(void) 
{
    while(!(ESPISTAT & ESPISTAT_TDRE));
}


void spi_wait_RDRF(void) 
{
    while(!(ESPISTAT & ESPISTAT_RDRF));
}

void spi_wait_TFST(void) 
{
    while(ESPISTAT & ESPISTAT_TFST);
}

void spi_enable(void)
{
	ESPITDCR |= 0x01;             // Set SS
}

void spi_disable(void)
{
	ESPITDCR &= 0xFE;             // Clear SS to stop communication
}

void spi_transfer(unsigned char byte)
{
	unsigned char dummy;

	ESPIDATA = byte;              // Control message

    spi_wait_TDRE();              // Wait for transmission to complete
    spi_wait_RDRF();              // Wait for recived byte to complete
  
    dummy = ESPIDATA;              
	spi_wait_TFST();              // Wait for SPI transfer to complete
}

void spi_write(unsigned char addr, unsigned char data) 
{
    spi_transfer(addr);
	spi_transfer(data);
}

unsigned char spi_read(unsigned char addr) 
{
	unsigned char data;

	spi_transfer(addr);

    ESPIDATA = 0x00;              // Send dummy byte (8 bits sends 8 clocks
                                  // so that we get 8 bits from the device. 

    spi_wait_RDRF();              // Wait for receive to complete
    data = ESPIDATA;              // Get received byte. This one we want.
    spi_wait_TFST();              // Wait for transfer to complete

    ESPITDCR &= 0xFE;             // Clear SS 

    return data;
}
