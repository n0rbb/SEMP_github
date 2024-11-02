/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fsm.h"
#include "stm32f411e_discovery_accelerometer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define threshold_x 17000
#define threshold_y 17000
#define threshold_z 17000

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim10;

/* USER CODE BEGIN PV */
int blueledflag = 0;

int activoflag = 0;
int available = 1;

enum estados_led{
	LED_ENCENDIDO,
	LED_APAGADO,
};

enum estados_btn{
	INACTIVO,
//	AR,
	ACTIVO,
//	AR2,
};

int Trigger_state = 0;
int Blue_Led_state = 0;
int Red_Led_state = 0;
int Green_Led_state = 0;
int Orange_Led_state = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM10_Init(void);
/* USER CODE BEGIN PFP */
//Funciones de salida de transiciones ledfsm
static void func_LED_ENCENDIDO (fsm_t* this){
    Blue_Led_state = 1;
    blueledflag = 0;
}

static void func_LED_APAGADO (fsm_t* this){
    Blue_Led_state = 0;
    blueledflag = 0;

}

//Funciones de entrada de transiciones ledfsm
static int blueLED_timer_finished (fsm_t* this) { //Función que pasa el valor de timer para el estado de una fsm
    return blueledflag;
}

//Funciones de salida de transiciones btnfsm


static void func_ACTIVO (fsm_t* this){
	activoflag = 1;

	Trigger_state = 0;

	Red_Led_state = 1;
	Green_Led_state = 1;
	Orange_Led_state = 1;
}

static void func_INACTIVO (fsm_t* this){
	activoflag = 0;

	Trigger_state = 0;

	Red_Led_state = 0;
	Green_Led_state = 0;
	Orange_Led_state = 0;

}

/*static void func_AR2 (fsm_t* this){
	available = 0;
	Trigger_state = 0;
	Red_Led_state = 1;
	Green_Led_state = 0;
	Orange_Led_state = 0;
}*/

//Funciones de entrada de transiciones btnfsm
static int read_BTN(fsm_t* this){
	int readbtn = HAL_GPIO_ReadPin(User_BTN_GPIO_Port, User_BTN_Pin);
	if (available && readbtn){
			available = 0;
			Trigger_state = 1;
			return 1;
	}
	else return 0;
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static fsm_trans_t ledfsm[] = { //FSM que enciende y apaga el LED.
    {LED_ENCENDIDO, blueLED_timer_finished, LED_APAGADO, func_LED_APAGADO},
    {LED_APAGADO, blueLED_timer_finished, LED_ENCENDIDO, func_LED_ENCENDIDO},
    {-1, NULL, -1, NULL}, //Valor centinela para la FSM

};

static fsm_trans_t btnfsm[] = { //FSM que controla el cooldown del pulsador (antirrebote)
	{INACTIVO, read_BTN, ACTIVO, func_ACTIVO},
//	{AR, turnon, ACTIVO, func_ACTIVO},
//	{AR, turnoff, INACTIVO, func_INACTIVO},
	{ACTIVO, read_BTN, INACTIVO, func_INACTIVO},
	{-1, NULL, -1, NULL},
};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim4); //Inicializo el timer 4.
  HAL_TIM_Base_Start_IT(&htim3); //También el 3.

  fsm_t* maquinaLED = fsm_new(ledfsm);
  fsm_t* maquinaBTN = fsm_new(btnfsm);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  fsm_fire(maquinaBTN);
	  fsm_fire(maquinaLED);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_WritePin(BTN_Trigger_GPIO_Port, BTN_Trigger_Pin, Trigger_state);
	  HAL_GPIO_WritePin(Blue_Led_GPIO_Port, Blue_Led_Pin, Blue_Led_state);
	  HAL_GPIO_WritePin(Red_Led_GPIO_Port, Red_Led_Pin, Red_Led_state);
	  HAL_GPIO_WritePin(Green_Led_GPIO_Port, Green_Led_Pin, Green_Led_state);
	  HAL_GPIO_WritePin(Orange_Led_GPIO_Port, Orange_Led_Pin, available);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 4799;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 9999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_ETRF;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_NONINVERTED;
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim3, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 4799;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 9999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 4799;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 999;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, Green_Led_Pin|Orange_Led_Pin|Red_Led_Pin|Blue_Led_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : User_BTN_Pin */
  GPIO_InitStruct.Pin = User_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(User_BTN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Green_Led_Pin Orange_Led_Pin Red_Led_Pin Blue_Led_Pin */
  GPIO_InitStruct.Pin = Green_Led_Pin|Orange_Led_Pin|Red_Led_Pin|Blue_Led_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
