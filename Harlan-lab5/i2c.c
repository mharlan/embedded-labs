
#include "i2c.h"
#include "uart.h"

#include <zneo.h>
#include <stdlib.h>
#include <stdarg.h>

#define I2C_RETRY                   32      // Retry attempts when failing to receive ACK
#define I2C_TIMEOUT                 4024    // Timeout value for waiting for receive/transmit complete

// Defines for I2CCTL
#define	I2CCTL_ENABLE             0x80    
#define I2CCTL_DISABLE            0x00
#define I2CCTL_START              0x40   
#define I2CCTL_STOP               0x20    
#define I2CCTL_BIRQ               0x10    
#define I2CCTL_TXI                0x08   
#define I2CCTL_NACK               0x04   
#define I2CCTL_FLUSH              0x02   
#define I2CCTL_FILTER_ENABLE      0x01   

// Defines for I2CISTAT
#define TRANSMIT_DATA_REG_EMPTY   0x80    
#define	RECEIVE_DATA_REG_FULL     0x40    
#define	RECEIVED_SAM              0x20    
#define RECEIVED_10BIT_ADDR       0x10    
#define I2C_RECEIVING             0x08    
#define I2C_ARBITRATION           0x04   
#define I2C_SPRS                  0x02    
#define	RECEIVED_NACK             0x01  
#define I2C_ACK                   0x40  


void init_i2c()
{

    // Set baud rate
    // BRG = systemclock/(4 * baudrate)
    I2CBR = 0x04;                      // about 100k @ 5.5296 MHz
    PAAFL |= 0xC0;                     // Enable I2C alternate function
    I2CMODE = 0x00;                    // polling, 7bit, auto ack
                                       // no GCE, no slave addr
                                       // no diags
    I2CCTL = I2CCTL_ENABLE;            // Enable Rx/Tx; 

}

/*
 * Wait for transmission to complete
 */ 
void i2c_wait_TDRE() 
{
    int timeout = 0;

    while((I2CISTAT & TRANSMIT_DATA_REG_EMPTY) == 0x00) {
        //if(++timeout == TIMEOUT)
        //break;
        ;
    }
}

/* 
 * Wait for data to arrive.
 */
void i2c_wait_RDRF() 
{
    int timeout = 0;

    while((I2CISTAT & RECEIVE_DATA_REG_FULL) == 0x00) {
        //if(++timeout == TIMEOUT)
        //break;
        ;
    }
}

/*
 * Flush the buffer and toggle the I2C on and off.
 */
void i2c_clear() 
{
    I2CCTL |= I2CCTL_FLUSH;
    I2CCTL &= ~I2CCTL_ENABLE;
    I2CCTL |= I2CCTL_ENABLE;
}

/*
 * Write 1 byte to device.
 */
void i2c_write_byte(unsigned char addr, unsigned char data) 
{ 
    i2c_wait_TDRE();              // wait for any previous
                                  // writes to complete
    I2CDATA = addr;
    I2CCTL |= I2CCTL_START;
    i2c_wait_TDRE();

    I2CDATA = data;
    i2c_wait_TDRE();

    I2CCTL |= I2CCTL_STOP;

}

/*
 * Write 1 byte to device.
 */
void i2c_write_byte_no_stop(unsigned char addr, unsigned char data) 
{ 
    i2c_wait_TDRE();              // wait for any previous
                                  // writes to complete
    I2CDATA = addr;
    I2CCTL |= I2CCTL_START;
    i2c_wait_TDRE();

    I2CDATA = data;
    i2c_wait_TDRE();
}

/*
 * Read a byte from a device
 */ 
unsigned char i2c_read_byte(unsigned char addr) 
{ 
    unsigned char data=0;

    i2c_wait_TDRE();              // wait for any previous
                                  // writes to complete
    I2CDATA = addr;
    I2CCTL |= I2CCTL_START;
	I2CCTL |= I2CCTL_NACK;
    i2c_wait_RDRF();
            
    data = I2CDATA;
    I2CCTL |= I2CCTL_STOP;

    return data;
}

/* 
 * Send a sequence of I2C bytes 
 * with the first byte, set the START condition 
 * and with the last byte set the STOP condition
 */
void i2c_write_bytes(int n, ... ) 
{ 
    va_list ap;
    int i=0;
    int data=0;

    va_start(ap, n);                // prepare vararg list

    i2c_wait_TDRE();                // wait for any previous transaction

    for (i = 0; i < n; i++) {

        data = va_arg(ap, int);     // get vararg n
        I2CDATA = data;             // send it

        if (i==0)                   // first byte? set STOP condition
            I2CCTL |= I2CCTL_START;

        i2c_wait_TDRE();            // wait for byte to go

        if (i==(n-1))               // last byte? set STOP condition
            I2CCTL |= I2CCTL_STOP;

    }
    va_end(ap);   
}
