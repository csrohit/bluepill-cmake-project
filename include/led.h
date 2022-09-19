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
    /**
     * @brief Construct a new Led object
     * 
     * @param PORT_NAME POinter to port base address
     * @param pin_no pin number
     */
    Led(GPIO_TypeDef * PORT_NAME, uint16_t pin_no);

    ~Led();

    /**
     * @brief Turn on led
     * 
     */
    void on();

    /**
     * @brief Turn off led
     * 
     */
    void off();

    /**
     * @brief Toggle led
     * 
     */
    void toggle();
};
