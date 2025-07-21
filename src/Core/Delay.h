#ifndef __DELAY_H
#define __DELAY_H

#include "stdint.h"

/**
 * @brief Delays execution for a specified number of microseconds.
 * @param us Time to delay in microseconds
 */
void Delay_us(uint32_t us);

/**
 * @brief Delays execution for a specified number of milliseconds.
 * @param ms Time to delay in milliseconds
 */
void Delay_ms(uint32_t ms);

/**
 * @brief Delays execution for a specified number of seconds.
 * @param s Time to delay in seconds
 */
void Delay_s(uint32_t s);

#endif /* __DELAY_H */