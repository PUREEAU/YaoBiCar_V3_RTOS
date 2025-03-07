/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Variable.h"
#include "JoyStick.h"
#include "stdio.h"
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

/* Car_InIt_Cariable */
osThreadId_t CarInitTaskHandle;
const osThreadAttr_t CarInitTask_attributes = {
  .name = "CarInitTask",
  .stack_size = 172 * 4,
  .priority = (osPriority_t) osPriorityRealtime7,
};




/* USER CODE END Variables */
/* Definitions for FreeTask */
osThreadId_t FreeTaskHandle;
const osThreadAttr_t FreeTask_attributes = {
  .name = "FreeTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void Car_Init_Task(void *argument);
/* USER CODE END FunctionPrototypes */

void Free_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of FreeTask */
  FreeTaskHandle = osThreadNew(Free_Task, NULL, &FreeTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  CarInitTaskHandle = osThreadNew(Car_Init_Task,NULL,&CarInitTask_attributes);
  
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Free_Task */
/**
  * @brief  Function implementing the FreeTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Free_Task */
void Free_Task(void *argument)
{
  /* USER CODE BEGIN Free_Task */
    int task_count;
  /* Infinite loop */
  for(;;)
  {
      PS2_DataKey();
      PS2_Start();
        task_count=uxTaskGetNumberOfTasks();
        printf("%d\r\n",task_count);
      HAL_UART_Transmit_IT(&huart7,(uint8_t *)"Free\r\n",6);
      
      
        osDelay(100);
  }
  /* USER CODE END Free_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void Car_Init_Task(void *argument)
{
    int task_count;
    
    
  for(;;)
  {
        HAL_TIM_Base_Start_IT(&htim1);
        HAL_TIM_Base_Start_IT(&htim3);
        HAL_TIM_Base_Start_IT(&htim12);
        Motor_Init();
        RudderDesk_ResetOn();
        
        HAL_UARTEx_ReceiveToIdle_DMA(&huart8,(uint8_t *)JoyStick_PackageData,20);
        
        task_count=uxTaskGetNumberOfTasks();
        printf("%d\r\n",task_count);
        
        
        
        vTaskDelete(NULL);
        
        
  }
  
}
/* USER CODE END Application */

