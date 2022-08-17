#include "L9110.h"
#include "stm32f10x.h"

void fan_Init()
{
 GPIO_InitTypeDef  GPIO_InitStructure;
  
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能PB,PE端口时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;     //PB13-->INA
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);     

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;     //PB15-->INB
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //推挽复用输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);      
 
 
 GPIO_ResetBits(GPIOB,GPIO_Pin_13);        //拉低PB13
 
}
