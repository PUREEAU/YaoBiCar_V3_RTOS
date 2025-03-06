#ifndef __YBCAR_CAN_H
#define __YBCAR_CAN_H
#include "stm32f4xx.h"                  // Device header
#include "can.h"

/*****      TYPEDEF      *****/
// 电机测量数据结构体
typedef struct
{
    int16_t speed_rpm;       // 转子转速（单位：rpm）
    int16_t given_current;   // 转矩给定电流
    uint8_t temperate;     // 温度（单位：℃）
    int16_t angle;           // 转子机械角度（绝对范围：0~8191）
    int16_t last_angle;      // 上一次转子机械角度（绝对范围：0~8191）
} Motor_Measure_Data;

typedef enum
{
    CAN_CHASSIS_ALL_ID = 0x200,
    CAN_2006_F1_ID = 0x201,
    CAN_2006_F2_ID = 0x202,
    CAN_2006_M1_ID = 0x203,
    CAN_2006_M2_ID = 0x204,

    CAN_2006_B1_ID = 0x205,
    CAN_2006_B2_ID = 0x206,
    CAN_GIMBAL_ALL_ID = 0x1FF,
    
} can_msg_id_e;


/*****      EXTERN      *****/
extern void Motor_Init(void);
extern void Can_filter_Init(void);
extern void CAN_cmd_Frontend(int16_t F1_motor, int16_t F2_motor, int16_t B1_motor, int16_t B2_motor);
extern void CAN_cmd_Backend(int16_t B1_motor, int16_t B2_motor, int16_t NA_1, int16_t NA_2);

extern const Motor_Measure_Data *Get_motor_measure_point(uint8_t i);
#endif
