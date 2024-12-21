/*
 * stm32f411e_discovery_magnetometer.h
 *
 *  Created on: Nov 22, 2024
 *      Author: worbb
 */

#ifndef STM32F411E_DISCOVERY_MAGNETOMETER_H_
#define STM32F411E_DISCOVERY_MAGNETOMETER_H_

#include "../Components/lsm303dlhc/lsm303dlhc.h"
#include "../Components/lsm303agr/lsm303agr.h"

void LSM303AGR_MagInit(void);
void LSM303AGR_MagReadXYZ(int16_t *pData);

void LSM303DLHC_MagInit();
void LSM303DLHC_MagReadXYZ(int16_t *pData);

#endif /* STM32F411E_DISCOVERY_MAGNETOMETER_H_ */
