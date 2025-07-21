#include "stm32f10x.h"    // Device header
#include "PWM.h"

/**
 * @brief Initializes PWM for servo control on TIM3_CH4 (PB1).
 *        Uses PWM_Init() from PWM module.
 */
void Servo_Init(void)
{
    PWM_Init();
}

/**
 * @brief Sets the servo angle.
 * @param Angle Range: 0 to 180 degrees
 * 
 *        Converts angle to PWM pulse width:
 *        - 0° corresponds to 500us
 *        - 180° corresponds to 2500us
 */
void Servo_SetAngle(float Angle)
{
    PWM_SetCompare4((uint16_t)(Angle / 180.0f * 2000 + 500));
}