#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "adc.h"
#include "L9110.h"
#include "font.h"	 
#include "iic.h"
#include "oled.h"
#include "dht11.h"
#include "stm32f10x.h"
#include "main.h"
#include  "math.h"
#include "remote.h"
#include "timer.h"

/************************************************
 ALIENTEK ս��STM32F103������ʵ��17
 ADC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

 
 int main(void)
 {	
	 u8 t=0;
	u8 temperature;
	u8 humidity;
	 u8 ppm;
	  u8 key;
	 float adcx;
	 float vol;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	 TIM4_PWM_Init();    //����Ƶ
	 Remote_Init();     //�����߳�ʼ��
	KEY_Init();
	Oled_Init(); //OLED��ʼ��
 	Adc_Init();		//ADC��ʼ��
 DHT11_Init();	 //DHT11��ʪ�ȴ�������ʼ��
	  fan_Init(); //���ȳ�ʼ��
	 

	 
	while(1)
	{
			
		if(t%10==0)		//ÿ100ms��ȡһ��	
		{	
		  adcx=Get_Adc_Average(ADC_Channel_1,10);//��ȡ��ģת����ֵ
			vol=(float)adcx*3.3/4096;//��ȡ��ѹֵ
			
			ppm=pow((3.4880*10*vol)/(5-vol),(1.0/0.3203));
			DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ		
			delay_ms(10);	
 			Oled_Display_String (0,2,"Temp:");
			Oled_Display_String (2,2,"Hum:");
			Oled_Display_String (4,2,"Air:");
			Oled_Display_String (6,2,"Vol:");
			Oled_Display_String (0,85,"C");
			Oled_Display_String (2,75,"RH");
			Oled_Display_Num(0,45,temperature);
			Oled_Display_Num(2,35,humidity);
			Oled_Display_Num(4,35,ppm);	
			Oled_Display_Num(6,35,vol);
		if(humidity>70||temperature>26){
		 MOT1=1;
			MOT2=0;
				
				}
					else
						 MOT1=0;
				     MOT2=0;
		 			key=Remote_Scan();
				

					
  switch(key)    
     {
    case 56:GPIO_SetBits(GPIOB,GPIO_Pin_13);break;    
    case 24: GPIO_ResetBits(GPIOB,GPIO_Pin_13);break;
     }
		}	

	}
 }


