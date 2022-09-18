
#include <main.h>
#include <stm32f1xx.h>
#include <stdint.h>
#include <led.h>
#include <gpio.h>

int main(void)
{
	ENABLE_GPIOC();
	Led led(GPIOC, 13);
	while (1)
	{
		led.blink(500);
	}
	for (;;)
		;
}
