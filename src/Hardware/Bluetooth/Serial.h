#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f10x.h"

/**
 * @brief Initializes USART1 and configures GPIO, NVIC, and baud rate.
 */
void Serial_Init(void);

/**
 * @brief Sends a single byte via USART1.
 * @param Byte The byte to be sent.
 */
void Serial_SendByte(uint8_t Byte);

/**
 * @brief Sends an array of bytes via USART1.
 * @param Arry Pointer to the array of bytes.
 * @param Length Number of bytes to send.
 */
void Serial_SendArry(uint8_t *Arry, uint16_t Length);

/**
 * @brief Sends a null-terminated string via USART1.
 * @param String Pointer to the string.
 */
void Serial_SendString(char *String);

/**
 * @brief Sends a decimal number (converted to ASCII) via USART1.
 * @param Number The number to be sent.
 * @param Length Number of digits to display.
 */
void Serial_SendNumber(uint32_t Number, uint8_t Length);

/**
 * @brief Gets the flag indicating whether new serial data has been received.
 * @retval 1 if new data is available, 0 otherwise.
 */
uint8_t Serial_GetRxFlag(void);

/**
 * @brief Retrieves the last received byte from USART1.
 * @retval The last received byte.
 */
uint8_t Serial_GetRxData(void);

#endif