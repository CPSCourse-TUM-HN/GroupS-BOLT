#ifndef __HCSR04_H
#define __HCSR04_H

/**
 * @brief Initializes the HC-SR04 ultrasonic sensor.
 *        Configures GPIO and timer for distance measurement.
 */
void HCSR04_Init(void);

/**
 * @brief Measures the distance to an obstacle using the HC-SR04.
 * @retval Distance in centimeters.
 */
float HCSR04_Distance(void);

/**
 * @brief Executes the obstacle avoidance routine using ultrasonic sensing and servo scanning.
 */
void AvoidObstacle(void);

#endif /* __HCSR04_H */