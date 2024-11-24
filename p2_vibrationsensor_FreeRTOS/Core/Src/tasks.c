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
#include "stm32f411e_discovery_magnetometer.h"
#include "arm_math.h"

extern int encendido;
extern osMutexId_t mutexi2c1Handle;
int16_t accxyz[3], magxyz[3], cumxyz[3], magcumxyz[3];

//extern fsm_t* LEDazul;

int absolute(int16_t value){
	if (value >= 0) return value;
	else return -value;
}


//Tareas

void tk_BlinkBlue(void *argument){
	for (;;) {

		HAL_GPIO_TogglePin(Blue_LED_GPIO_Port, Blue_LED_Pin);
		osDelay(1000);
	}
}

void tk_ReadAccel(void *argument){

	for(;;) {
		osMutexAcquire(mutexi2c1Handle, osWaitForever); //Pongo a esperar hasta que el token esté available
		BSP_ACCELERO_GetXYZ(accxyz);
		osMutexRelease(mutexi2c1Handle); //Pongo el token available
		printf("Acc: %d, %d, %d\n", accxyz[0], accxyz[1], accxyz[2]);
		cumxyz[0] += absolute(accxyz[0]);
		cumxyz[1] += absolute(accxyz[1]);
		cumxyz[2] += absolute(accxyz[2]);

		printf("Cumacc: %d, %d, %d\n", cumxyz[0], cumxyz[1], cumxyz[2]);

		osDelay(5);
	}
}

void tk_ReadMagnet(void *argument){
	for(;;){

		osMutexAcquire(mutexi2c1Handle, osWaitForever); //Pongo a esperar hasta que el token esté available
		LSM303AGR_MagReadXYZ(magxyz);
		osMutexRelease(mutexi2c1Handle); //Pongo el token en available
		printf("Mag: %d, %d, %d\n", magxyz[0], magxyz[1], magxyz[2]);
		magcumxyz[0] += absolute(magxyz[0]);
		magcumxyz[1] += absolute(magxyz[1]);
		magcumxyz[2] += absolute(magxyz[2]);
		printf("Cummag: %d, %d, %d\n", magxyz[0], magxyz[1], magxyz[2]);

		osDelay(10);
	}
}

void tk_WriteLED(void *argument){
	for(;;) {
		write_t* data = (write_t*)argument;
		float modulo;
		if (data->channel == TIM_CHANNEL_1){
			arm_sqrt_f32(cumxyz[0]*cumxyz[0] + cumxyz[1]*cumxyz[1] + cumxyz[2]*cumxyz[2], &modulo);
			cumxyz[0] = 0; //Reseteo los valores del acumulado recién leído.
			cumxyz[1] = 0;
			cumxyz[2] = 0;
		}
		else if (data->channel == TIM_CHANNEL_3){
			arm_sqrt_f32(magcumxyz[0]*magcumxyz[0] + magcumxyz[1]*magcumxyz[1] + magcumxyz[2]*magcumxyz[2], &modulo);
			magcumxyz[0] = 0;
			magcumxyz[1] = 0;
			magcumxyz[2] = 0;
		}
		modulo /= 400; //Divido por 200^2 para promediar

		if (modulo >= data->warning && modulo < data->danger){
			__HAL_TIM_SET_COMPARE(data->htim, data->channel, 50);
		}
		else if (modulo >= data->danger){
			__HAL_TIM_SET_COMPARE(data->htim, data->channel, 90);
		}
		osDelay(data->timeout);
	}
}
