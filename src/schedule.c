/**
 * @file schedule.c Implementation of Scheduler.
 * @author Thomas Reidemeister <thomas@labforge.ca>
 * @date 2014/02/20
 * @addtogroup SCHEDULE
 * @{
 */
#include <stdint.h>
#include "schedule.h"
#include "stm32f4xx.h"

static schedule_t gSchedule;

void schedule_init() {
    // ---------- SysTick timer -------- //
    if (SysTick_Config(SystemCoreClock / 1000)) {
        // Capture error
        while (1){};
    }

    gSchedule.timeout = 0;
}

void schedule_delay(uint32_t ms) {
    gSchedule.timeout = ms+1;
    while(gSchedule.timeout > 0);
}

void schedule_timeset(uint32_t ticks) {
    gSchedule.tickcount = ticks;
}

uint32_t schedule_time() {
    return gSchedule.tickcount;
}

/**
  * @brief  This function handles SysTick Handler.
  */
void SysTick_Handler(void)
{
    if(gSchedule.timeout > 0)
        gSchedule.timeout--;

    /** General measure of time */
    gSchedule.tickcount++;
}

/** @} */
