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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BASIC.h"
#include <stdio.h>
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

/* USER CODE BEGIN PV */
char basic_prog[] = "\
pri \"expr_test:\"\n\
var i\n\
i = 9230\n\
i = 2 < 1 \n\
i = i * i \n\
i = i + 2 * ( 1 + ( 3 + 4 ) * 5 + 1 * 1 - 2 + ( 4 - 2 ) * ( 10 - 9 ) )\n\
pri i\n\
pri \"test_end:\"\n\
pri \"if_test:\"\n\
if i > 2\n\
    pri \"big\"\n\
endif \n\
if i < 2\n\
    pri \"smal\"\n\
    if i \n\
        pri \"inner_if\"\n\
    endif \n\
    pri \"inner_endif\"\n\
endif \n\
pri \"test_end:\"\n\
pri \"while_test:\"\n\
while i < 2 \n\
    pri \"small\"\n\
    while 1\n\
    endwh \n\
    pri \"inner_endwh\"\n\
endwh \n\
while i > 2 \n\
    pri i \n\
    i = i - 1 \n\
endwh \n\
pri \"prim\"\n\
var b \n\
var div \n\
var flag \n\
b = 2 \n\
div = 2 \n\
flag = 0 \n\
while b < 100 \n\
    flag = 1 \n\
    div = 2 \n\
    while div < b / 2 + 1 \n\
        if ( b / div ) * div == b \n\
        flag = 0 \n\
        endif \n\
        div = div + 1\n\
    endwh \n\
    if flag \n\
    pri b \n\
    endif \n\
    b = b + 1 \n\
endwh \n\
pri \"prim_end\"\n\
\0\
";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//重定向printf函数
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1,(uint8_t *)&ch, 1, 0xffff);
    return ch;
}

LIST lists;
VARLISTS varLists;
int mem[MEM_SIZE];
u8 RxTemp;
u8 volatile RxStop = 0;
u32 RxCount = 0;
char RxBuf[2048];
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
    RxTemp = 0;
    RxStop = 0;
    RxCount = 0;
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    HAL_UART_MspInit(&huart1);
    HAL_UART_Receive_IT(&huart1, &RxTemp, sizeof(RxTemp));
    HAL_Delay(500);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    //C语言质数计算
    int b=2, div=2, flag=0;
    while (b < 100)
    {
        flag = 1;
        div = 2;
        while (div < b/2 + 1)
        {
            if ((b/div) * div == b)
            {
                flag = 0;
            }
            div++;
        }

        if (flag)
        {
            printf("%d ", b);
        }

        b++;
    }


    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        HAL_Delay(500);
        printf("HELLOW\r\n");

        if(RxStop == 1)
        {
            RxStop = 0;

			printf("%s\n", RxBuf);
            printf("code_len: %d\n", strlen(RxBuf));
            parser(RxBuf, &lists, &varLists);
            index_match(RxBuf, &lists);
            //pri_var(&varLists);
            //list_print(&lists);
            pri_parser(&lists, &varLists, 0, lists.index);
            printf("\n-----BASIC RUN-----\n");
            basic_run(&lists, &varLists, mem);

            HAL_UART_Receive_IT(&huart1, &RxTemp, sizeof(RxTemp));
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

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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
//USART1字符接收
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(RxTemp != '\0')
    {
        HAL_UART_Receive_IT(&huart1, &RxTemp, sizeof(RxTemp));
        RxBuf[RxCount] = RxTemp;
        RxCount++;

        if(RxCount > 1023)
        {
            RxCount = 0;
        }
    }
    else	//接收到换行符后停止接收
    {
        RxBuf[RxCount] = '\0';
        RxCount = 0;
        RxStop = 1;
    }
}
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
