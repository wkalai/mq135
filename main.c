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
 ALIENTEK 战舰STM32F103开发板实验17
 ADC 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	 TIM4_PWM_Init();    //不分频
	 Remote_Init();     //红外线初始化
	KEY_Init();
	Oled_Init(); //OLED初始化
 	Adc_Init();		//ADC初始化
 DHT11_Init();	 //DHT11温湿度传感器初始化
	  fan_Init(); //风扇初始化
	 

	 
	while(1)
	{
			
		if(t%10==0)		//每100ms读取一次	
		{	
		  adcx=Get_Adc_Average(ADC_Channel_1,10);//读取数模转换的值
			vol=(float)adcx*3.3/4096;//读取电压值
			
			ppm=pow((3.4880*10*vol)/(5-vol),(1.0/0.3203));
			DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值		
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


