#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

#include "exti.h"
#include "led.h"


void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;//�ṹ��Ķ���
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//����ʱ��
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);//��ʾʹ��PE4��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line4;//��4����
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;//ʹ��
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;//�ж�ģʽ
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;//�½���
	EXTI_Init(&EXTI_InitStruct);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line3;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;//������
	EXTI_Init(&EXTI_InitStruct);
   //NVIC�жϷ��飬ʹ���жϴ���ο�
   NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�0 
   NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�0 
	NVIC_Init(&NVIC_InitStructure);
}
//�жϷ�����
void EXTI4_IRQHandler(void)
{
   //delay_ms(10);//��ʱȥ��
	 if(EXTI_GetITStatus(EXTI_Line4))//�õ���4���ߵ��ж�״̬
	 {
		 delay_ms(10);
		 if(KEY0==0)
		 {
		   LED0=0;
			 delay_ms(300);
			 LED0=1;
			 delay_ms(300);
			 LED0=0;
			 delay_ms(300);
			 LED0=1;
			 delay_ms(300);
		 }
     //GPIO_ResetBits(GPIOB,GPIO_Pin_5);//���
		 //delay_ms(500);//��ʱ
	 }
	 EXTI_ClearITPendingBit(EXTI_Line4);//����жϷ����־λ
}

void EXTI3_IRQHandler(void)
{
	//delay_ms(10);//��ʱȥ��
	if(EXTI_GetITStatus(EXTI_Line3))
	{
		delay_ms(10);
	if(KEY1==0)
	{
    LED1=0;
    delay_ms(500);		
	}
	//GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	//delay_ms(500);
	//GPIO_SetBits(GPIOB,GPIO_Pin_5);
	//delay_ms(500);
	//GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	//delay_ms(500);
	//GPIO_SetBits(GPIOB,GPIO_Pin_5);
	//delay_ms(500);
   }
	EXTI_ClearITPendingBit(EXTI_Line3);
}

