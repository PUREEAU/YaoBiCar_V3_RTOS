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
    uint8_t mode; // ������ģʽ

    // PID ������
    float Kp; // ����ϵ��
    float Ki; // ����ϵ��
    float Kd; // ΢��ϵ��

    float max_out;  // ����������
    float max_iout; // �������������

    // PID ��������Ŀ��ֵ�ͷ���ֵ
    float set; // Ŀ��ֵ���趨ֵ��
    float fdb; // ����ֵ��ʵ��ֵ��

    // PID �����������
    float out;  // �����
    float Pout; // �������
    float Iout; // �������
    float Dout; // ΢�����

    // ΢����������Ļ�����
    float Dbuf[3];  // ΢������������ڴ洢���¡���һ�Ρ����ϴε�ֵ
    float error[3]; // �������������ڴ洢���¡���һ�Ρ����ϴε����
} CanPid_Typedef;

/* ������� PID ���������ݽṹ�� */
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


