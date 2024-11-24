/*
 * tasks.h
 *
 *  Created on: Nov 23, 2024
 *      Author: worbb
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

#include "stm32f4xx_hal.h"

typedef struct {
	uint32_t timeout;
	TIM_HandleTypeDef* htim;
	uint32_t channel;
	uint16_t warning;
	uint16_t danger;
	int16_t xyz[3];
} write_t;




void tk_BlinkBlue(void *argument);
void tk_ReadAccel(void *argument);
void tk_ReadMagnet(void *argument);
void tk_WriteLED(void *argument);


#endif /* INC_TASKS_H_ */
