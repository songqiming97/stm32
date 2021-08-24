#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "usart3.h"
#include "WeightPeakGet.h"

extern s32 NetWeight;
			 	
 int main(void)
 {	 
	u8 t=0;
	u8 cnt=0;
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//NetWeight发送口
	LED_Init();		  		//初始化与LED连接的硬件接口
	USART3_Init(38400);	//串口初始化为115200  ,命令接收口
 									  
	while(1)
	{
		if(USART3_Receive_Data() == TRUE)
		{
            printf("NetWeight = %d\r\n",NetWeight);
			WeightPeakGet(NetWeight);   //单位为KG
		}

		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//提示系统正在运行	
			t=0;
			cnt++;
		}		   
	} 
}


