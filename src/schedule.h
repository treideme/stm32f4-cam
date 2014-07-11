/**
 * @file schedule.h Header for HIL scheduler.
 * @author Thomas Reidemeister <thomas@labforge.ca>
 * @date 04.11.2013
 * @defgroup SCHEDULE HIL scheduler.
 * @{
 */
#ifndef _schedule_h_
#define _schedule_h_

#include <stdint.h>

/**
 * Internal structure to measure time.
 */
typedef struct {
    volatile uint32_t tickcount; /**< tick count, absolute measure of time */
    volatile uint32_t timeout;   /**< timeout counter */
} schedule_t;

/**
 * Initialise the scheduling system.
 */
extern void schedule_init();

/**
 * Delay the execution by ms milliseconds.
 * @param ms
 */
extern void schedule_delay(uint32_t ms);

/**
 * Set the time to the number of ticks.
 * 1 tick = ms.
 * @param ticks Absolute time in ms.
 */
extern void schedule_timeset(uint32_t ticks);

/**
 * Return the absolute time.
 * @return time.
 */
extern uint32_t schedule_time();

#endif /* _schedule_h_ */
/** @} */
