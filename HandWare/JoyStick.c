#include "JoyStick.h"
#include "Variable.h"
#include "fashion_star_uart_servo.h"
uint16_t Demo_Flag;
JoyStickData_TypeDef JoyStick_Data ;

void FashionStar_Work(void);

void Demo_Work(void)
{
    if(Demo_Flag == 1)
    {
        RD_F1_Data = 2500;
        if(TIM4->CCR3 == 2500 ) RD_M1_Data = 2500;
        if(TIM4->CCR2 == 2500 ) RD_B1_Data = 2500;
        if(TIM4->CCR1 == 2500 ) RD_F2_Data = 2500;
        if(TIM2->CCR3 == 2500 ) RD_M2_Data = 2500;
        if(TIM2->CCR2 == 2500 ) 
        {
            Demo_Flag = 2;
            RD_B2_Data = 2500;
        }
    }
    else if(Demo_Flag == 2)
    {
        RD_F1_Data = 1500;
        if(TIM4->CCR3 == 1500 ) RD_M1_Data = 1500;
        if(TIM4->CCR2 == 1500 ) RD_B1_Data = 1500;
        if(TIM4->CCR1 == 1500 ) RD_F2_Data = 1500;
        if(TIM2->CCR3 == 1500 ) RD_M2_Data = 1500;
        if(TIM2->CCR2 == 1500 ) 
        {
            Demo_Flag = 0;
            RD_B2_Data = 1500;
        }
    }
    
}


void Wheel_Velocity_Change(float F1_Vel,float F2_Vel,float M1_Vel,float M2_Vel,float B1_Vel,float B2_Vel)
{
    
    Setspeed_F1 = (F1_Vel/102)*36*60;
    Setspeed_F2 = -(F2_Vel/102)*36*60;
    
    Setspeed_M1 = (M1_Vel/102)*36*60;
    Setspeed_M2 = -(M2_Vel/102)*36*60;
    
    Setspeed_B1 = (B1_Vel/102)*36*60;
    Setspeed_B2 = -(B2_Vel/102)*36*60;
    
}



void PS2_DataKey(void)
{
    
    /* ��ఴ������ */
    JoyStick_Data.Key_L_Up    = JoyStick_PackageData[6];
    JoyStick_Data.Key_L_Left  = JoyStick_PackageData[5];
    JoyStick_Data.Key_L_Down  = JoyStick_PackageData[8];
    JoyStick_Data.Key_L_Right = JoyStick_PackageData[7];
                         
    /* �Ҳఴ������ */
    JoyStick_Data.Key_R_Up    = JoyStick_PackageData[10];
    JoyStick_Data.Key_R_Left  = JoyStick_PackageData[9];
    JoyStick_Data.Key_R_Down  = JoyStick_PackageData[12];
    JoyStick_Data.Key_R_Right = JoyStick_PackageData[11];
                        
    /* ǰ�ð������� */
    JoyStick_Data.Key_L1 = JoyStick_PackageData[13];
    JoyStick_Data.Key_L2 = JoyStick_PackageData[14];
    JoyStick_Data.Key_R1 = JoyStick_PackageData[15];
    JoyStick_Data.Key_R2 = JoyStick_PackageData[16];
    
    JoyStick_Data.Key_Rocker_Left  = JoyStick_PackageData[17];
    JoyStick_Data.Key_Rocker_Right = JoyStick_PackageData[18];
    
    JoyStick_Data.Rocker_RX = JoyStick_PackageData[2];
    JoyStick_Data.Rocker_RY = JoyStick_PackageData[1];
    JoyStick_Data.Rocker_LX = JoyStick_PackageData[4];
    JoyStick_Data.Rocker_LY = JoyStick_PackageData[3];
    
}


/*
 *
 * ����ҡ�� Y ��ֵ�ͳ���ģʽ��Car_Flag�������Ƴ����ٶȵ��߼���
 * - ��ҡ�� Y ��ֵ���ڵ��� 5 ʱ�����ó��ֵ������ٶȣ�
 * - ��ҡ�� Y ��ֵС�ڵ��� -5 ʱ�����ó��ֵķ����ٶȡ�
 * ����ģʽ�� Car_Flag ��������ͬģʽ�³����ٶȲ�ͬ��
 *
if(JoyStick_Data.Rocker_LY >= 5)
{
    // ���� Car_Flag ���ó��ֵ������ٶ�
    if(Car_Flag == 0) Wheel_Velocity_Change(115,115,70,70,65,65);
    else if(Car_Flag == 1) Wheel_Velocity_Change(130,150,115,140,120,150);
    else if(Car_Flag == 2) Wheel_Velocity_Change(150,130,140,115,150,120);
    else if(Car_Flag == 3) Wheel_Velocity_Change(130,170,80,160,110,160);
    else if(Car_Flag == 4) Wheel_Velocity_Change(170,130,160,80,160,110);
    else if(Car_Flag == 5) Wheel_Velocity_Change(-150,150,-160,130,-150,150);
}
else if(JoyStick_Data.Rocker_LY <= -5)
{
    // ���� Car_Flag ���ó��ֵķ����ٶ�
    if(Car_Flag == 0) Wheel_Velocity_Change(-120,-120,-120,-120,-120,-120);
    else if(Car_Flag == 1) Wheel_Velocity_Change(-130,-150,-115,-140,-120,-150);
    else if(Car_Flag == 2) Wheel_Velocity_Change(-150,-130,-140,-115,-150,-120);
    else if(Car_Flag == 3) Wheel_Velocity_Change(-130,-170,-80,-160,-110,-160);
    else if(Car_Flag == 4) Wheel_Velocity_Change(-170,-130,-160,-80,-160,-110);
    else if(Car_Flag == 5) Wheel_Velocity_Change(150,-150,130,-160,150,-150);
}
*/
/*                  */
uint8_t Car_Flag=0;

/*
 * ���ܣ�PS2 �����߼�
 * 1. ҡ�� Y ����Ƴ����ٶȣ�
 *    - ҡ�� Y ��ֵ���ڵ��� 5 ʱ������ Car_Flag ���ó��ֵ������ٶȡ�
 *    - ҡ�� Y ��ֵС�ڵ��� -5 ʱ������ Car_Flag ���ó��ֵķ����ٶȡ�
 *    - ҡ�� Y ��ֵ�� -5 �� 5 ֮��ʱ��ֹͣ���֡�
 * 2. �������ƣ�
 *    - R2 �� Start ͬʱ���£����� RudderDesk_ResetOn��
 *    - ��ҡ�˰������Ƴ���ģʽ�л����ض�������
 * 3. ��ʾģʽ���ƣ�
 *    - �ض���������л���ʾģʽ��Demo_Flag����
 */
void PS2_Start(void)
{
    // ��� R2 �� Start ���������� RudderDesk_ResetOn
    if(JoyStick_Data.Key_L2 && JoyStick_Data.Key_R2 && JoyStick_Data.Key_L_Up && JoyStick_Data.Key_R_Up)
    {
//        && JoyStick_Data.Key_Start == 1
        RudderDesk_ResetOn();
    }
    
    
    if(JoyStick_Data.Rocker_LY >= 5)
    {
        // ҡ�� Y ��ֵ���ڵ��� 5�����ó��������ٶ�
        if(Car_Flag == 0) Wheel_Velocity_Change(115,115,70,70,65,65);
        else if(Car_Flag == 1) Wheel_Velocity_Change(110,130,95,120,100,130);
        else if(Car_Flag == 2) Wheel_Velocity_Change(130,120,120,95,130,100);
        else if(Car_Flag == 3) Wheel_Velocity_Change(110,150,60,140,90,140);
        else if(Car_Flag == 4) Wheel_Velocity_Change(150,110,140,60,140,90);
        else if(Car_Flag == 5) Wheel_Velocity_Change(-130,130,-140,110,-130,130);
    }
    else if(JoyStick_Data.Rocker_LY <= -5)
    {
        // ҡ�� Y ��ֵС�ڵ��� -5�����ó��ַ����ٶ�
        if(Car_Flag == 0) Wheel_Velocity_Change(-120,-120,-120,-120,-120,-120);
        else if(Car_Flag == 1) Wheel_Velocity_Change(-110,-130,-95,-120,-100,-130);
        else if(Car_Flag == 2) Wheel_Velocity_Change(-130,-110,-120,-95,-130,-100);
        else if(Car_Flag == 3) Wheel_Velocity_Change(-110,-150,-60,-140,-90,-140);
        else if(Car_Flag == 4) Wheel_Velocity_Change(-150,-110,-140,-60,-140,-90);
        else if(Car_Flag == 5) Wheel_Velocity_Change(130,-130,110,-140,130,-130);
    }
    else
    {
        // ҡ�� Y ��ֵ�� -5 �� 5 ֮�䣬ֹͣ����
        Wheel_Velocity_Change(0,0,0,0,0,0);
    }
    
    if(JoyStick_Data.Key_R_Down == 1)
    {
        Handoff_Right_Left_Model();
    }
    else if(JoyStick_Data.Key_R_Left == 1 && JoyStick_Data.Key_R1 != 1 && JoyStick_Data.Key_R2 != 1)
    {
        Car_Flag = 1;
        Handoff_Sharp_Left_HandBend();
    }
    else if(JoyStick_Data.Key_R_Right == 1 && JoyStick_Data.Key_R1 != 1 && JoyStick_Data.Key_R2 != 1)
    {
        Car_Flag = 2;
        Handoff_Sharp_Right_HandBend();
    }
    else if(JoyStick_Data.Key_R_Left == 1 && JoyStick_Data.Key_R2 == 1)
    {
        Car_Flag = 3;
        Handoff_Little_Left_HandBend();
    }
    else if(JoyStick_Data.Key_R_Right == 1 && JoyStick_Data.Key_R2 == 1)
    {
        Car_Flag = 4;
        Handoff_Little_Right_HandBend();
    }
    else if(JoyStick_Data.Key_R_Up == 1)
    {
        Car_Flag = 5;
        Handoff_Left_CircleAround_Model();
    }
    else if(JoyStick_Data.Key_L_Left == 1)
    {
        Handoff_Left_Avertence_Model();
    }
    else if(JoyStick_Data.Key_L_Right == 1)
    {
        Handoff_Right_Avertence_Model();
    }
    else
    {
        if(Demo_Flag == 0)
        {
            Car_Flag = 0;
            Handoff_Front_Back_Model();
        }
    }

    // ��ʾģʽ����
    if(JoyStick_Data.Key_L1 == 1 && JoyStick_Data.Key_L2 == 1 && 
        JoyStick_Data.Key_R1 == 1 && JoyStick_Data.Key_R2 == 1 && 
        JoyStick_Data.Key_L_Left == 1  && JoyStick_Data.Key_R_Right != 1)
    {
        Demo_Flag = 1;
        Car_Flag = 0xFF;
    }
    if(JoyStick_Data.Key_L1 == 1 && JoyStick_Data.Key_L2 == 1 && 
        JoyStick_Data.Key_R1 == 1 && JoyStick_Data.Key_R2 == 1 && 
        JoyStick_Data.Key_L_Left != 1  && JoyStick_Data.Key_R_Right == 1)
    {
        Demo_Flag = 0;
    }
    
    Demo_Work();
    FashionStar_Work();
}

void FashionStar_Work(void)
{
    if(JoyStick_Data.Rocker_RX>110)JoyStick_Data.Rocker_RX=110;
    if(JoyStick_Data.Rocker_RX<-110)JoyStick_Data.Rocker_RX=-110;
        FSUS_SetServoAngle(servoUsart,0,JoyStick_Data.Rocker_RX,200,100,0);
    if(JoyStick_Data.Rocker_RY>110)JoyStick_Data.Rocker_RY=110;
    if(JoyStick_Data.Rocker_RY<-110)JoyStick_Data.Rocker_RY=-110;
        FSUS_SetServoAngle(servoUsart,1,JoyStick_Data.Rocker_RY/3,200,100,0);
    JoyStick_Data.Rocker_RX  = 0;
    JoyStick_Data.Rocker_RY  = 0;
}

void PS2_Stop(void)
{
    if(JoyStick_Data.Key_L2 == 1 )
    {
//        && JoyStick_Data.Key_Select == 1
        RudderDesk_ResetOff();
        
    }
}
