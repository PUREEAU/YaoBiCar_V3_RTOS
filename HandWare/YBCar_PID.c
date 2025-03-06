#include "YBCar_PID.h"


/* ������� PID ���������ݽṹ�� */
CanPid_Typedef F1_motor_pid, F2_motor_pid, M1_motor_pid, M2_motor_pid, B1_motor_pid, B2_motor_pid;


#define ABS(x)  ((x>0)? x: -x) 
/**
 * @brief          ��������ֵ���������ֵ
 * @param[in,out]  input: ��Ҫ�����Ƶ�����ֵ
 * @param[in]      max: ��������ֵ
 * @retval         none
 */
#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

            /*****      VOID      *****/
    
/**
 * @brief          ��ʼ��PID�������ṹ��
 * @param[in,out]  pid: ָ��PID�������ṹ���ָ��
 * @param[in]      mode: ������ģʽ
 * @param[in]      PID: ����Kp, Ki, Kd����������
 * @param[in]      max_out: ������ֵ����
 * @param[in]      max_iout: ����������ֵ����
 * @retval         none
 */
void PID_Init(CanPid_Typedef *pid, uint8_t mode, const float PID[3], float max_out, float max_iout)
{
    // ���ָ���Ƿ�Ϊ�գ����Ϊ���򷵻�
    if (pid == NULL || PID == NULL)
    {
        return;
    }
    // ���ÿ�����ģʽ
    pid->mode = mode;
    // ����PID����
    pid->Kp = PID[0]; // ����ϵ��
    pid->Ki = PID[1]; // ����ϵ��
    pid->Kd = PID[2]; // ΢��ϵ��
    // �����������
    pid->max_out = max_out;       // ������ֵ
    pid->max_iout = max_iout;     // ����������ֵ
    // ��ʼ��΢�������
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    // ��ʼ�����������
    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f; // ������ʼ��Ϊ0
    pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f; // ������ʼ��Ϊ0
}


/**
 * @brief          ����PID��������������������
 * @param[in,out]  pid: ָ��PID�������ṹ���ָ��
 * @param[in]      ref: ��ǰ�ķ���ֵ
 * @param[in]      set: Ŀ���趨ֵ
 * @retval         �������ֵ
 */
float PID_Proc(CanPid_Typedef *pid, float ref, float set)
{
    // ���ָ���Ƿ�Ϊ�գ����Ϊ���򷵻�0.0f
    if (pid == NULL) 
    {
        return 0.0f;
    }
    
    // �������������
    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->fdb = ref;  // ���·���ֵ
    pid->set = set;  // ����Ŀ���趨ֵ
    pid->error[0] = set - ref;  // ���㵱ǰ���

    // ����ģʽ����PID���
    if (pid->mode == PID_POSITION)
    {
        // λ��ʽPIDģʽ
        pid->Pout = pid->Kp * pid->error[0];  // ���������
        pid->Iout += pid->Ki * pid->error[0];  // �����������ۼ�
        // ����΢�������
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
        pid->Dout = pid->Kd * pid->Dbuf[0];  // ����΢����
        // ���ƻ�����������������
        LimitMax(pid->Iout, pid->max_iout);
        // ���������
        pid->out = pid->Pout + pid->Iout + pid->Dout;
        // ���������������������
        LimitMax(pid->out, pid->max_out);
    }
    else if (pid->mode == PID_DELTA)
    {
        // ����ʽPIDģʽ
        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);  // ���������
        pid->Iout = pid->Ki * pid->error[0];  // ���������
        // ����΢�������
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
        pid->Dout = pid->Kd * pid->Dbuf[0];  // ����΢����
        // �ۼӵ������
        pid->out += pid->Pout + pid->Iout + pid->Dout;
        // ���������������������
        LimitMax(pid->out, pid->max_out);
    }
    // ���ؼ����������
    return pid->out;
}

/**
 * @brief          ����PID������״̬
 * @param[in,out]  pid: ָ��PID�������ṹ���ָ��
 * @retval         none
 */
void PID_Clear(CanPid_Typedef *pid)
{
    // ���ָ���Ƿ�Ϊ�գ����Ϊ���򷵻�
    if (pid == NULL)
    {
        return;
    }

    // ���������
    pid->error[0] = 0.0f; // �������
    pid->error[1] = 0.0f; // ��һ�����
    pid->error[2] = 0.0f; // ���ϴ����

    // ����΢�������
    pid->Dbuf[0] = 0.0f; // ����΢��ֵ
    pid->Dbuf[1] = 0.0f; // ��һ��΢��ֵ
    pid->Dbuf[2] = 0.0f; // ���ϴ�΢��ֵ

    // ����PID���
    pid->out = 0.0f;   // �����
    pid->Pout = 0.0f;  // �������
    pid->Iout = 0.0f;  // �������
    pid->Dout = 0.0f;  // ΢�����

    // ����Ŀ��ֵ�ͷ���ֵ
    pid->fdb = 0.0f;  // ����ֵ
    pid->set = 0.0f;  // Ŀ��ֵ
}
