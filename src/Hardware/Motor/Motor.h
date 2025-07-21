#ifndef __MOTOR_H
#define __MOTOR_H

#include "stdint.h"

/**
 * @brief Initializes motor control GPIO and PWM.
 *        Configures PA4, PA5, PA6, PA7 as motor direction pins.
 */
void Motor_Init(void);

/**
 * @brief Controls the left motor's direction and speed.
 * @param Speed Motor speed (-100 to 100). Positive = forward, Negative = backward, 0 = brake.
 */
void LeftMotor_Speed(int8_t Speed);

/**
 * @brief Controls the right motor's direction and speed.
 * @param Speed Motor speed (-100 to 100). Positive = forward, Negative = backward, 0 = brake.
 */
void RightMotor_Speed(int8_t Speed);

#endif /* __MOTOR_H */