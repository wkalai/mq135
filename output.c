#include "output.h"
#include "delay.h"

//PD2 设置成输出
void FAN_Init(void)
{ 	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);    //使能PORTD时钟	   	 									  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//PD.2推挽输出
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
  GPIO_SetBits(GPIOD,GPIO_Pin_2);     //PD.2输出高
} 
 

















