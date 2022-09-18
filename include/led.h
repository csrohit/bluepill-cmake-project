#pragma once
#include <stm32f1xx.h>
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

class Led
{
private:
    uint16_t pin;
    GPIO_TypeDef * PORT;

public:
    Led(GPIO_TypeDef * PORT_NAME, uint16_t pin_no);
    ~Led();
    void on();
    void off();
    void blink(uint16_t delay);
};
