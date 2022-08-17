#include "stm32f10x.h"
#include "timer.h"
//TIM3 PWM 部分初始化
//PWM 输出初始化
//arr：自动重装值=?
//psc：时钟预分频数=?
//PWM 频率=1Khz
void TIM4_PWM_Init(void)//初始化
{
	GPIO_InitTypeDef GPIO_InitStruct;//初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//初始化
	TIM_OCInitTypeDef TIM_OCInitStruct;//初始化
	
	//使能定时器4 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//时钟使能
	
	//使能 GPIO时钟
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO ,ENABLE);//同时打开两个时钟
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//重映射TIM3
	
	//初始化 GPIOB.8
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;//PB8端口配置
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//I/O口设置为50MHZ
	GPIO_Init(GPIOB,&GPIO_InitStruct);//初始化
	
	//初始化 GPIOB.5
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;//PB5端口配置
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//I/O口设置为50MHZ
	GPIO_Init(GPIOB,&GPIO_InitStruct);//初始化
	
	//初始化 TIM4
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;//设置时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=899;//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=79;//预分频值
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);//初始化
	
	//初始化 TIM3
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;//设置时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=99;//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler=71;//预分频值
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);//初始化
	
	//初始化 TIM4 Channel3 PWM 模式
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;//选择定时器模式：TIM脉冲宽度调制模式2
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_High;//输出极性：TIM输出比较极性高
	TIM_OC3Init(TIM4,&TIM_OCInitStruct);//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	//初始化 TIM3 Channel3 PWM 模式
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//选择定时器模式：TIM脉冲宽度调制模式1
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_High;//输出极性：TIM输出比较极性高
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);//根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	
	//使能预装载寄存器
	TIM_OC3PreloadConfig(TIM4,TIM_OutputState_Enable);//TIM4通道3预装载配置
	TIM_OC2PreloadConfig(TIM3,TIM_OutputState_Enable);//TIM3通道2预装载配置
	
	
	TIM_Cmd(TIM3,ENABLE);//使能 TIM3
	

}
