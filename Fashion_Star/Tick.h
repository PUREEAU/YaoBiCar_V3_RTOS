#ifndef __TICK_H
#define __TICK_H

#include "stm32f4xx.h"                  // Device header
#include "fashion_star_uart_servo.h"
#include "tim.h"

/**
  * @brief ��ʱ����ʱ������extern ������ʵ�ʶ����������ļ��У�
  */
extern __IO uint32_t TickCnt;

/**
  * @brief �ȴ���ʱ��ɣ�����ʽ��
  * @details ������ʱ���жϣ����ȴ�ֱ����ʱ����TickCnt��Ϊ0��Ȼ��ֹͣ��ʱ���жϡ�
  */
void Tick_Wait(void);

/**
  * @brief ��ʱָ����΢����
  * @param nTime ��Ҫ��ʱ��΢����
  * @details �������΢����ת��Ϊ�������������ü�ʱ����TickCnt��Ȼ�����Tick_Wait�ȴ���ʱ��ɡ�
  */
void Tick_DelayUs(__IO uint32_t nTime);

/**
  * @brief ��ʱָ���ĺ�����
  * @param nTime ��Ҫ��ʱ�ĺ�����
  * @details ֱ�����ü�ʱ����TickCntΪĿ���������Ȼ�����Tick_Wait�ȴ���ʱ��ɡ�
  */
void Tick_DelayMs(__IO uint32_t nTime);

/**
  * @brief ���õ���ʱ��������ʽ��
  * @param nTime ����ʱ�ĺ�����
  * @details ���ü�ʱ����TickCntΪָ���ĵ���ʱʱ�䣬��������ʱ���жϡ�
  */
void Tick_CountdownBegin(__IO uint32_t nTime);

/**
  * @brief ��������ʱ
  * @details ����ʱ����TickCnt��Ϊ0����ֹͣ��ʱ���жϡ�
  */
void Tick_CountdownCancel(void);

/**
  * @brief �жϵ���ʱ�Ƿ�ʱ
  * @return ���ص���ʱ�Ƿ���ɣ�0��δ��ʱ��1���ѳ�ʱ��
  * @details ����ʱ����TickCnt�Ƿ�Ϊ0������ǣ����ʾ����ʱ��ɡ�
  */
uint8_t Tick_CountdownIsTimeout(void);

#endif // __TICK_H



