#include "stm32f10x.h"    // Device header
#include "PWM.h"

/**
 * @brief Initializes GPIO pins and PWM for motor control.
 *        Motor control pins: PA4, PA5 (left), PA6, PA7 (right)
 */
void Motor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    PWM_Init();
}

/**
 * @brief Sets the speed and direction of the left motor.
 * @param Speed Range: -100 to 100
 */
void LeftMotor_Speed(int8_t Speed)
{
    if (Speed > 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare2(Speed);
    }
    else if (Speed == 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare2(0);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare2(-Speed);  // Convert to positive for CCR
    }
}

/**
 * @brief Sets the speed and direction of the right motor.
 * @param Speed Range: -100 to 100
 */
void RightMotor_Speed(int8_t Speed)
{
    if (Speed > 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_6);
        GPIO_ResetBits(GPIOA, GPIO_Pin_7);
        PWM_SetCompare1(Speed);
    }
    else if (Speed == 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_6);
        GPIO_SetBits(GPIOA, GPIO_Pin_7);
        PWM_SetCompare1(0);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);
        GPIO_SetBits(GPIOA, GPIO_Pin_7);
        PWM_SetCompare1(-Speed);  // Convert to positive for CCR
    }
}