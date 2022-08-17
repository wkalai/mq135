#include "remote.h"
#include "delay.h"
#include "usart.h"
//PB9

//红外遥控初始化
//设置IO以及定时器4的输入捕获
void Remote_Init(void)    			  
{  
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	//初始化GPIOB.9
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
	//根据指定的参数初始化TIMx
	//推荐定时溢出时间为10ms
  //初始化定时器输入捕获通道
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICFilter=0x02;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM4,&TIM_ICInitStructure);// TIM_ICInit
  	TIM_Cmd(TIM4,ENABLE);//使能定时器4
 
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructure);//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器	

	TIM_ITConfig( TIM4,TIM_IT_Update|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC4IE捕获中断		
	

	
		
}

//遥控器接收状态
//[7]:收到了引导码标志
//[6]:得到了一个按键的所有信息
//[5]:保留	
//[4]:标记上升沿是否已经被捕获								   
//[3:0]:溢出计时器
u8 	RmtSta=0;	  	  
u16 Dval;		//下降沿时计数器的值
u32 RmtRec=0;	//红外接收到的数据	   		    
u8  RmtCnt=0;	//按键按下的次数	  
//定时器4中断服务程序	 
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

//处理红外键盘
//返回值:
//	 0,没有任何按键按下
//其他,按下的按键键值.
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
































