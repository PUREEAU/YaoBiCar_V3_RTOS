#include "Variable.h"

int8_t JoyStick_PackageData[20];


/*      From RudderDesk.h      */
// �������
uint16_t RD_F1_Data = 1500; // ǰ��������
uint16_t RD_F2_Data = 1500; // ǰ�Ҷ������
uint16_t RD_M1_Data = 1500; // ����������
uint16_t RD_M2_Data = 1500; // ���Ҷ������
uint16_t RD_B1_Data = 1500; // ����������
uint16_t RD_B2_Data = 1500; // ���Ҷ������

/*      From YBCar_PID.h      */
// ���Ŀ���ٶ� (��λ: ת/����)
float Setspeed_F1 = 0.0f; // ǰ����Ŀ���ٶ�
float Setspeed_F2 = 0.0f; // ǰ�ҵ��Ŀ���ٶ�
float Setspeed_M1 = 0.0f; // ������Ŀ���ٶ�
float Setspeed_M2 = 0.0f; // ���ҵ��Ŀ���ٶ�
float Setspeed_B1 = 0.0f; // ������Ŀ���ٶ�
float Setspeed_B2 = 0.0f; // ���ҵ��Ŀ���ٶ�

/*      From YBCar_CAN.h      */
// �����������ָ��
const Motor_Measure_Data *F1_Motordata; // ǰ������������ָ��
const Motor_Measure_Data *F2_Motordata; // ǰ�ҵ����������ָ��
const Motor_Measure_Data *M1_Motordata; // ��������������ָ��
const Motor_Measure_Data *M2_Motordata; // ���ҵ����������ָ��
const Motor_Measure_Data *B1_Motordata; // ��������������ָ��
const Motor_Measure_Data *B2_Motordata; // ���ҵ����������ָ��

