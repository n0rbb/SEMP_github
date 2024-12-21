/**
  ******************************************************************************
  * @file           : test_runner.c
  * @brief          : Main test runner
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 DIE UPM.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "unity.h"
#include "gpio.h"
#include "unity.h"
#include "i2c.h"
#include "spi.h"
#include "math.h"
#include "stm32f411e_discovery_accelerometer.h"
#include "stm32f411e_discovery_magnetometer.h"
#include <stdio.h>
//TO BE DONE - ADD INCLUDES

/* Private define ------------------------------------------------------------*/
#define TEST_TIMEOUT_TICKS	10000

/* Private variables ---------------------------------------------------------*/
static volatile uint8_t exti_flag = 0;
static uint32_t last_tick;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
void test_tick();
void test_button();
void test_sqrt_1600();
void test_acc_valid_module();
void test_mag_valid_module();
void test_led_red();
void test_led_orange();
void test_led_blue();
void test_led_green();
void test_led_green_50();
void test_led_green_90();
void test_led_red_50();
void test_led_red_90();
void test_acc_get_x();
void test_acc_get_y();
void test_acc_get_z();
void test_mag_get_north();

void setUp(void) {
    // set stuff up here
	exti_flag = 0;
	last_tick = HAL_GetTick();
}

void tearDown(void) {
    // clean stuff up here
}

/**
  * @brief  Test that the tick system changes with time
  */
void
test_tick_changes() {
	volatile uint32_t i;

	//Read tick value and perform long operation.
	for (i=0; i<100000; i++) {
		if (HAL_GetTick() - last_tick) {
			break;
		}
	}

	TEST_ASSERT_NOT_EQUAL(last_tick, HAL_GetTick());
}

/**
  * @brief  Test that the tick system timing is correct
  */
void
test_tick_correct() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the user button
  */
void
test_button() {
	printf("*****\r\n");
	printf("Pulsa el boton de usuario\r\n");

	//Read tick value and perform long operation.
	while ( (HAL_GetTick() - last_tick) <= TEST_TIMEOUT_TICKS) {
		if (exti_flag) {
			break;
		}
	}

	TEST_ASSERT_EQUAL(1, exti_flag);
}

/**
  * @brief  Test the Square Root
  */
void test_sqrt_1600() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the accelerometer module with 2G range
  */
void test_acc_valid_module() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the magnetometer module
  */
void test_mag_valid_module() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the led red turns on
  */
void test_led_red() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the led orange turns on
  */
void test_led_orange() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the led blue turns on
  */
void test_led_blue() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the led green turns on
  */
void test_led_green() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the led green turns on 50% of time
  */
void test_led_green_50() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the led green turns on 90% of time
  */
void test_led_green_90() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the led red turns on 50% of time
  */
void test_led_red_50() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the led red turns on 90% of time
  */
void test_led_red_90() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the accelerometer oriented to X axis, with 1G on X and 0 on Y and Z
  */
void test_acc_get_x() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the accelerometer oriented to Y axis, with 1G on Y and 0 on X and Z
  */
void test_acc_get_y() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the accelerometer oriented to Z axis, with 1G on Z and 0 on X and Y
  */
void test_acc_get_z() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}

/**
  * @brief  Test the magnetometer oriented to North
  */
void test_mag_get_north() {
	//TO BE DONE - COMPLETE TEST
	TEST_IGNORE();
}


/**
  * @brief  The test entry point.
  * @retval int
  */
int main(void)
{
	HAL_Init();
	SystemClock_Config();

	HAL_Delay(1000);

	MX_GPIO_Init();
	//TO BE DONE - ADD REQUIRED INIT FUNCTIONS
	BSP_ACCELERO_Init();
	LSM303AGR_MagInit();
	MX_TIM4_Init();
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);


	UnityBegin("test_runner_p3");
	RUN_TEST(test_tick_changes);
	RUN_TEST(test_tick_correct);
	RUN_TEST(test_button);
	RUN_TEST(test_sqrt_1600);
	RUN_TEST(test_acc_valid_module);
	RUN_TEST(test_mag_valid_module);
	RUN_TEST(test_led_red);
	RUN_TEST(test_led_orange);
	RUN_TEST(test_led_blue);
	RUN_TEST(test_led_green);
	RUN_TEST(test_led_green_50);
	RUN_TEST(test_led_green_90);
	RUN_TEST(test_led_red_50);
	RUN_TEST(test_led_red_90);
	RUN_TEST(test_acc_get_x);
	RUN_TEST(test_acc_get_y);
	RUN_TEST(test_acc_get_z);
	RUN_TEST(test_mag_get_north);

	return UnityEnd();
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	exti_flag = 1;
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM10 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM10) {
    HAL_IncTick();
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
__weak void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators to 96MHz, from HSE at 8MHz with PLL,
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
   * APB1: 24MHz
   * APB1 timers: 48MHz
   * APB2: 96MHz
   * APB2 timers: 96MHz
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
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

/**
  * @brief  This function is used by syscall _write to print a char
  * @param ch : character to be printed
  * @retval number of bytes actually sent
  */
int __io_putchar(int ch) {
	return ITM_SendChar(ch);
}

/**
  * @brief  This function is used by unity to print a char
  * @param ch : character to be printed
  * @retval number of bytes actually sent
  */
inline int putchar(int ch) {
	return __io_putchar(ch);
}
