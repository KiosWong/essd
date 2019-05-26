#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

extern volatile u16 CNT_MS;
extern volatile u16 CNT_MS_MOTOR;
extern u16 Loop_10Ms;
extern u8 Alert_Flag;

//typedef struct
//{
//	int msec;
//	int  sec;
//	int  min;
//	int  hour;
//}system_time_type_struct;

//extern volatile system_time_type_struct system_time;	

void TIM3_PWM_Init(void);
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM1_Init(u16 arr, u16 psc);
 
#endif
