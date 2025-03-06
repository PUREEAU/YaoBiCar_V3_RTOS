
	
#ifndef __tick_H
#define __tick_H

#include "stm32f4xx.h"                  // Device header
#include "fashion_star_uart_servo.h"
#include "tim.h"
#include "tick.h"

	
extern __IO uint32_t TickCnt;

void Tick_Wait(void);
void Tick_DelayUs(__IO uint32_t nTime);
void Tick_DelayMs(__IO uint32_t nTime);
void Tick_CountdownBegin(__IO uint32_t nTime);
void Tick_CountdownCancel(void);
uint8_t Tick_CountdownIsTimeout(void);



#endif




