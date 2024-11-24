/*
 * tasks.c
 *
 *  Created on: Nov 17, 2024
 *      Author: worbb
 *
*/

#include "main.h"
#include "fsm.h"
#include "cmsis_os.h"
#include "tasks.h"
#include <stdio.h>
#include "stm32f411e_discovery_accelerometer.h"
#include "arm_math.h"

#define TH_ACC_WARN 18000
#define TH_ACC_DANGER 23000

extern int encendido;


int16_t xyz[3];
float32_t modulo;


//Tareas

void tk_BlinkBlue(void *argument){
	for (;;) {
		//fsm_fire(LEDazul);
		HAL_GPIO_TogglePin(Blue_LED_GPIO_Port, Blue_LED_Pin);
		osDelay(1000);
	}
}

void tk_ReadAccel(void *argument){
	for(;;) {
		BSP_ACCELERO_GetXYZ(xyz);
		//printf("%d, %d, %d \n", xyz[0], xyz[1], xyz[2]);
		//if (
		arm_sqrt_f32(xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2], &modulo);//){
			//printf("Resultado: %d\n", (int)modulo);
			//printf("\n");
		//}
		osDelay(5);
	}
}

void tk_WriteLED(void *argument){
	for(;;) {
		write_t* data = (write_t*)argument;
		if (modulo >= TH_ACC_WARN && modulo < TH_ACC_DANGER){
			__HAL_TIM_SET_COMPARE(data->htim, data->channel, 50);
		}
		else if (modulo >= TH_ACC_DANGER){
			__HAL_TIM_SET_COMPARE(data->htim, data->channel, 90);
		}
		osDelay(data->timeout);

	}
}
