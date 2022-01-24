#include "main.h"


//指示灯线程
static struct rt_thread led_thread;				//按键扫描线程控制块
static char led_thread_stack[512];				//线程堆栈
#define LED_THREAD_PRIORITY         16			//线程优先级，按键扫描为最高优先级
#define LED_THREAD_TIMESLICE        100			//线程的时间片大小


int ams_thread_init(void)					//创建开机检测线程
{
	rt_thread_init(&led_thread,					//线程控制块
                   "led_thread",				//线程控制块名字
                   led_thread_entry,			//线程入口函数
                   RT_NULL,						//线程入口函数的参数
                   &led_thread_stack[0],		//线程栈起始地址
                   sizeof(led_thread_stack),	//线程栈大小
                   LED_THREAD_PRIORITY, 		//线程优先级
									 LED_THREAD_TIMESLICE);		//线程时间片大小
									 
	rt_thread_startup(&led_thread); 
				   
	return 0;
}

void led_thread_entry(void *par)
{
	uint16_t count = 0;
	
	while(1)
	{
		rt_thread_mdelay(100);
		count++;
		if(count==2)		LED_ON(LED1);
		else if(count==4)	LED_ON(LED2);
		else if(count==6)	LED_ON(LED3);
		else if(count==8)	LED_ON(LED4);
		else if(count==13)
		{
			count=0;
			LED_OFF(LED1|LED2|LED3|LED4);
		}
	}
	
}



























