#include "remote.h"
#include "delay.h"
#include "usart.h"
//PB9

//����ң�س�ʼ��
//����IO�Լ���ʱ��4�����벶��
void Remote_Init(void)    			  
{  
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��ʱ�� 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	//��ʼ��GPIOB.9
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	  
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
  
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=10000;
	TIM_TimeBaseInitStructure.TIM_Prescaler=(72-1);
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	//����ָ���Ĳ�����ʼ��TIMx
	//�Ƽ���ʱ���ʱ��Ϊ10ms
  //��ʼ����ʱ�����벶��ͨ��
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICFilter=0x02;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM4,&TIM_ICInitStructure);// TIM_ICInit
  	TIM_Cmd(TIM4,ENABLE);//ʹ�ܶ�ʱ��4
 
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructure);//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���	

	TIM_ITConfig( TIM4,TIM_IT_Update|TIM_IT_CC4,ENABLE);//��������ж� ,����CC4IE�����ж�		
	

	
		
}

//ң��������״̬
//[7]:�յ����������־
//[6]:�õ���һ��������������Ϣ
//[5]:����	
//[4]:����������Ƿ��Ѿ�������								   
//[3:0]:�����ʱ��
u8 	RmtSta=0;	  	  
u16 Dval;		//�½���ʱ��������ֵ
u32 RmtRec=0;	//������յ�������	   		    
u8  RmtCnt=0;	//�������µĴ���	  
//��ʱ��4�жϷ������	 
void TIM4_IRQHandler(void)
{ 		    	 
 
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{
		if(RmtSta&0x80)	//
		{	
			RmtSta&=~0X10;							//
			if((RmtSta&0X0F)==0X00)RmtSta|=1<<6;	//
			if((RmtSta&0X0F)<15)RmtSta++;
			else
			{
				RmtSta&=~(1<<7);					//
				RmtSta&=0XF0;						//
			}								 	   	
		}							    
	}
	if(TIM_GetITStatus(TIM4,TIM_IT_CC4)!=RESET)
	{	  
		if(RDATA)//
		{
  			TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);//
			TIM_SetCounter(TIM4,0);	//
			RmtSta|=0X10;//
		}else //
		{
			Dval=TIM_GetCapture4(TIM4);//
  		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);//
			if(RmtSta&0X10)	// 
			{
 				if(RmtSta&0X80)//
				{
					
					if(Dval>300&&Dval<800)//
					{
						RmtRec<<=1;	//
						RmtRec|=0;	//   
					}else if(Dval>1400&&Dval<1800)	//
					{
						RmtRec<<=1;		//
						RmtRec|=1;	//
					}else if(Dval>2200&&Dval<2600)//
					{
						RmtCnt++; 					//
						RmtSta&=0XF0;				//		
					}
 				}else if(Dval>4200&&Dval<4700)		//
				{
					RmtSta|=1<<7;//
					RmtCnt=0;	//
				}						 
			}
			RmtSta&=~(1<<4);
		}				 		     	    					   
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update|TIM_IT_CC4);	 	    
}

//����������
//����ֵ:
//	 0,û���κΰ�������
//����,���µİ�����ֵ.
u8 Remote_Scan(void)
{        
	u8 sta=0;       
    u8 t1,t2;  
	if(RmtSta&(1<<6))//
	{ 
	    t1=RmtRec>>24;			//
	    t2=(RmtRec>>16)&0xff;	//
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)// 
	    { 
	        t1=RmtRec>>8;
	        t2=RmtRec; 	
	        if(t1==(u8)~t2)sta=t1;//
		}   
		if((sta==0)||((RmtSta&0X80)==0))//
		{
		 	RmtSta&=~(1<<6);//
			RmtCnt=0;		//
		}
	}  
    return sta;
}
































