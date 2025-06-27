/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "W25Q64.h"
#include "OLED.h"
#include "math.h"
extern DMA_HandleTypeDef hdma_usart2_rx;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t massage[258];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
  if(huart==&huart2){
    uint32_t a=(massage[0]<<8)+massage[1];
    W25QXX_Page_Program(massage+2,a<<8,256);
/*******用来在OLED显示屏上显示汉字字库写入进度代码，可以注释掉******/
    OLED_Clear();
    char aa[10];
    sprintf(aa,"%d",a);
    OLED_PrintASCIIString(0,0,aa,&afont16x8,OLED_COLOR_NORMAL);
    OLED_DisplayRectangle(0,27,127,16,OLED_COLOR_NORMAL);
    float x=(a*127/1303);
    OLED_DisplayFilledRectangle(1,28,(int)round(x),15,OLED_COLOR_NORMAL);
    x=(a/13.03);
    sprintf(aa,"%.2f%%",x);
    OLED_PrintASCIIString(64,0,aa,&afont16x8,OLED_COLOR_NORMAL);
    OLED_Show();
/****************************************************************/
    HAL_UARTEx_ReceiveToIdle_DMA(&huart2,(uint8_t*)massage,Size);
    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx,DMA_IT_HT);
  }
}

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
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
  /***********************************擦除整个芯片，阻塞进程，大概要等待十几秒*********************************/
  W25QXX_Erase_chip();
  uint8_t massage1[36];
  W25QXX_Read(massage1,0x00000000,36);
  HAL_UART_Transmit(&huart2, (uint8_t*)&massage1,36, HAL_MAX_DELAY);//擦除完成后会向串口发送W25Q64芯片前36个地址里存的数据（因为擦除过了所以都位0xFF）
  /******************芯片擦除完成后记得将这四行代码注释掉，再重新编译代码下载到单片机**************************/

  HAL_UARTEx_ReceiveToIdle_DMA(&huart2,(uint8_t*)massage,258);
  __HAL_DMA_DISABLE_IT(&hdma_usart2_rx,DMA_IT_HT);

  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  // OLED_PrintString(0,0,"待到秋来九月八,",OLED_COLOR_NORMAL);
  // OLED_PrintString(0,16,"我花开后百花杀.",OLED_COLOR_NORMAL);
  // OLED_PrintString(0,32,"冲天香阵透长安,",OLED_COLOR_NORMAL);
  // OLED_PrintString(0,48,"满城尽带黄金甲.",OLED_COLOR_NORMAL);
  // OLED_Show();
  while (1)
  {


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
