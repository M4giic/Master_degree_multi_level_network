/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "configuration.h"


void SystemClock_Config(void);

uint8_t Measure_inputs(void);

uint8_t measured_inputs = 0x00;


char* msg = "Program is running\n\r";


int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_CAN_Init();
  MX_USART1_UART_Init();

  //if(HAL_UART_Transmit(&huart1,(uint8_t*)msg,strlen(msg),HAL_MAX_DELAY)!=HAL_OK)
	  //Error_Handler();

  PRINTF_DEBUG("Program is running\n\r");

  HAL_ADC_Start(&hadc1);

  PRINTF_DEBUG("Checking state \n\r");

  while (1)
  {

	  HAL_Delay(1000);

	  PRINTF_DEBUG("Checking state \n\r");

	  PRINTF_DEBUG("State of channels PA1-PA7 is: %d \n\r",Measure_inputs());;

  }
  /* USER CODE END 3 */
}

/*
 * This function will measure inputs on ports PA1-PA7 and save data to measured_inputs
 *
 * Information will be saved as binary number 0x00000000 where
 *
 * 		0 represent low state
 * 		1 represent high state
 *
 * on respective bit starting from lowest value and lowest peripheral PA1.
 *
 */


uint8_t Measure_inputs(void)
{
	measured_inputs = 0;

	if(adc_read_channel(ADC_CHANNEL_0)>2000)
		measured_inputs += PA0_High;

	if(adc_read_channel(ADC_CHANNEL_1)>2000)
		measured_inputs += PA1_High;

	if(adc_read_channel(ADC_CHANNEL_2)>2000)
		measured_inputs += PA2_High;

	if(adc_read_channel(ADC_CHANNEL_3)>2000)
		measured_inputs += PA3_High;

	if(adc_read_channel(ADC_CHANNEL_4)>2000)
		measured_inputs += PA4_High;

	if(adc_read_channel(ADC_CHANNEL_5)>2000)
		measured_inputs += PA5_High;

	if(adc_read_channel(ADC_CHANNEL_6)>2000)
		measured_inputs += PA6_High;

	if(adc_read_channel(ADC_CHANNEL_7)>2000)
		measured_inputs += PA7_High;

	return measured_inputs;
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{
	while(1)
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
			HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
			HAL_Delay(100);
	}

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
