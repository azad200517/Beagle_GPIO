#include<stdio.h>
//#include<asm/arch/gpio.h>

void init_config(void)
{
	int GPIO_PIN;
	GPIO_PIN = 139; // To use the Pin No. 3
	// GPIO_PIN = GPIO_138; // To use the Pin No. 5

}


void gpio_set_value(int value) // To glow the LED
{
	FILE *fp;
	char path[80] = "/sys/class/gpio ";

	fp = fopen(path, "w");
	if (fp == NULL)
	{
		fprintf(stderr,"Can't open file\n");
		return -1;
	}
	else 
	{

		fprintf(fp, export);
		fprintf(fp, %d, value);
	}
	fclose()
		return 0;

}


void gpio_reset_value(int value) // To OFF the LED
{
	FILE *fp;
	char path[80] = "/sys/class/gpio ";

	fp = fopen(path, "w");
	if (fp == NULL)
	{
		fprintf(stderr,"Can't open file\n");
		return -1;
	}
	else
	{

		fprintf(fp, export);
		fprintf(fp, %d, value);
	}
	fclose()
		return 0;

}


int main(void)
{

	int value;
	printf("Enter the value High 1 or Low O\n");
	scanf("%d", & value);

	while(1)
	{
		init_config();
		if (value == 1)
		{
			gpio_set_value(value);
			sleep(1);
		}


		else if (value == 0)
		{
			gpio_reset_value(value);
			sleep(1);
		}
	}

	return 0;
}







