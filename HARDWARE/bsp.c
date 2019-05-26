#include "bsp.h"

void bsp_init()
{
#ifndef __DEBUG       
        __system_lock();
#endif
        
	delay_init();	    	 															
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 	
	Adc_Init();
	uart_init(115200);																
	uart2_init(38400);
	TIM2_Int_Init(99,719);
	TIM3_PWM_Init();
	OLED_IIC_GPIO_Init();
	MPU6050_IIC_GPIO_Init();
	Led_PWM_GPIO_Init();
	Key_GPIO_Init();
	HC05_GPIO_Init();
	while(!MPU_init());
	HC05_Init();
	GUI_Init();
	
}



