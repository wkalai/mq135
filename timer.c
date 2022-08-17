#include "stm32f10x.h"
#include "timer.h"
//TIM3 PWM ���ֳ�ʼ��
//PWM �����ʼ��
//arr���Զ���װֵ=?
//psc��ʱ��Ԥ��Ƶ��=?
//PWM Ƶ��=1Khz
void TIM4_PWM_Init(void)//��ʼ��
{
	GPIO_InitTypeDef GPIO_InitStruct;//��ʼ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//��ʼ��
	TIM_OCInitTypeDef TIM_OCInitStruct;//��ʼ��
	
	//ʹ�ܶ�ʱ��4 ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʱ��ʹ��
	
	//ʹ�� GPIOʱ��
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO ,ENABLE);//ͬʱ������ʱ��
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//��ӳ��TIM3
	
	//��ʼ�� GPIOB.8
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;//PB8�˿�����
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//I/O������Ϊ50MHZ
	GPIO_Init(GPIOB,&GPIO_InitStruct);//��ʼ��
	
	//��ʼ�� GPIOB.5
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;//PB5�˿�����
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;//I/O������Ϊ50MHZ
	GPIO_Init(GPIOB,&GPIO_InitStruct);//��ʼ��
	
	//��ʼ�� TIM4
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;//����ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period=899;//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler=79;//Ԥ��Ƶֵ
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);//��ʼ��
	
	//��ʼ�� TIM3
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;//����ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period=99;//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler=71;//Ԥ��Ƶֵ
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);//��ʼ��
	
	//��ʼ�� TIM4 Channel3 PWM ģʽ
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ2
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_High;//������ԣ�TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM4,&TIM_OCInitStruct);//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	//��ʼ�� TIM3 Channel3 PWM ģʽ
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ1
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_High;//������ԣ�TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM4,TIM_OutputState_Enable);//TIM4ͨ��3Ԥװ������
	TIM_OC2PreloadConfig(TIM3,TIM_OutputState_Enable);//TIM3ͨ��2Ԥװ������
	
	
	TIM_Cmd(TIM3,ENABLE);//ʹ�� TIM3
	

}
