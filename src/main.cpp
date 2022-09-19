
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
		led.toggle();
		ms_delay(500);
	}
}

extern "C" void ms_delay(int ms)
{
    while (ms-- > 0)
    {
        volatile int x = 1000;
        while (x-- > 0)
            __asm("nop");
    }
}