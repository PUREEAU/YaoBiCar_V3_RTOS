#ifndef __VARIABLE_H_
#define __VARIABLE_H_

#include "tim.h"
#include "usart.h"

#include "RudderDesk.h"

#include "YBCar_PID.h"
#include "YBCar_CAN.h"

extern int8_t JoyStick_PackageData[20];


/*      From RudderDesk.h      */
// �������
extern uint16_t RD_F1_Data ; // ǰ��������
extern uint16_t RD_F2_Data ; // ǰ�Ҷ������
extern uint16_t RD_M1_Data ; // ����������
extern uint16_t RD_M2_Data ; // ���Ҷ������
extern uint16_t RD_B1_Data ; // ����������
extern uint16_t RD_B2_Data ; // ���Ҷ������

/*      From YBCar_PID.h      */
// ���Ŀ���ٶ� (��λ: ת/����)
extern float Setspeed_F1 ; // ǰ����Ŀ���ٶ�
extern float Setspeed_F2 ; // ǰ�ҵ��Ŀ���ٶ�
extern float Setspeed_M1 ; // ������Ŀ���ٶ�
extern float Setspeed_M2 ; // ���ҵ��Ŀ���ٶ�
extern float Setspeed_B1 ; // ������Ŀ���ٶ�
extern float Setspeed_B2 ; // ���ҵ��Ŀ���ٶ�


/*      From YBCar_CAN.h      */
// �����������ָ��
extern const Motor_Measure_Data *F1_Motordata; // ǰ������������ָ��
extern const Motor_Measure_Data *F2_Motordata; // ǰ�ҵ����������ָ��
extern const Motor_Measure_Data *M1_Motordata; // ��������������ָ��
extern const Motor_Measure_Data *M2_Motordata; // ���ҵ����������ָ��
extern const Motor_Measure_Data *B1_Motordata; // ��������������ָ��
extern const Motor_Measure_Data *B2_Motordata; // ���ҵ����������ָ��






#endif

