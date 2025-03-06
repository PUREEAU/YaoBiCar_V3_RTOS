#include "variable.h"

/*
    ¶æ»ú¿ØÖÆÎ»ÖÃ
    X(500,1000,1500.2000,2500);
    
    TIM4->CCR3  = X;  Front_Left_RudderDesk
    TIM2->CCR3  = X;  Front_Right_RudderDesk
    
    TIM4->CCR2  = X;  Middle_Left_RudderDesk
    TIM2->CCR2  = X;  Middle_Right_RudderDesk
    
    TIM4->CCR1  = X;  Back_Left_RudderDesk
    TIM2->CCR1  = X;  Back_Right_RudderDesk
    
*/

void RD_Work(uint16_t F1_RD,uint16_t F2_RD,uint16_t M1_RD,uint16_t M2_RD,uint16_t B1_RD,uint16_t B2_RD)
{
    if(F1_RD>TIM4->CCR3)TIM4->CCR3+=10;
    else if(F1_RD<TIM4->CCR3)TIM4->CCR3-=10;
    else if(F1_RD == TIM4->CCR3){}
    
    if(F2_RD>TIM2->CCR3)TIM2->CCR3+=10;
    else if(F2_RD<TIM2->CCR3)TIM2->CCR3-=10;
    else if(F2_RD == TIM2->CCR3){}
        
    if(M1_RD>TIM4->CCR2)TIM4->CCR2+=10;
    else if(M1_RD<TIM4->CCR2)TIM4->CCR2-=10;
    else if(M1_RD == TIM4->CCR2){}
        
    if(M2_RD>TIM2->CCR2)TIM2->CCR2+=10;
    else if(M2_RD<TIM2->CCR2)TIM2->CCR2-=10;
    else if(M2_RD == TIM2->CCR2){}
    
    if(B1_RD>TIM4->CCR1)TIM4->CCR1+=10;
    else if(B1_RD<TIM4->CCR1)TIM4->CCR1-=10;
    else if(B1_RD == TIM4->CCR1){}
    
    if(B2_RD>TIM2->CCR1)TIM2->CCR1+=10;
    else if(B2_RD<TIM2->CCR1)TIM2->CCR1-=10;
    else if(B2_RD == TIM2->CCR1){}
    
}
int pwm_Flag=0;
void RudderDesk_On(void)
{
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    pwm_Flag=0xff;
}


void RudderDesk_Off(void)
{
    HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_3);
    HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_3);
}


void RudderDesk_ResetOn(void)
{
    RD_F1_Data = RD_F2_Data = RD_M1_Data = RD_M2_Data = RD_B1_Data = RD_B2_Data = 1500;
    RudderDesk_On();
}


void RudderDesk_ResetOff(void)
{
    RD_F1_Data = RD_F2_Data = RD_M1_Data = RD_M2_Data = RD_B1_Data = RD_B2_Data = 1500;
    HAL_Delay(100);
    RudderDesk_Off();
}


void Handoff_Front_Back_Model(void)
{
    
     RD_F1_Data = 1500;
     RD_F2_Data = 1500;
    
     RD_M1_Data = 1500;
     RD_M2_Data = 1500;
    
     RD_B1_Data = 1500;
     RD_B2_Data = 1500;
    
}


void Handoff_Right_Left_Model(void)
{
    
    RD_F1_Data = 2500;
    RD_F2_Data = 2500;
       
    RD_M1_Data = 2500;
    RD_M2_Data = 2500;
       
    RD_B1_Data = 2500;
    RD_B2_Data = 2500;
    
}


void Handoff_Little_Left_HandBend(void)
{
    
    RD_F1_Data = 1000;
    RD_F2_Data = 1000;
    
    RD_M1_Data = 1100;
    RD_M2_Data = 1500;
    
    RD_B1_Data = 2000;
    RD_B2_Data = 2000;
    
}


void Handoff_Little_Right_HandBend(void)
{
    
    RD_F1_Data = 2000;
    RD_F2_Data = 2000;
    
    RD_M1_Data = 1500;
    RD_M2_Data = 1900;
    
    RD_B1_Data = 1000;
    RD_B2_Data = 1000;
    
}


void Handoff_Sharp_Left_HandBend(void)
{
    
    RD_F1_Data = 1250;
    RD_F2_Data = 1250;
       
    RD_M1_Data = 1500;
    RD_M2_Data = 1500;
       
    RD_B1_Data = 1750;
    RD_B2_Data = 1750;

}


void Handoff_Sharp_Right_HandBend(void)
{
    
    RD_F1_Data = 1750;
    RD_F2_Data = 1750;
       
    RD_M1_Data = 1500;
    RD_M2_Data = 1500;
       
    RD_B1_Data = 1250;
    RD_B2_Data = 1250;
    
}


void Handoff_Left_Avertence_Model(void)
{
    
    RD_F1_Data = 1000;
    RD_F2_Data = 1000;
       
    RD_M1_Data = 1000;
    RD_M2_Data = 1000;
       
    RD_B1_Data = 1000;
    RD_B2_Data = 1000;
    
}


void Handoff_Right_Avertence_Model(void)
{
    
    RD_F1_Data = 2000;
    RD_F2_Data = 2000;
       
    RD_M1_Data = 2000;
    RD_M2_Data = 2000;
       
    RD_B1_Data = 2000;
    RD_B2_Data = 2000;
    
}


void Handoff_Left_CircleAround_Model(void)
{
    
    RD_F1_Data = 2000;
    RD_F2_Data = 1000;
       
    RD_M1_Data = 1650;
    RD_M2_Data = 1350;
       
    RD_B1_Data = 1000;
    RD_B2_Data = 2000;
    
//    Control_Wheel_Direction(-1,1,-1,1,-1,1);
    
}


void Handoff_Right_CircleAround_Model(void)
{
    
    RD_F1_Data = 2000;
    RD_F2_Data = 1000;
       
    RD_M1_Data = 1650;
    RD_M2_Data = 1350;
       
    RD_B1_Data = 1000;
    RD_B2_Data = 2000;
    
//    Control_Wheel_Direction(1,-1,1,-1,1,-1);
    
}

