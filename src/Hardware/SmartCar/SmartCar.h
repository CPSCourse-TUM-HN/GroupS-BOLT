#ifndef __SMARTCAR_H
#define __SMARTCAR_H

#include "stdint.h"

/**
 * @brief Initializes the smart car (motors, PWM).
 */
void SmartCar_Init(void);

/**
 * @brief Moves the car forward.
 */
void Move_Forward(void);

/**
 * @brief Moves the car backward.
 */
void Move_Backward(void);

/**
 * @brief Stops both motors.
 */
void Car_Stop(void);

/**
 * @brief Turns the car left by stopping the left motor and running the right.
 * @param Speed Right motor speed (0 to 100)
 */
void Turn_Left(int8_t Speed);

/**
 * @brief Turns the car right by stopping the right motor and running the left.
 * @param Speed Left motor speed (0 to 100)
 */
void Turn_Right(int8_t Speed);

/**
 * @brief Rotates the car clockwise in place.
 */
void Clockwise_Rotation(void);

/**
 * @brief Rotates the car counter-clockwise in place.
 */
void CounterClockwise_Rotation(void);

#endif /* __SMARTCAR_H */