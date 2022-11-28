#pragma once

/**
 ******************************************************************************
 * @file           : gpio.hpp
 * @author         : Rohit Nimkar <nehalnimkar@gmail.com> <https://csrohit.github.io>
 * @brief          : GPIO library header file
 *                   This source file contains definitions of inline function and all declarations
 ******************************************************************************
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#define STM32F103xB /* temperary definition */
#include <stm32f1xx.h>
#include <stdint.h>

class GPIO
{
public:
    /**
     * @brief GPIO port pins
     *
     */
    enum PIN : uint16_t
    {
        PIN_0 = (uint16_t)0x0000,  /* GPIO pin 0 */
        PIN_1 = (uint16_t)0x0001,  /* GPIO pin 1 */
        PIN_2 = (uint16_t)0x0002,  /* GPIO pin 2 */
        PIN_3 = (uint16_t)0x0003,  /* GPIO pin 3 */
        PIN_4 = (uint16_t)0x0004,  /* GPIO pin 4 */
        PIN_5 = (uint16_t)0x0005,  /* GPIO pin 5 */
        PIN_6 = (uint16_t)0x0006,  /* GPIO pin 6 */
        PIN_7 = (uint16_t)0x0007,  /* GPIO pin 7 */
        PIN_8 = (uint16_t)0x0008,  /* GPIO pin 8 */
        PIN_9 = (uint16_t)0x0009,  /* GPIO pin 9 */
        PIN_10 = (uint16_t)0x000A, /* GPIO pin 10 */
        PIN_11 = (uint16_t)0x000B, /* GPIO pin 11 */
        PIN_12 = (uint16_t)0x000C, /* GPIO pin 12 */
        PIN_13 = (uint16_t)0x000D, /* GPIO pin 13 */
        PIN_14 = (uint16_t)0x000E, /* GPIO pin 14 */
        PIN_15 = (uint16_t)0x000F, /* GPIO pin 15 */
        PIN_ALL = (uint16_t)0xffff /* Select all gpio pins */
    };

    /**
     * @brief GPIO logical pin state
     *
     */
    enum PIN_STATE : uint8_t
    {
        LOW = (uint8_t)0x00, /* Pin state logical LOW */
        HIGH = (uint8_t)0x01 /* Pin state logical HIGH */
    };

    /**
     * @brief Enable clock source for Port A
     *
     */
    static void enable_PortA() { RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; }

    /**
     * @brief Enable clock source for Port B
     *
     */
    static void enable_PortB() { RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; }

    /**
     * @brief Enable clock source for Port C
     *
     */
    static void enable_PortC() { RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; }

    /**
     * @brief Construct a new GPIO object
     *
     * @param PORT_NAME POinter to port base address
     * @param pin_no pin number
     */
    GPIO(GPIO_TypeDef *PORT_NAME, PIN pin_no)
    {
        this->pin = pin_no;
        this->PORT = PORT_NAME;
        if (this->pin < 8)
            this->PORT->CRL = 0x02U << (this->pin << 2U);
        else
            this->PORT->CRH = 0x02U << ((this->pin - 8) << 2U);
    };

    /**
     * @brief Destroy the GPIO object
     * 
     */
    ~GPIO();

    /**
     * @brief Write HIGH logic to GPIO
     *
     */
    void high() { this->PORT->BSRR = 1 << this->pin; };

    /**
     * @brief Write LOW logic to GPIO
     *
     */
    void low() { this->PORT->BRR = 1 << this->pin; };

    /**
     * @brief Toggle GPIO
     *
     */
    void toggle();

    /**
     * @brief Set the state of GPIO pin
     *
     * @param state new state to be set
     */
    void write(PIN_STATE state)
    {
        if (state == PIN_STATE::HIGH)
        {
            high();
        }
        else
        {
            low();
        }
    };

private:
    PIN pin;
    GPIO_TypeDef *PORT;
};

inline void GPIO::toggle() { this->PORT->ODR ^= 1 << this->pin; };
