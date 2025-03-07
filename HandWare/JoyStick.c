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
    
    /* 左侧按键部分 */
    JoyStick_Data.Key_L_Up    = JoyStick_PackageData[6];
    JoyStick_Data.Key_L_Left  = JoyStick_PackageData[5];
    JoyStick_Data.Key_L_Down  = JoyStick_PackageData[8];
    JoyStick_Data.Key_L_Right = JoyStick_PackageData[7];
                         
    /* 右侧按键部分 */
    JoyStick_Data.Key_R_Up    = JoyStick_PackageData[10];
    JoyStick_Data.Key_R_Left  = JoyStick_PackageData[9];
    JoyStick_Data.Key_R_Down  = JoyStick_PackageData[12];
    JoyStick_Data.Key_R_Right = JoyStick_PackageData[11];
                        
    /* 前置按键部分 */
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
 * 根据摇杆 Y 轴值和车辆模式（Car_Flag），控制车轮速度的逻辑：
 * - 当摇杆 Y 轴值大于等于 5 时，设置车轮的正向速度；
 * - 当摇杆 Y 轴值小于等于 -5 时，设置车轮的反向速度。
 * 车辆模式由 Car_Flag 决定，不同模式下车轮速度不同。
 *
if(JoyStick_Data.Rocker_LY >= 5)
{
    // 根据 Car_Flag 设置车轮的正向速度
    if(Car_Flag == 0) Wheel_Velocity_Change(115,115,70,70,65,65);
    else if(Car_Flag == 1) Wheel_Velocity_Change(130,150,115,140,120,150);
    else if(Car_Flag == 2) Wheel_Velocity_Change(150,130,140,115,150,120);
    else if(Car_Flag == 3) Wheel_Velocity_Change(130,170,80,160,110,160);
    else if(Car_Flag == 4) Wheel_Velocity_Change(170,130,160,80,160,110);
    else if(Car_Flag == 5) Wheel_Velocity_Change(-150,150,-160,130,-150,150);
}
else if(JoyStick_Data.Rocker_LY <= -5)
{
    // 根据 Car_Flag 设置车轮的反向速度
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
 * 功能：PS2 控制逻辑
 * 1. 摇杆 Y 轴控制车轮速度：
 *    - 摇杆 Y 轴值大于等于 5 时，根据 Car_Flag 设置车轮的正向速度。
 *    - 摇杆 Y 轴值小于等于 -5 时，根据 Car_Flag 设置车轮的反向速度。
 *    - 摇杆 Y 轴值在 -5 到 5 之间时，停止车轮。
 * 2. 按键控制：
 *    - R2 和 Start 同时按下，触发 RudderDesk_ResetOn。
 *    - 右摇杆按键控制车辆模式切换和特定动作。
 * 3. 演示模式控制：
 *    - 特定按键组合切换演示模式（Demo_Flag）。
 */
void PS2_Start(void)
{
    // 检测 R2 和 Start 按键，触发 RudderDesk_ResetOn
    if(JoyStick_Data.Key_L2 && JoyStick_Data.Key_R2 && JoyStick_Data.Key_L_Up && JoyStick_Data.Key_R_Up)
    {
//        && JoyStick_Data.Key_Start == 1
        RudderDesk_ResetOn();
    }
    
    
    if(JoyStick_Data.Rocker_LY >= 5)
    {
        // 摇杆 Y 轴值大于等于 5，设置车轮正向速度
        if(Car_Flag == 0) Wheel_Velocity_Change(115,115,70,70,65,65);
        else if(Car_Flag == 1) Wheel_Velocity_Change(110,130,95,120,100,130);
        else if(Car_Flag == 2) Wheel_Velocity_Change(130,120,120,95,130,100);
        else if(Car_Flag == 3) Wheel_Velocity_Change(110,150,60,140,90,140);
        else if(Car_Flag == 4) Wheel_Velocity_Change(150,110,140,60,140,90);
        else if(Car_Flag == 5) Wheel_Velocity_Change(-130,130,-140,110,-130,130);
    }
    else if(JoyStick_Data.Rocker_LY <= -5)
    {
        // 摇杆 Y 轴值小于等于 -5，设置车轮反向速度
        if(Car_Flag == 0) Wheel_Velocity_Change(-120,-120,-120,-120,-120,-120);
        else if(Car_Flag == 1) Wheel_Velocity_Change(-110,-130,-95,-120,-100,-130);
        else if(Car_Flag == 2) Wheel_Velocity_Change(-130,-110,-120,-95,-130,-100);
        else if(Car_Flag == 3) Wheel_Velocity_Change(-110,-150,-60,-140,-90,-140);
        else if(Car_Flag == 4) Wheel_Velocity_Change(-150,-110,-140,-60,-140,-90);
        else if(Car_Flag == 5) Wheel_Velocity_Change(130,-130,110,-140,130,-130);
    }
    else
    {
        // 摇杆 Y 轴值在 -5 到 5 之间，停止车轮
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

    // 演示模式控制
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
