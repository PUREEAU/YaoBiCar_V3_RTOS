#include "Variable.h"

int8_t JoyStick_PackageData[20];


/*      From RudderDesk.h      */
// 舵机数据
uint16_t RD_F1_Data = 1500; // 前左舵机数据
uint16_t RD_F2_Data = 1500; // 前右舵机数据
uint16_t RD_M1_Data = 1500; // 中左舵机数据
uint16_t RD_M2_Data = 1500; // 中右舵机数据
uint16_t RD_B1_Data = 1500; // 后左舵机数据
uint16_t RD_B2_Data = 1500; // 后右舵机数据

/*      From YBCar_PID.h      */
// 电机目标速度 (单位: 转/分钟)
float Setspeed_F1 = 0.0f; // 前左电机目标速度
float Setspeed_F2 = 0.0f; // 前右电机目标速度
float Setspeed_M1 = 0.0f; // 中左电机目标速度
float Setspeed_M2 = 0.0f; // 中右电机目标速度
float Setspeed_B1 = 0.0f; // 后左电机目标速度
float Setspeed_B2 = 0.0f; // 后右电机目标速度

/*      From YBCar_CAN.h      */
// 电机测量数据指针
const Motor_Measure_Data *F1_Motordata; // 前左电机测量数据指针
const Motor_Measure_Data *F2_Motordata; // 前右电机测量数据指针
const Motor_Measure_Data *M1_Motordata; // 中左电机测量数据指针
const Motor_Measure_Data *M2_Motordata; // 中右电机测量数据指针
const Motor_Measure_Data *B1_Motordata; // 后左电机测量数据指针
const Motor_Measure_Data *B2_Motordata; // 后右电机测量数据指针

