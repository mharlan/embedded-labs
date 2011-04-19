1. What is the full part number for each device?

SPI Memory - 25LC040A-I/P
I2C Memory - 24LC16B-I/P

2. Give me a simple schematic (ASCII art is good) showing how you connected each 
memory to the Z16. Label all pins with signal name an pin numbers.

                    24LC16B
                  ____________
  Not Connected-->|A3     Vcc|<----Vcc
  Not Connected-->|A3      WP|<----Vss
  Not Connected-->|A3     SCL|<----PA6
          Vss---->|vss    SDA|<----PA7
		  
		  
                     25LC040A
                   ____________
           PC2---->|/CS    Vcc|<----Vcc
           PC5---->|SO   /HOLD|<----Vss
           Vcc---->|/WP    SCK|<----PC3
           Vss---->|vss     SI|<----PC4
										
3. Did you have any problems finding the datasheets or getting the necessary information?

No. The memory manufacture, Microchip, has them posted on their website and on
www.datasheetcatalog.com

4. What techniques did you use to help you debug your programs?

I used the Smart Debugger in combination with print statements to the serial port.

5. Did you need any pull up resistors? Why?

No, the I2C ports on the microcontroller have their own internal pull-up resistors that are enabled
when the I2C alternate functions are set. SPI does not require pull-up resistors as used.

