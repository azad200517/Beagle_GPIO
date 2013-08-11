#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

Setting the pin configuration:

//O_SYNC makes the memory uncacheable

int fd = open("/dev/mem", O_RDWR | O_SYNC);
if (fd < 0) 
{
	sprintf(stderr,"Could not open memory\n");
	return 0;
}

// Pad configuration
volatile ulong *pinconf;

pinconf = (ulong*) mmap(NULL, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x48000000);
if (pinconf == MAP_FAILED) 
{
	sprintf(stderr,"Pinconf Mapping failed\n");
	close(fd);
	return 0;
}
// set lower 16 pins to GPIO bank5
pinconf[0x2158/4] = 0x00040004;
pinconf[0x215C/4] = 0x00040004;
pinconf[0x2160/4] = 0x00040004;
pinconf[0x2164/4] = 0x00040004;
/* pinconf[0x2168/4] = 0x00040004; */
/* pinconf[0x216C/4] = 0x00040004; */
/* pinconf[0x2170/4] = 0x00040004; */
/* pinconf[0x2188/4] = 0x00040004; */
close(fd);


GPIO Bank 5 configuration:

volatile ulong * gpio_fd = open("/dev/mem", O_RDWR | O_SYNC);
if (gpio_fd < 0) 
{
	sprintf(stderr,"Could not open memory\n");
	return 0;
}
// First set all output on bank5 to high
// (set_data_out has offset 0x94)
gpio[0x6094/4]=0xFFFFFFFF;

// Configure low 16 GPIO pins on bank 5 as output.
// GPIO 5 is at physical address 0x49056000 = 0x49050000+0x6000
// GPIO Output enable (GPIO_OE) is offset by 0x34 for each bank
// (set low for output)
gpio[0x6034/4] = 0x00000000;
// Also disable the wakeupenable and irqenable intertupts
// GPIO clear_Wakeupenable is offset by 0x80 for each bank
gpio[0x6080/4] = 0x0000FFFF;
// GPIO clear_irqenable1 is offset by 0x60 for each bank
gpio[0x6060/4] = 0x0000FFFF;
// GPIO clear_irqenable2 is offset by 0x70 for each bank
gpio[0x6070/4] = 0x0000FFFF;



Toggling the pins from high to low, waste some time, then toggle pin back to high:

//clear_data_out has offset 0x90
gpio[0x6090/4]=0x0000FFFF;
usleep(500);
for (i=0;i<25000;i++);
//set_data_out has offset 0x94
gpio[0x6094/4]=0x0000FFFF;
usleep(500);
