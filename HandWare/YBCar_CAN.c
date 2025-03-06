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
    
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_2, GPIO_PIN_SET);//����24V�����
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_5, GPIO_PIN_SET);
    
    F1_Motordata = Get_motor_measure_point(0); //��ȡ�������ָ���ŷ�Χ��0~5��
    F2_Motordata = Get_motor_measure_point(1); //��ȡ�������ָ���ŷ�Χ��0~5��
    M1_Motordata = Get_motor_measure_point(2); //��ȡ�������ָ���ŷ�Χ��0~5��
    M2_Motordata = Get_motor_measure_point(3); //��ȡ�������ָ���ŷ�Χ��0~5��
    B1_Motordata = Get_motor_measure_point(4); //��ȡ�������ָ���ŷ�Χ��0~5��
    B2_Motordata = Get_motor_measure_point(5); //��ȡ�������ָ���ŷ�Χ��0~5��
    
    PID_Init(&F1_motor_pid,PID_POSITION,PID,19000,2000);//�ṹ�壬����ģʽ�������������������������
    PID_Init(&F2_motor_pid,PID_POSITION,PID,19000,2000);//�ṹ�壬����ģʽ�������������������������
    PID_Init(&M1_motor_pid,PID_POSITION,PID,19000,2000);//�ṹ�壬����ģʽ�������������������������
    PID_Init(&M2_motor_pid,PID_POSITION,PID,19000,2000);//�ṹ�壬����ģʽ�������������������������
    PID_Init(&B1_motor_pid,PID_POSITION,PID,19000,2000);//�ṹ�壬����ģʽ�������������������������
    PID_Init(&B2_motor_pid,PID_POSITION,PID,19000,2000);//�ṹ�壬����ģʽ�������������������������
    
}



/*
    ��CANͨ�Ź������������á�
    ������Ҫʹ��CAN�����������ù������Ĺ���ģʽλ��ʶ������λģʽ��λ��Ϊ32λ�������ù�������ʶ���Ĵ���������λ�Ĵ�����Ϊ0��
    ˫·CANģʽ�¿�ѡ��������ַΪ027������Ŀ�н�CAN1����������ʼ��Ϊ0��CAN2����������ʼ��Ϊ14��
    ��CAN1ʹ�õ�ַΪ013�Ĺ������飬CAN2ʹ�õ�ַΪ14~27�Ĺ������顣
*/
/**
 * @brief          CAN��������ʼ������
 * @param[in]      none
 * @retval         none
 */
void Can_filter_Init(void)
{
    
    CAN_FilterTypeDef can_filter_st;                        //����������ṹ��
    can_filter_st.FilterActivation = ENABLE;                //ENABLEʹ�ܹ�����
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;       //���ù�����ģʽ--��ʶ������λģʽ
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;      //��������λ�� 32 λ
    can_filter_st.FilterIdHigh = 0x0000;                    //ID��λ
    can_filter_st.FilterIdLow = 0x0000;                     //ID��λ
    can_filter_st.FilterMaskIdHigh = 0x0000;                //�����������λ
    can_filter_st.FilterMaskIdLow = 0x0000;                 //�����������λ
    
    can_filter_st.FilterBank = 0;                                        //��������-˫CAN��ָ��0~27
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;                   //������������� FIFO
    HAL_CAN_ConfigFilter(&hcan1,&can_filter_st);                         //HAL�����ù���������
    HAL_CAN_Start(&hcan1);                                               //ʹ��CAN1������
    HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);    //ʹ��CAN�ĸ����ж�
    
    can_filter_st.SlaveStartFilterBank = 14;                             //˫CANģʽ�¹涨CAN������ģʽ�Ĺ��������䣬�ӹ�����Ϊ14
    can_filter_st.FilterBank = 14;                                       //��������-˫CAN��ָ��0~27
    HAL_CAN_ConfigFilter(&hcan2,&can_filter_st);                         //HAL�����ù���������
    HAL_CAN_Start(&hcan2);                                               //ʹ��CAN2������
    HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING);    //ʹ��CAN�ĸ����ж�
    
}
uint8_t xxsw;
/**
 * @brief          ������յ��ĵ������
 * @param[in]      ptr: ָ�������ݽṹ���ָ��
 * @param[in]      RX_buffer: ���ջ���������
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
  * @brief          hal��CAN�ص�����,������ղ�ͬID�������
  * @param[in]      hcan:CAN���ָ��
  * @retval         none
  */

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
    
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);  //��ȡ���ݲ����ɵ�����ݴ����к�������
    
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
 * @brief          ���͵�����Ƶ��������Բ�ͬ����Ŀ���ID��0x201, 0x202, 0x203, 0x204��
 * @param[in]      F1_motor: (0x201) ǰ���1��2006������Ƶ�������Χ [-16384, 16384]
 * @param[in]      F2_motor: (0x202) ǰ���2��2006������Ƶ�������Χ [-16384, 16384]
 * @param[in]      M1_motor: (0x203) ����1��2006������Ƶ�������Χ [-16384, 16384]
 * @param[in]      M2_motor: (0x204) ����2��2006������Ƶ�������Χ [-16384, 16384]
 * @retval         none
 */
void CAN_cmd_Frontend(int16_t F1_motor, int16_t F2_motor, int16_t M1_motor, int16_t M2_motor)
{
    uint32_t send_mail_box = 0;                     // ������Ϣ���������
    chassis_tx_message.StdId = CAN_CHASSIS_ALL_ID;  // ����CAN��Ϣ�ı�׼ID
    chassis_tx_message.IDE = CAN_ID_STD;            // ����Ϊ��׼֡
    chassis_tx_message.RTR = CAN_RTR_DATA;          // ����Ϊ����֡
    chassis_tx_message.DLC = 0x08;                  // ���ݳ��ȴ��룬��ʾ������8���ֽ�

    // ��������Ƶ���������ֵ��Ϊ��8λ�͵�8λ��Ȼ����뷢����������
    chassis_can_send_data[0] = F1_motor >> 8;   // ǰ���1�ĸ�8λ
    chassis_can_send_data[1] = F1_motor;        // ǰ���1�ĵ�8λ
    chassis_can_send_data[2] = F2_motor >> 8;   // ǰ���2�ĸ�8λ
    chassis_can_send_data[3] = F2_motor;        // ǰ���2�ĵ�8λ
    chassis_can_send_data[4] = M1_motor >> 8;   // ����1�ĸ�8λ
    chassis_can_send_data[5] = M1_motor;        // ����1�ĵ�8λ
    chassis_can_send_data[6] = M2_motor >> 8;   // ����2�ĸ�8λ
    chassis_can_send_data[7] = M2_motor;        // ����2�ĵ�8λ

    // ��CAN��Ϣ��ӵ����Ͷ�����
    HAL_CAN_AddTxMessage(&hcan1, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}

/**
 * @brief          ���͵�����Ƶ��������Բ�ͬ����Ŀ���ID��0x205, 0x206, void, void)
 * @param[in]      B1_motor: ����1��3508������Ƶ�������Χ [-16384, 16384]
 * @param[in]      B2_motor: ����2��3508������Ƶ�������Χ [-16384, 16384]
 * @param[in]      NA_1: ��������1����ʹ��
 * @param[in]      NA_2: ��������2����ʹ��
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
  * @brief          ���ص��̵�� 2006�������ָ��
  * @param[in]      i: ������,��Χ[0,5]
  * @retval         �������ָ��
  */
const Motor_Measure_Data *Get_motor_measure_point(uint8_t i)
{
    return &Motor_measure[(i & 0x07)];
}
