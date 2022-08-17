#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

#include "exti.h"
#include "led.h"


void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;//结构体的定义
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//复用时钟
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);//表示使用PE4线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line4;//第4根线
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;//使能
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿
	EXTI_Init(&EXTI_InitStruct);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line3;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;//上升沿
	EXTI_Init(&EXTI_InitStruct);
   //NVIC中断分组，使能中断代码参考
   NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//使能按键KEY0所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级0 
   NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级0 
	NVIC_Init(&NVIC_InitStructure);
}
//中断服务函数
void EXTI4_IRQHandler(void)
{
   //delay_ms(10);//延时去抖
	 if(EXTI_GetITStatus(EXTI_Line4))//得到第4根线的中断状态
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
     //GPIO_ResetBits(GPIOB,GPIO_Pin_5);//点灯
		 //delay_ms(500);//延时
	 }
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除中断服务标志位
}

void EXTI3_IRQHandler(void)
{
	//delay_ms(10);//延时去抖
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

