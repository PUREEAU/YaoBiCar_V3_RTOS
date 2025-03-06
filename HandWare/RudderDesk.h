#ifndef __RUDDERDESK
#define __RUDDERDESK
#include "stm32f4xx.h"                  // Device header

void RD_Work(uint16_t F1_RD,uint16_t F2_RD,uint16_t M1_RD,uint16_t M2_RD,uint16_t B1_RD,uint16_t B2_RD);
    
void RudderDesk_On(void);

void RudderDesk_Off(void);

void RudderDesk_ResetOn(void);

void RudderDesk_ResetOff(void);

void Handoff_Front_Back_Model(void);

void Handoff_Right_Left_Model(void);

void Handoff_Little_Left_HandBend(void);

void Handoff_Little_Right_HandBend(void);

void Handoff_Sharp_Left_HandBend(void);

void Handoff_Sharp_Right_HandBend(void);

void Handoff_Left_Avertence_Model(void);

void Handoff_Right_Avertence_Model(void);

void Handoff_Left_CircleAround_Model(void);

void Handoff_Right_CircleAround_Model(void);





#endif

