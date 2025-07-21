#ifndef __PWM_H
#define __PWM_H

#include "stdint.h"

/**
 * @brief Initializes TIM2 and TIM3 for PWM output.
 *        - TIM2_CH1 (PA0), TIM2_CH2 (PA1): for motor control
 *        - TIM3_CH4 (PB1): for servo control
 */
void PWM_Init(void);

/**
 * @brief Sets PWM duty cycle on TIM2_CH2 (PA1).
 * @param Compare Duty cycle (0 to 100)
 */
void PWM_SetCompare2(uint16_t Compare);

/**
 * @brief Sets PWM duty cycle on TIM2_CH1 (PA0).
 * @param Compare Duty cycle (0 to 100)
 */
void PWM_SetCompare1(uint16_t Compare);

/**
 * @brief Sets PWM duty cycle on TIM3_CH4 (PB1).
 * @param Compare Pulse width in ticks (e.g. 500–2500 for servo control)
 */
void PWM_SetCompare4(uint16_t Compare);

#endif /* __PWM_H */