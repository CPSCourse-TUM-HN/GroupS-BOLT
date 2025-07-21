#include "stm32f10x.h"                  // Device header
#include <stdio.h>

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

/**
 * @brief Initializes USART1 on GPIOA (PA9: TX, PA10: RX).
 *        Configures GPIO, USART parameters, interrupts, and enables USART1.
 */
void Serial_Init(void)
{
    // 1. Enable clocks for USART1 and GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 2. Configure GPIOA pins for TX and RX
    GPIO_InitTypeDef GPIO_InitStructure;

    // PA9 - TX (Alternate Function Push-Pull)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PA10 - RX (Input Pull-Up)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. Configure USART1
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    // Enable USART1 RX interrupt
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // 4. Configure NVIC for USART1 interrupt
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    // 5. Enable USART1
    USART_Cmd(USART1, ENABLE);
}

/**
 * @brief Sends a single byte via USART1.
 * @param Byte The byte to be sent.
 */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/**
 * @brief Sends an array of bytes via USART1.
 * @param Arry Pointer to the byte array.
 * @param Length Number of bytes to send.
 */
void Serial_SendArry(uint8_t *Arry, uint16_t Length)
{
    for (uint16_t i = 0; i < Length; i++)
    {
        Serial_SendByte(Arry[i]);
    }
}

/**
 * @brief Sends a null-terminated string via USART1.
 * @param String Pointer to the string.
 */
void Serial_SendString(char *String)
{
    for (uint8_t i = 0; String[i] != '\0'; i++)
    {
        Serial_SendByte(String[i]);
    }
}

/**
 * @brief Computes power (x^y).
 * @param x Base
 * @param y Exponent
 * @retval Result of x raised to the power y.
 */
uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
    uint32_t Result = 1;
    while (y--)
    {
        Result *= x;
    }
    return Result;
}

/**
 * @brief Sends a number as ASCII characters via USART1.
 * @param Number The number to send.
 * @param Length Number of digits to display.
 */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
 * @brief Overrides printf redirection to USART1.
 */
int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}

/**
 * @brief Checks if a byte has been received.
 * @retval 1 if new data available, 0 otherwise.
 */
uint8_t Serial_GetRxFlag(void)
{
    if (Serial_RxFlag == 1)
    {
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

/**
 * @brief Returns the last received byte.
 * @retval Received byte.
 */
uint8_t Serial_GetRxData(void)
{
    return Serial_RxData;
}

/**
 * @brief USART1 interrupt handler.
 *        Sets flag and stores received data when RXNE interrupt occurs.
 */
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        Serial_RxData = USART_ReceiveData(USART1);
        Serial_RxFlag = 1;
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}