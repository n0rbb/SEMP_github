/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
	CoreDebug -> DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT -> CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	DWT -> CYCCNT = 0; //Reloj de depuración, cuenta ciclos de reloj, empieza en 0;

}

__weak unsigned long getRunTimeCounterValue(void)
{
return DWT -> CYCCNT;
}
/* USER CODE END 1 */

/* USER CODE BEGIN PREPOSTSLEEP */
extern void xPortSysTickHandler (void);

/*
  SysTick handler implementation that also clears overflow flag.
*/
#if (USE_CUSTOM_SYSTICK_HANDLER_IMPLEMENTATION != 0)
void SysTick_Handler (void) {
  /* Clear overflow flag */
 // SysTick->CTRL;

  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
    /* Call tick handler */
    xPortSysTickHandler();
  }
}
#endif

__weak void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

__weak void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
	HAL_ResumeTick();
}
/* USER CODE END PREPOSTSLEEP */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

