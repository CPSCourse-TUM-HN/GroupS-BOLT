#ifndef __OLED_H
#define __OLED_H

#include "stdint.h"

/**
 * @brief Initialize the OLED display (I2C interface, configuration, clear screen).
 */
void OLED_Init(void);

/**
 * @brief Clear the entire OLED display (all pixels off).
 */
void OLED_Clear(void);

/**
 * @brief Display a single ASCII character (8x16) at given position.
 * @param Line   Line number (1–4)
 * @param Column Column number (1–16)
 * @param Char   Character to display (visible ASCII)
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);

/**
 * @brief Display a null-terminated string.
 * @param Line   Line number (1–4)
 * @param Column Column number (1–16)
 * @param String Pointer to string
 */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);

/**
 * @brief Display an unsigned decimal number.
 * @param Line   Line number (1–4)
 * @param Column Column number (1–16)
 * @param Number Number to display (0 ~ 4294967295)
 * @param Length Number of digits to show (1–10)
 */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/**
 * @brief Display a signed decimal number.
 * @param Line   Line number (1–4)
 * @param Column Column number (1–16)
 * @param Number Number to display (-2147483648 ~ 2147483647)
 * @param Length Number of digits to show (excluding sign)
 */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

/**
 * @brief Display a hexadecimal number (uppercase letters).
 * @param Line   Line number (1–4)
 * @param Column Column number (1–16)
 * @param Number Number to display (0x0 ~ 0xFFFFFFFF)
 * @param Length Number of hex digits (1–8)
 */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

/**
 * @brief Display a binary number.
 * @param Line   Line number (1–4)
 * @param Column Column number (1–16)
 * @param Number Number to display
 * @param Length Number of bits to show (1–16)
 */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif /* __OLED_H */