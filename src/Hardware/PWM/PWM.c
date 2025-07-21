#include "stm32f10x.h"    // Device header

/**
 * @brief Initializes GPIO pins and timers for PWM output.
 *        - TIM2_CH1: PA0
 *        - TIM2_CH2: PA1
 *        - TIM3_CH4: PB1
 */
void PWM_Init(void)
{
    // Enable clocks for TIM2, TIM3, GPIOA, GPIOB
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    // Configure PA0, PA1, PB1 as alternate function push-pull
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  // TIM2_CH1, TIM2_CH2
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;               // TIM3_CH4
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Configure TIM2: 20kHz PWM for motor control
    TIM_InternalClockConfig(TIM2);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    // Configure TIM3: 50Hz PWM for servo control
    TIM_InternalClockConfig(TIM3);
    TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    // Configure output compare for PWM mode
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // Initial duty cycle = 0

    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  // PA0 - TIM2_CH1
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);  // PA1 - TIM2_CH2
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);  // PB1 - TIM3_CH4

    // Enable TIM2 and TIM3
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

/**
 * @brief Sets PWM duty cycle on TIM2_CH2 (PA1).
 * @param Compare Duty cycle (0 to 100)
 */
void PWM_SetCompare2(uint16_t Compare)
{
    TIM_SetCompare2(TIM2, Compare);
}

/**
 * @brief Sets PWM duty cycle on TIM2_CH1 (PA0).
 * @param Compare Duty cycle (0 to 100)
 */
void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare);
}

/**
 * @brief Sets PWM duty cycle on TIM3_CH4 (PB1).
 * @param Compare Pulse width in timer ticks (e.g., 500~2500 for 0°~180° servo)
 */
void PWM_SetCompare4(uint16_t Compare)
{
    TIM_SetCompare4(TIM3, Compare);
}