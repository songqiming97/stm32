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
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//NetWeight���Ϳ�
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	USART3_Init(38400);	//���ڳ�ʼ��Ϊ115200  ,������տ�
 									  
	while(1)
	{
		if(USART3_Receive_Data() == TRUE)
		{
            printf("NetWeight = %d\r\n",NetWeight);
			WeightPeakGet(NetWeight);   //��λΪKG
		}

		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
			cnt++;
		}		   
	} 
}


