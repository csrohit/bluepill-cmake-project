#include <led.h>
#include <stm32f1xx.h>
#include <gpio.h>

/**
 * @brief Add blocking delay
 *
 * @param ms number of milliseconds
 */
void ms_delay(int ms)
{
    while (ms-- > 0)
    {
        volatile int x = 1000;
        while (x-- > 0)
            __asm("nop");
    }
}

Led::Led(GPIO_TypeDef * PORT_NAME, uint16_t pin_no)
{
    this->pin = pin_no;
    this->PORT = PORT_NAME;
    if(this->pin < 8)
    this->PORT->CRL = 0x02U << (this->pin << 2U);
    else
    this->PORT->CRH = 0x02U << ((this->pin - 8) << 2U);
}

Led::~Led()
{
}

void Led::on()
{
    this->PORT->BSRR = 1 << this->pin;
}

void Led::off()
{

    this->PORT->BRR = 1 << this->pin;
}

void Led::blink(uint16_t delay)
{
    this->on();
    ms_delay(delay);
    this->off();
    ms_delay(delay);
}
