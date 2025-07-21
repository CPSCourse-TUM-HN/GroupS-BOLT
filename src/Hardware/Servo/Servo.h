#ifndef __SERVO_H
#define __SERVO_H

/**
 * @brief Initializes the PWM module for servo control.
 *        Servo signal is output on TIM3_CH4 (PB1).
 */
void Servo_Init(void);

/**
 * @brief Sets the angle of the servo motor.
 * @param Angle Desired angle in degrees (0 to 180)
 */
void Servo_SetAngle(float Angle);

#endif /* __SERVO_H */