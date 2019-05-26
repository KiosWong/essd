#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "stm32f10x_dma.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "bsp.h"

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"
#endif

extern volatile u8 rcv_sta;

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���
struct __FILE {
	int handle;

};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}
//�ض���fputc����
int fputc(int ch, FILE *f)
{
#ifdef __DEBUG
	while((USART1->SR & 0X40) == 0); //ѭ������,ֱ���������
	USART1->DR = (u8) ch;
#endif
	return ch;
}
#endif

/*ʹ��microLib�ķ���*/
/*
int fputc(int ch, FILE *f)
{
USART_SendData(USART1, (uint8_t) ch);

while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}

   return ch;
}
int GetKey (void)  {

   while (!(USART1->SR & USART_FLAG_RXNE));

   return ((int)(USART1->DR & 0x1FF));
}
*/

#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART_RX_BUF[100];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART2_RX_BUF[USART_REC_LEN];
u8 USART2_TX_BUF[USART_TX_LEN];
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA = 0;     //����״̬���
u16 USART2_RX_STA = 0;
u16 NETWORK_RX_STA = 0;
//��ʼ��IO ����1
//bound:������
void uart_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	USART_DeInit(USART1);  //��λ����1
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9

	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

	//Usart1 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ; //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); //��ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���

}

void TIM4_Init(u16 arr, u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );


	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void TIM4_Set(u8 sta)
{
	if(sta) {
		TIM_SetCounter(TIM4, 0);
		TIM_Cmd(TIM4, ENABLE);
	} else TIM_Cmd(TIM4, DISABLE);
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		if(USART_RX_STA & 0x4000) {
			USART_RX_STA |= 1 << 15;	//��ǽ������
		}
		if(USART2_RX_STA & 0x4000) {
			USART2_RX_STA |= 1 << 15;	//��ǽ������
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		TIM4_Set(0);
	}
}

void uart2_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2��GPIOBʱ��
	USART_DeInit(USART2);  //��λ����2
	//USART2_TX   PA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	//USART2_RX	  PA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	//USART2 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ; //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ



	USART_Init(USART2, &USART_InitStructure); //��ʼ������

	TIM4_Init(99, 7199);
	USART2_RX_STA = 0;
	TIM4_Set(0);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�

	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���

}

//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//	u8 Res;

//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntEnter();
//#endif
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) { //�����ж�(���յ������ݱ�����0x0d 0x0a��β)

//		Res = USART_ReceiveData(USART1); //(USART1->DR);	//��ȡ���յ�������

//		if((USART_RX_STA & 0x8000) == 0) { //����δ���
//			if(USART_RX_STA & 0x4000) { //���յ���0x0d
//				if(Res != 0x0a)USART_RX_STA = 0; //���մ���,���¿�ʼ
//				else USART_RX_STA |= 0x8000;	//���������
//			} else { //��û�յ�0X0D
//				if(Res == 0x0d)USART_RX_STA |= 0x4000;
//				else {
//					USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA > (USART_REC_LEN - 1))USART_RX_STA = 0; //�������ݴ���,���¿�ʼ����
//				}
//			}
//		}
//	}
//#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
//	OSIntExit();
//#endif
//}

void USART1_IRQHandler(void)                	//����3�жϷ������
{
	u8 res;
	static vu16 times = 0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		res = USART_ReceiveData(USART1);
		if(0 == (USART_RX_STA & (1 << 15))) {
			if(times < USART_REC_LEN) {
				TIM_SetCounter(TIM4, 0);
				if(USART_RX_STA == 0) {
					USART_RX_STA |= 1 << 14;
					times = 0;
					TIM_Cmd(TIM4, ENABLE);
				}
				USART_RX_BUF[times++] = res;
				++USART_RX_STA;
			} else
				USART_RX_STA |= 1 << 15;
		}
	}
}


void USART2_IRQHandler(void)                	//����3�жϷ������
{
	u8 res;
	static vu16 times = 0;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		res = USART_ReceiveData(USART2);
		if(0 == (USART2_RX_STA & (1 << 15))) {
			if(times < USART_REC_LEN) {
				TIM_SetCounter(TIM4, 0);
				if(USART2_RX_STA == 0) {
					USART2_RX_STA |= 1 << 14;
					times = 0;
					TIM_Cmd(TIM4, ENABLE);
				}
				USART2_RX_BUF[times++] = res;
				++USART2_RX_STA;
			} else
				USART2_RX_STA |= 1 << 15;
		}
	}
}

u8 USART2_SendString(u8 *p)
{
	u8 i = 0;
	u8 SendByte = 0;
	while(p[i] != 0) {
		while((USART2->SR & 0X40) == 0);
		USART_SendData(USART2, p[i]);
		i++;
		SendByte ++;
	}
	return SendByte;
}

void USART2_SendRaw(u8 *p, u8 len)
{
	int i = 0;
	while(i < len) {
		while((USART2->SR & 0X40) == 0);
		USART_SendData(USART2, p[i]);
		i++;
	}
}


void USART2_Response()
{
	u8 i = 0;
	if(USART2_RX_BUF[0]) {
		printf("%s\r\n", USART2_RX_BUF);	//���͵�����
		USART2_RX_STA = 0;
		for(i = 0; i < USART_REC_LEN; i++)
			USART2_RX_BUF[i] = 0;
	}
}

void USART1_SendCommand()
{
	u8 i = 0;
	if(USART_RX_BUF[0]) {
		USART2_SendString(USART_RX_BUF);
		USART_RX_STA = 0;
		USART2_RX_STA = 0;
		for(i = 0; i < USART_REC_LEN; i++) {
			USART_RX_BUF[i] = 0;
			USART2_RX_BUF[i] = 0;
		}
	}
}
#endif

