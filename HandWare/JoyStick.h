#ifndef __JOYSTICK_H_
#define __JOYSTICK_H_

#include "stm32f4xx.h"                  // Device header

typedef struct
{
    int16_t Rocker_RX;       // 左摇杆 X 轴值（模拟状态为 0-0xFF，数字态为 0、0x80 或 0xFF）
    int16_t Rocker_RY;       // 左摇杆 Y 轴值（模拟状态为 0-0xFF，数字态为 0、0x80 或 0xFF）
    int16_t Rocker_LX;       // 右摇杆 X 轴值（模拟状态为 0-0xFF，数字态为 0、0x80 或 0xFF）
    int16_t Rocker_LY;       // 右摇杆 Y 轴值（模拟状态为 0-0xFF，数字态为 0、0x80 或 0xFF）

    uint8_t Key_L1;          // 左侧按键 L1
    uint8_t Key_L2;          // 左侧按键 L2
    uint8_t Key_R1;          // 右侧按键 R1
    uint8_t Key_R2;          // 右侧按键 R2

    uint8_t Key_L_Up;        // 左侧方向键上
    uint8_t Key_L_Left;      // 左侧方向键左
    uint8_t Key_L_Down;      // 左侧方向键下
    uint8_t Key_L_Right;     // 左侧方向键右

    uint8_t Key_R_Up;        // 右侧方向键上
    uint8_t Key_R_Left;      // 右侧方向键左
    uint8_t Key_R_Down;      // 右侧方向键下
    uint8_t Key_R_Right;     // 右侧方向键右

    uint8_t Key_Rocker_Left; // 左摇杆按键
    uint8_t Key_Rocker_Right;// 右摇杆按键

} JoyStickData_TypeDef;





void PS2_DataKey(void);
void PS2_Start(void);
#endif

