#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>

volatile char *GPIO_OE = (char *) 0x49056034; // GPIO_OE is a pointer to byte address 0x49056034
volatile char *GPIO_DATAIN = (char *) 0x49056038; // GPIO_DATAIN is a pointer to byte address 0x49056038
volatile char *GPIO_DATAOUT = (char *) 0x4905603c; // GPIO_DATAOUT is a pointer to byte address 0x4905603c

void init_config(void)
{
	*GPIO_OE = 0x00000001; // Configure 5th bank of GPIO as I/p
}

void main (void)
{
	init_config();

	while(1)
	{

		char b = *GPIO_OE; // Read byte from address 0x49056034
		printf("\n The value of GPIO_OE is %c", b);
		char c = *GPIO_DATAIN; // Read from GPIO pin
		
		char setLED = *GPIO_DATAOUT; // Now use setLED variable for writing 1 or 0 for LED 	
		if (c == 1)
		{
			setLED = 0; //By writing 0 to this register make LED OFF
			sleep(2);
		}

		else
		{
			setLED = 1; // By writing 1 to this register make LED ON
			sleep(2);	
		}
	}
}
/* In 'b' variable we read the value from GPIO_OE pointer
   In 'c' variable we read the value from GPIO_DATAIN pointer
   In 'setLED' variable we read the value from GPIO_DATAOUT */

  
