#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main() 
{

	int fd = open("/dev/mem", O_RDWR | O_SYNC);

	if (fd < 0) 
	{
		printf("Could not open memory\n");
		return 0;
	}

	// Pad configuration
	volatile ulong *pinconf;
	pinconf = (ulong*) mmap(NULL, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x48000000);
	if (pinconf == MAP_FAILED) 
	{
		printf("Pinconf Mapping failed\n");
		close(fd);
		return 0;
	}

	// Configure Expansion header pins as input.
	pinconf[0x2158/4] = 0x011C011C;
	pinconf[0x215C/4] = 0x011C011C;
	pinconf[0x2160/4] = 0x011C011C;
	pinconf[0x2164/4] = 0x011C011C;
	pinconf[0x2168/4] = 0x011C011C;
	pinconf[0x216C/4] = 0x011C011C;
	pinconf[0x2170/4] = 0x011C011C;
	pinconf[0x2188/4] = 0x011C011C;
	close(fd);

	fd = open("/dev/mem", O_RDWR | O_SYNC);

	// GPIO Configuration: configure are input
	volatile ulong *gpio;
	gpio = (ulong*) mmap(NULL, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x49050000);
	if (gpio == MAP_FAILED) 
	{
		printf("Gpio Mapping failed\n");
		close(fd);
		return 0;
	}

	// Configure all GPIO pins on bank 5 as input.
	gpio[0x6034/4] = 0xFFFFFFFF;

	// Prints 1 when pin 3 of the Expansion header is Grounded.
	int c=0;
	for(;;) 
	{
		if(gpio[0x6038/4] == 201390076) printf("1\n");
		// printf("gpio5: %d \n",gpio[0x6038/4]);
	}
}
