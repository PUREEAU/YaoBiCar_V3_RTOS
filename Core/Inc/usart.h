/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "ring_buffer.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart7;

extern UART_HandleTypeDef huart8;

extern UART_HandleTypeDef huart6;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_UART7_Init(void);
void MX_UART8_Init(void);
void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */


/**
  * @brief 串口数据结构体
  */
typedef struct {
    UART_HandleTypeDef *pUSARTx;   // 指向USART外设的句柄
    RingBufferTypeDef *sendBuf;    // 发送缓冲区指针（环形缓冲区）
    RingBufferTypeDef *recvBuf;    // 接收缓冲区指针（环形缓冲区）
} Usart_DataTypeDef;

// 定义接收缓冲区大小
#define USART_RECV_BUF_SIZE 500

// 定义发送缓冲区大小
#define USART_SEND_BUF_SIZE 500

// 全局变量声明
extern RingBufferTypeDef usart1SendRingBuf; // USART1发送环形缓冲区
extern RingBufferTypeDef usart1RecvRingBuf; // USART1接收环形缓冲区
extern Usart_DataTypeDef usart6;            // USART6的串口数据结构体实例
extern uint8_t usart1SendBuf[USART_SEND_BUF_SIZE + 1]; // USART1发送缓冲区
extern uint8_t usart1RecvBuf[USART_RECV_BUF_SIZE + 1]; // USART1接收缓冲区

/**
  * @brief 发送串口缓冲区中的所有数据
  * @param usart 串口数据结构体指针
  * @details 该函数用于检测环形缓冲区中是否有数据需要发送，如果有，则通过串口逐字节发送出去，直到缓冲区为空
  */
void Usart_SendAll(Usart_DataTypeDef *usart);


extern Usart_DataTypeDef* servoUsart;


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

