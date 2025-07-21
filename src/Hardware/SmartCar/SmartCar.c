#include "stm32f10x.h"    // Device header
#include "Motor.h"

/**
 * @brief Initializes the smart car by initializing motor control.
 */
void SmartCar_Init(void)
{
    Motor_Init();
}

/**
 * @brief Moves the car forward at fixed speed.
 */
void Move_Forward(void)
{
    LeftMotor_Speed(40);
    RightMotor_Speed(40);
}

/**
 * @brief Moves the car backward at fixed speed.
 */
void Move_Backward(void)
{
    LeftMotor_Speed(-50);
    RightMotor_Speed(-50);
}

/**
 * @brief Stops the car.
 */
void Car_Stop(void)
{
    LeftMotor_Speed(0);
    RightMotor_Speed(0);
}

/**
 * @brief Turns the car left in place or arc depending on speed.
 * @param Speed Speed for the right motor (0 to 100)
 */
void Turn_Left(int8_t Speed)
{
    LeftMotor_Speed(0);
    RightMotor_Speed(Speed);
}

/**
 * @brief Turns the car right in place or arc depending on speed.
 * @param Speed Speed for the left motor (0 to 100)
 */
void Turn_Right(int8_t Speed)
{
    LeftMotor_Speed(Speed);
    RightMotor_Speed(0);
}

/**
 * @brief Rotates the car clockwise in place.
 */
void Clockwise_Rotation(void)
{
    LeftMotor_Speed(90);
    RightMotor_Speed(-90);
}

/**
 * @brief Rotates the car counter-clockwise in place.
 */
void CounterClockwise_Rotation(void)
{
    LeftMotor_Speed(-90);
    RightMotor_Speed(90);
}