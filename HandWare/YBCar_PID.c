#include "YBCar_PID.h"


/* 声明电机 PID 控制器数据结构体 */
CanPid_Typedef F1_motor_pid, F2_motor_pid, M1_motor_pid, M2_motor_pid, B1_motor_pid, B2_motor_pid;


#define ABS(x)  ((x>0)? x: -x) 
/**
 * @brief          限制输入值不超过最大值
 * @param[in,out]  input: 需要被限制的输入值
 * @param[in]      max: 允许的最大值
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
 * @brief          初始化PID控制器结构体
 * @param[in,out]  pid: 指向PID控制器结构体的指针
 * @param[in]      mode: 控制器模式
 * @param[in]      PID: 包含Kp, Ki, Kd参数的数组
 * @param[in]      max_out: 输出最大值限制
 * @param[in]      max_iout: 积分输出最大值限制
 * @retval         none
 */
void PID_Init(CanPid_Typedef *pid, uint8_t mode, const float PID[3], float max_out, float max_iout)
{
    // 检查指针是否为空，如果为空则返回
    if (pid == NULL || PID == NULL)
    {
        return;
    }
    // 设置控制器模式
    pid->mode = mode;
    // 设置PID参数
    pid->Kp = PID[0]; // 比例系数
    pid->Ki = PID[1]; // 积分系数
    pid->Kd = PID[2]; // 微分系数
    // 设置输出限制
    pid->max_out = max_out;       // 输出最大值
    pid->max_iout = max_iout;     // 积分输出最大值
    // 初始化微分项缓冲区
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    // 初始化误差和输出项
    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f; // 误差项初始化为0
    pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f; // 输出项初始化为0
}


/**
 * @brief          根据PID控制器参数计算控制输出
 * @param[in,out]  pid: 指向PID控制器结构体的指针
 * @param[in]      ref: 当前的反馈值
 * @param[in]      set: 目标设定值
 * @retval         控制输出值
 */
float PID_Proc(CanPid_Typedef *pid, float ref, float set)
{
    // 检查指针是否为空，如果为空则返回0.0f
    if (pid == NULL) 
    {
        return 0.0f;
    }
    
    // 更新误差项数组
    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->fdb = ref;  // 更新反馈值
    pid->set = set;  // 更新目标设定值
    pid->error[0] = set - ref;  // 计算当前误差

    // 根据模式计算PID输出
    if (pid->mode == PID_POSITION)
    {
        // 位置式PID模式
        pid->Pout = pid->Kp * pid->error[0];  // 计算比例项
        pid->Iout += pid->Ki * pid->error[0];  // 计算积分项，并累加
        // 更新微分项缓冲区
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
        pid->Dout = pid->Kd * pid->Dbuf[0];  // 计算微分项
        // 限制积分项不超过最大积分输出
        LimitMax(pid->Iout, pid->max_iout);
        // 计算总输出
        pid->out = pid->Pout + pid->Iout + pid->Dout;
        // 限制总输出不超过最大输出
        LimitMax(pid->out, pid->max_out);
    }
    else if (pid->mode == PID_DELTA)
    {
        // 增量式PID模式
        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);  // 计算比例项
        pid->Iout = pid->Ki * pid->error[0];  // 计算积分项
        // 更新微分项缓冲区
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
        pid->Dout = pid->Kd * pid->Dbuf[0];  // 计算微分项
        // 累加到总输出
        pid->out += pid->Pout + pid->Iout + pid->Dout;
        // 限制总输出不超过最大输出
        LimitMax(pid->out, pid->max_out);
    }
    // 返回计算后的总输出
    return pid->out;
}

/**
 * @brief          重置PID控制器状态
 * @param[in,out]  pid: 指向PID控制器结构体的指针
 * @retval         none
 */
void PID_Clear(CanPid_Typedef *pid)
{
    // 检查指针是否为空，如果为空则返回
    if (pid == NULL)
    {
        return;
    }

    // 重置误差项
    pid->error[0] = 0.0f; // 最新误差
    pid->error[1] = 0.0f; // 上一次误差
    pid->error[2] = 0.0f; // 上上次误差

    // 重置微分项缓冲区
    pid->Dbuf[0] = 0.0f; // 最新微分值
    pid->Dbuf[1] = 0.0f; // 上一次微分值
    pid->Dbuf[2] = 0.0f; // 上上次微分值

    // 重置PID输出
    pid->out = 0.0f;   // 总输出
    pid->Pout = 0.0f;  // 比例输出
    pid->Iout = 0.0f;  // 积分输出
    pid->Dout = 0.0f;  // 微分输出

    // 重置目标值和反馈值
    pid->fdb = 0.0f;  // 反馈值
    pid->set = 0.0f;  // 目标值
}
