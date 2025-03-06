#include "Variable.h"


const float PID[3]={5,0.1,2};

Motor_Measure_Data Motor_measure[6];

static CAN_TxHeaderTypeDef  gimbal_tx_message;
static uint8_t              gimbal_can_send_data[8];

static CAN_TxHeaderTypeDef  chassis_tx_message;
static uint8_t              chassis_can_send_data[8];

        /*****      VOID      *****/
void Motor_Init(void)
{
    Can_filter_Init();
    
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_2, GPIO_PIN_SET);//开启24V供电口
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_5, GPIO_PIN_SET);
    
    F1_Motordata = Get_motor_measure_point(0); //获取电机数据指针编号范围（0~5）
    F2_Motordata = Get_motor_measure_point(1); //获取电机数据指针编号范围（0~5）
    M1_Motordata = Get_motor_measure_point(2); //获取电机数据指针编号范围（0~5）
    M2_Motordata = Get_motor_measure_point(3); //获取电机数据指针编号范围（0~5）
    B1_Motordata = Get_motor_measure_point(4); //获取电机数据指针编号范围（0~5）
    B2_Motordata = Get_motor_measure_point(5); //获取电机数据指针编号范围（0~5）
    
    PID_Init(&F1_motor_pid,PID_POSITION,PID,19000,2000);//结构体，计算模式，参数，最大输出，最大积分输出
    PID_Init(&F2_motor_pid,PID_POSITION,PID,19000,2000);//结构体，计算模式，参数，最大输出，最大积分输出
    PID_Init(&M1_motor_pid,PID_POSITION,PID,19000,2000);//结构体，计算模式，参数，最大输出，最大积分输出
    PID_Init(&M2_motor_pid,PID_POSITION,PID,19000,2000);//结构体，计算模式，参数，最大输出，最大积分输出
    PID_Init(&B1_motor_pid,PID_POSITION,PID,19000,2000);//结构体，计算模式，参数，最大输出，最大积分输出
    PID_Init(&B2_motor_pid,PID_POSITION,PID,19000,2000);//结构体，计算模式，参数，最大输出，最大积分输出
    
}



/*
    对CAN通信过滤器进行配置。
    首先需要使能CAN过滤器，设置过滤器的工作模式位标识符屏蔽位模式且位宽为32位，并设置过滤器标识符寄存器和屏蔽位寄存器均为0。
    双路CAN模式下可选过滤器地址为027，本项目中将CAN1过滤器组起始设为0，CAN2过滤器组起始设为14。
    即CAN1使用地址为013的过滤器组，CAN2使用地址为14~27的过滤器组。
*/
/**
 * @brief          CAN过滤器初始化函数
 * @param[in]      none
 * @retval         none
 */
void Can_filter_Init(void)
{
    
    CAN_FilterTypeDef can_filter_st;                        //定义过滤器结构体
    can_filter_st.FilterActivation = ENABLE;                //ENABLE使能过滤器
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;       //设置过滤器模式--标识符屏蔽位模式
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;      //过滤器的位宽 32 位
    can_filter_st.FilterIdHigh = 0x0000;                    //ID高位
    can_filter_st.FilterIdLow = 0x0000;                     //ID低位
    can_filter_st.FilterMaskIdHigh = 0x0000;                //过滤器掩码高位
    can_filter_st.FilterMaskIdLow = 0x0000;                 //过滤器掩码低位
    
    can_filter_st.FilterBank = 0;                                        //过滤器组-双CAN可指定0~27
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;                   //与过滤器组管理的 FIFO
    HAL_CAN_ConfigFilter(&hcan1,&can_filter_st);                         //HAL库配置过滤器函数
    HAL_CAN_Start(&hcan1);                                               //使能CAN1控制器
    HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);    //使能CAN的各种中断
    
    can_filter_st.SlaveStartFilterBank = 14;                             //双CAN模式下规定CAN的主从模式的过滤器分配，从过滤器为14
    can_filter_st.FilterBank = 14;                                       //过滤器组-双CAN可指定0~27
    HAL_CAN_ConfigFilter(&hcan2,&can_filter_st);                         //HAL库配置过滤器函数
    HAL_CAN_Start(&hcan2);                                               //使能CAN2控制器
    HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING);    //使能CAN的各种中断
    
}
uint8_t xxsw;
/**
 * @brief          处理接收到的电机数据
 * @param[in]      ptr: 指向电机数据结构体的指针
 * @param[in]      RX_buffer: 接收缓冲区数组
 * @retval         none
 */
#define Motor_measure_fun(ptr, RX_buffer)                                        \
{                                                                                \
    (ptr)->last_angle = (ptr)->angle;                                            \
    (ptr)->angle = (uint16_t)((RX_buffer)[0] << 8 | (RX_buffer)[1]);             \
    (ptr)->speed_rpm = (uint16_t)((RX_buffer)[2] << 8 | (RX_buffer)[3]);         \
    (ptr)->given_current = (uint16_t)((RX_buffer)[4] << 8 | (RX_buffer)[5]);     \
    (ptr)->temperate = (RX_buffer)[6];                                           \
    xxsw = (ptr)->speed_rpm;                                                     \
}

/**
  * @brief          hal库CAN回调函数,区别接收不同ID电机数据
  * @param[in]      hcan:CAN句柄指针
  * @retval         none
  */

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
    
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);  //获取数据并交由电机数据处理行函数处理
    
    switch (rx_header.StdId)
    {
        case CAN_2006_F1_ID:
        case CAN_2006_F2_ID:
        case CAN_2006_M1_ID:
        case CAN_2006_M2_ID:
        case CAN_2006_B1_ID:
        case CAN_2006_B2_ID:
        {
            static uint8_t i = 0;
            i = rx_header.StdId - CAN_2006_F1_ID;
            Motor_measure_fun(&Motor_measure[i], rx_data);
            break;
        }
        
        default:
        {
            break;
        }
    }
    
}

/**
 * @brief          发送电机控制电流命令（针对不同电机的控制ID：0x201, 0x202, 0x203, 0x204）
 * @param[in]      F1_motor: (0x201) 前电机1的2006电机控制电流，范围 [-16384, 16384]
 * @param[in]      F2_motor: (0x202) 前电机2的2006电机控制电流，范围 [-16384, 16384]
 * @param[in]      M1_motor: (0x203) 后电机1的2006电机控制电流，范围 [-16384, 16384]
 * @param[in]      M2_motor: (0x204) 后电机2的2006电机控制电流，范围 [-16384, 16384]
 * @retval         none
 */
void CAN_cmd_Frontend(int16_t F1_motor, int16_t F2_motor, int16_t M1_motor, int16_t M2_motor)
{
    uint32_t send_mail_box = 0;                     // 发送消息的邮箱变量
    chassis_tx_message.StdId = CAN_CHASSIS_ALL_ID;  // 设置CAN消息的标准ID
    chassis_tx_message.IDE = CAN_ID_STD;            // 设置为标准帧
    chassis_tx_message.RTR = CAN_RTR_DATA;          // 设置为数据帧
    chassis_tx_message.DLC = 0x08;                  // 数据长度代码，表示数据有8个字节

    // 将电机控制电流的整数值分为高8位和低8位，然后存入发送数据数组
    chassis_can_send_data[0] = F1_motor >> 8;   // 前电机1的高8位
    chassis_can_send_data[1] = F1_motor;        // 前电机1的低8位
    chassis_can_send_data[2] = F2_motor >> 8;   // 前电机2的高8位
    chassis_can_send_data[3] = F2_motor;        // 前电机2的低8位
    chassis_can_send_data[4] = M1_motor >> 8;   // 后电机1的高8位
    chassis_can_send_data[5] = M1_motor;        // 后电机1的低8位
    chassis_can_send_data[6] = M2_motor >> 8;   // 后电机2的高8位
    chassis_can_send_data[7] = M2_motor;        // 后电机2的低8位

    // 将CAN消息添加到发送队列中
    HAL_CAN_AddTxMessage(&hcan1, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}

/**
 * @brief          发送电机控制电流命令（针对不同电机的控制ID：0x205, 0x206, void, void)
 * @param[in]      B1_motor: 后电机1的3508电机控制电流，范围 [-16384, 16384]
 * @param[in]      B2_motor: 后电机2的3508电机控制电流，范围 [-16384, 16384]
 * @param[in]      NA_1: 保留参数1，不使用
 * @param[in]      NA_2: 保留参数2，不使用
 * @retval         none
 */
void CAN_cmd_Backend(int16_t B1_motor, int16_t B2_motor, int16_t NA_1, int16_t NA_2)
{
    uint32_t send_mail_box;
    gimbal_tx_message.StdId = CAN_GIMBAL_ALL_ID;
    gimbal_tx_message.IDE = CAN_ID_STD;
    gimbal_tx_message.RTR = CAN_RTR_DATA;
    gimbal_tx_message.DLC = 0x08; 
    
    gimbal_can_send_data[0] = (B1_motor >> 8);
    gimbal_can_send_data[1] =  B1_motor;
    gimbal_can_send_data[2] = (B2_motor >> 8);
    gimbal_can_send_data[3] =  B2_motor;
    gimbal_can_send_data[4] = (NA_1 >> 8);
    gimbal_can_send_data[5] =  NA_1;
    gimbal_can_send_data[6] = (NA_2 >> 8);
    gimbal_can_send_data[7] =  NA_2;
    
    HAL_CAN_AddTxMessage(&hcan1, &gimbal_tx_message, gimbal_can_send_data, &send_mail_box);
}


/**
  * @brief          返回底盘电机 2006电机数据指针
  * @param[in]      i: 电机编号,范围[0,5]
  * @retval         电机数据指针
  */
const Motor_Measure_Data *Get_motor_measure_point(uint8_t i)
{
    return &Motor_measure[(i & 0x07)];
}
