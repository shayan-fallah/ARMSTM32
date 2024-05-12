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
#include <stdio.h>
#include <string.h>
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define RST_1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET)
#define RST_0 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET)
#define EN_1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET)
#define EN_0 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET)
#define RW_1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET)
#define RW_0 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET)
#define DI_1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET)
#define DI_0 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET)
#define CS1_1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)
#define CS1_0 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET)
#define CS2_1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET)
#define CS2_0 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN PV */
int rand_blk, relative_pos, block_pos;
int i, j, k=21, r, test = 4, adc_in;
int map[9][64];
int running = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */
void comm(char c)
{
  HAL_GPIO_WritePin(GPIOA,0xFF,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,c,GPIO_PIN_SET);
  DI_0;
  RW_0;
  EN_1;
  EN_0;
  HAL_Delay(2);
}
void datw(char c)
{
  HAL_GPIO_WritePin(GPIOA,0xFF,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA,c,GPIO_PIN_SET);
  DI_1;
  RW_0;
  EN_1;
  EN_0;
  //for(k=0;k<100;k++);
    HAL_Delay(2);
}
void glcd_init(void)
{
  RST_0;
  HAL_Delay(1);
  RST_1;
  CS1_1;
  CS2_1;
  comm(0x3f);
  CS1_1;
  CS2_0;
}
void datc(char c)
{
//	 HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);
//  DI_1;
//  RW_0;
//  EN_1;
//  EN_0;
//  //for(k=0;k<100;k++);
//    HAL_Delay(2);
	HAL_GPIO_WritePin(GPIOA,c,GPIO_PIN_RESET);
	DI_1;RW_0;EN_1;EN_0;
	
//		for(int i = 184; i < 192; i++)
//		{
//			comm(i);
//			comm(0x40);
//			if(i == 184) {for(int j = 0; j < 64; j++) {HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);DI_1;RW_0;EN_1;EN_0;}}
//			if(i == 185) {for(int j = 0; j < 64; j++) {HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);DI_1;RW_0;EN_1;EN_0;}}
//			if(i == 186) {for(int j = 0; j < 64; j++) {HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);DI_1;RW_0;EN_1;EN_0;}}
//			if(i == 187) {for(int j = 0; j < 64; j++) {HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);DI_1;RW_0;EN_1;EN_0;}}
//			if(i == 188) {for(int j = 0; j < 64; j++) {HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);DI_1;RW_0;EN_1;EN_0;}}
//			if(i == 189) {for(int j = 0; j < 64; j++) {HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);DI_1;RW_0;EN_1;EN_0;}}
//			if(i == 190) {for(int j = 0; j < 64; j++) {HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);DI_1;RW_0;EN_1;EN_0;}}
//			if(i == 191) {for(int j = 0; j < 64; j++) {HAL_GPIO_WritePin(GPIOA,0xff,GPIO_PIN_RESET);DI_1;RW_0;EN_1;EN_0;}}
//		}
}
//void draw_ball(int center_pos)
//{
//	int relative_pos = center_pos % 8;
//	int block_pos = (int)(center_pos / 8) + 184;
//	
//	if(relative_pos > 4)
//	{
//		for(int y = 70; y < 78; y++)
//		{
//			comm(block_pos);
//			comm(y);
//			datw(0xff<<(relative_pos - 4));
//			comm(block_pos + 1);
//			comm(y);
//			datw(0xff>>(8 - (relative_pos - 4)));
//		}
//	}
//	else if (relative_pos < 4)
//	{
//		for(int y = 70; y < 78; y++)
//		{
//			comm(block_pos);
//			comm(y);
//			datw(0xff>>(4 - relative_pos));
//			comm(block_pos - 1);
//			comm(y);
//			datw(0xff<<(8 - (4 - relative_pos)));
//		}
//	}
//	else
//	{
//		for(int y = 70; y < 78; y++)
//		{
//			comm(block_pos);
//			comm(y);
//			datw(0xff);
//		}
//		for(int y = 70; y < 78; y++)
//		{
//			comm(block_pos);
//			comm(y);
//			datc();
//		}
//	}
//}
//void draw_pixel(int center_pos)
//{
//	int block_pos = (int)(center_pos / 8) + 184;
//	int relative_pos = center_pos % 8;
//	comm(block_pos);
//	comm(70);
//	datw(0x01<<relative_pos);
//	comm(block_pos);
//	comm(70);
//	datc();
//}
void draw(int i, int j)
{
	if(i + 4 >= 64 && i + 4 <= 127)
	{
		CS1_1;
		CS2_0;
		comm(j);
		comm(i + 4);
		datw(0xff);
	}
	else if(i + 4 > 127 && i + 4 < 191)
	{
		CS1_0;
		CS2_1;
		comm(j);
		comm((i + 4)%128 + 64);
		datw(0xff);
	}
	
	if(i - 3 >= 64 && i - 3 <= 127)
	{
		CS1_1;
		CS2_0;
		comm(j);
		comm(i - 3);
		datc(0xff);
	}
	else if( i - 3 > 127 && i - 3 < 191)
	{
		CS1_0;
		CS2_1;
		comm(j);
		comm((i - 3)%128 + 64);
		datc(0xff);
	}
}
void draw_line(int i) // 0 < i < 7
{
	CS1_0;
	CS2_1;
	block_pos = i + 184;
	for(r = 184; r < 192; r++)
	{
		comm(127);
		comm(r);
		datc(0xff);
	}
	comm(127);
	comm(block_pos);
	datw(0xff);
	
//	for(r = 184; r < 192; r++)
//	{
//		comm(127);
//		comm(r);
//		datc(0xff);
//	}
//	block_pos = (int)(i / 8) + 184;
//	relative_pos = i % 8;
//	if(relative_pos > 4)
//	{
//		comm(block_pos);
//		comm(127);
//		datw(0xff<<(relative_pos - 4));
//		comm(block_pos + 1);
//		comm(127);
//		datw(0xff>>(8 - (relative_pos - 4)));
//	}
//	if(relative_pos < 4)
//	{
//		comm(block_pos);
//		comm(127);
//		datw(0xff>>(4 - relative_pos));
//		comm(block_pos - 1);
//		comm(127);
//		datw(0xff<<(8 - (4 - relative_pos)));
//	}
//	else
//	{
//		comm(block_pos);
//		comm(127);
//		datw(0xff);
//	}


//	if(dir == 'u')
//	{
//		block_pos = (int)((i + 3) / 8) + 184;
//		relative_pos = (i + 3) % 8;
//		comm(127);
//		comm(block_pos);
//		datc(0x00 | (0x01 << relative_pos));
//		block_pos = (int)((i - 5) / 8) + 184;
//		relative_pos = (i - 5) % 8;
//		comm(127);
//		comm(block_pos);
//		datw(0x00 | (0x01 << relative_pos));
//	}
//	else
//	{
//		
//	}

}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	glcd_init();
  srand(time(NULL)); 
	hadc1.Init.NbrOfConversion=1;
	HAL_ADC_Init(&hadc1);

//	int s = 60;
//	comm(184);
//	while(s < 131)
//	{
//		draw(s);
//		s++;
//		HAL_Delay(70);
//	}



	draw_line(test);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		HAL_ADC_Start(&hadc1);
		if(HAL_ADC_PollForConversion(&hadc1,100)==HAL_OK)
		{
			adc_in = HAL_ADC_GetValue(&hadc1);
			if(test != (adc_in / 512))
			{
				test = adc_in / 512;
			}
		}
		HAL_ADC_Stop(&hadc1);
		HAL_Delay(20);
		if(k > 20)
		{
			rand_blk = (rand() % (7 - 0 + 1)) + 0;
			for(j = 0; j < 64; j++)
			{
				if(map[rand_blk][j] == 0) {map[rand_blk][j] = 60;break;}
			}
			k = 0;
		}
		k++;
		if(running == 1)
		{
			for(i = 0; i < 8; i++)
			{
				for(j = 0; j < 64; j++)
				{
					if(map[i][j] != 0)
					{
						draw(map[i][j]++, i + 184);
						if(map[i][j] > 194) map[i][j] = 0;
						if(i == test &&( map[i][j] == 140)) running = 0;
						
					}
				}
			}
		}
		
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB14 PB15 PB3
                           PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
