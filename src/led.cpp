#include <led.h>
#include <stm32f1xx.h>
#include <gpio.h>



Led::Led(GPIO_TypeDef *PORT_NAME, uint16_t pin_no)
{
    this->pin = pin_no;
    this->PORT = PORT_NAME;
    if (this->pin < 8)
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

void Led::toggle()
{
    this->PORT->ODR ^= 1 << this->pin;
}
