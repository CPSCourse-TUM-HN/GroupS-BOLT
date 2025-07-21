#ifndef _LINEWALKING_H
#define _LINEWALKING_H

#include "stm32f10x.h"

/**
 * @brief Initializes the GPIOs for line tracking sensors.
 */
void LineWalking_Init(void);

/**
 * @brief Reads the states of all line tracking sensors.
 * @param L1 Pointer to left sensor 1 state.
 * @param L2 Pointer to left sensor 2 state.
 * @param R1 Pointer to right sensor 1 state.
 * @param R2 Pointer to right sensor 2 state.
 * @param Top_L Pointer to top-left sensor state.
 * @param Top_R Pointer to top-right sensor state.
 */
void Get_LineWalking(uint8_t *L1, uint8_t *L2, uint8_t *R1, uint8_t *R2, uint8_t *Top_L, uint8_t *Top_R);

/**
 * @brief Executes the line tracking algorithm based on sensor readings.
 */
void LineWalking(void);

#endif /* _LINEWALKING_H */