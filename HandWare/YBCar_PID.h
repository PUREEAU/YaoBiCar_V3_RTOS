#ifndef __YBCAR_PID_H
#define __YBCAR_PID_H

#include "stm32f4xx.h"                  // Device header

enum PID_MODE
{
    PID_POSITION = 0,
    PID_DELTA
};


typedef struct
{
    uint8_t mode; // 控制器模式

    // PID 三参数
    float Kp; // 比例系数
    float Ki; // 积分系数
    float Kd; // 微分系数

    float max_out;  // 最大输出限制
    float max_iout; // 最大积分输出限制

    // PID 控制器的目标值和反馈值
    float set; // 目标值（设定值）
    float fdb; // 反馈值（实际值）

    // PID 控制器的输出
    float out;  // 总输出
    float Pout; // 比例输出
    float Iout; // 积分输出
    float Dout; // 微分输出

    // 微分项和误差项的缓冲区
    float Dbuf[3];  // 微分项缓冲区，用于存储最新、上一次、上上次的值
    float error[3]; // 误差项缓冲区，用于存储最新、上一次、上上次的误差
} CanPid_Typedef;

/* 声明电机 PID 控制器数据结构体 */
extern CanPid_Typedef F1_motor_pid, 
                    F2_motor_pid, 
                    M1_motor_pid, 
                    M2_motor_pid, 
                    B1_motor_pid, 
                    B2_motor_pid;

/*****      EXTERN      *****/

extern void PID_Init(CanPid_Typedef *pid, uint8_t mode, const float PID[3], float max_out, float max_iout);
extern float PID_Proc(CanPid_Typedef *pid, float ref, float set);
extern void PID_Clear(CanPid_Typedef *pid);

#endif


