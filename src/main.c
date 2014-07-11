/**
 * @file main.c Main project file.
 * @author Thomas Reidemeister <thomas@labforge.com>
 * @defgroup Main Firmware.
 * @{
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "stm32f4xx.h"
#include "schedule.h"
#include "dcmi_OV7670.h"


// Private variables

void init();
void init_io();

int main(void) {
    init();

    while (1) {

    }

    return 0;
}

void init() {
    // init the GPIOS mapped to the camera
    init_io();

    // For timing of the camera driver
    schedule_init();

    // INIT DCMI
    DCMI_OV7670_Init();
}

void init_io() {
    GPIO_InitTypeDef GPIOInit;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
            RCC_AHB1Periph_GPIOC |RCC_AHB1Periph_GPIOE, ENABLE);

    /**
     * DCMI pins
     * PA4 ->  HSYNC
     * PA6 ->  PIXCLK
     * PB7 ->  VSYNC
     * PC6 ->  D0
     * PA10 -> D1
     * PC8 ->  D2
     * PC9 ->  D3
     * PC11->  D4
     * PB6 ->  D5
     * PE5 ->  D6
     * PB8 ->  D6
     * PE6 ->  D7
     *
     * PA8     ->  Generated clock (see dcmi_OV7670.c)
     * Disabled: PB0/PB1 ->  Reset and power-down of camera  (see dcmi_OV7670.c:215)
     */
    GPIO_StructInit(&GPIOInit);
    GPIOInit.GPIO_Mode = GPIO_Mode_AF;
    GPIOInit.GPIO_OType = GPIO_OType_PP;
    GPIOInit.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIOInit.GPIO_Speed = GPIO_Speed_100MHz;

    // PORTA
    GPIOInit.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIOInit);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_DCMI);

    // PORTB
    GPIOInit.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
    GPIO_Init(GPIOB, &GPIOInit);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_DCMI);

    // PORTC
    GPIOInit.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11;
    GPIO_Init(GPIOC, &GPIOInit);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_DCMI);

    // PORTE
    GPIOInit.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init(GPIOE, &GPIOInit);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);
}

/** @} */
