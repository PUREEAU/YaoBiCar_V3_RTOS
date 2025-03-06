#ifndef __JOYSTICK_H_
#define __JOYSTICK_H_

#include "stm32f4xx.h"                  // Device header

typedef struct
{
    int16_t Rocker_RX;       // ��ҡ�� X ��ֵ��ģ��״̬Ϊ 0-0xFF������̬Ϊ 0��0x80 �� 0xFF��
    int16_t Rocker_RY;       // ��ҡ�� Y ��ֵ��ģ��״̬Ϊ 0-0xFF������̬Ϊ 0��0x80 �� 0xFF��
    int16_t Rocker_LX;       // ��ҡ�� X ��ֵ��ģ��״̬Ϊ 0-0xFF������̬Ϊ 0��0x80 �� 0xFF��
    int16_t Rocker_LY;       // ��ҡ�� Y ��ֵ��ģ��״̬Ϊ 0-0xFF������̬Ϊ 0��0x80 �� 0xFF��

    uint8_t Key_L1;          // ��ఴ�� L1
    uint8_t Key_L2;          // ��ఴ�� L2
    uint8_t Key_R1;          // �Ҳఴ�� R1
    uint8_t Key_R2;          // �Ҳఴ�� R2

    uint8_t Key_L_Up;        // ��෽�����
    uint8_t Key_L_Left;      // ��෽�����
    uint8_t Key_L_Down;      // ��෽�����
    uint8_t Key_L_Right;     // ��෽�����

    uint8_t Key_R_Up;        // �Ҳ෽�����
    uint8_t Key_R_Left;      // �Ҳ෽�����
    uint8_t Key_R_Down;      // �Ҳ෽�����
    uint8_t Key_R_Right;     // �Ҳ෽�����

    uint8_t Key_Rocker_Left; // ��ҡ�˰���
    uint8_t Key_Rocker_Right;// ��ҡ�˰���

} JoyStickData_TypeDef;





void PS2_DataKey(void);
void PS2_Start(void);
#endif

