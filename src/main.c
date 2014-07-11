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


// Private variables

void init();

int main(void) {
    init();

    while (1) {

    }

    return 0;
}

void init() {
    schedule_init();
}

/** @} */
