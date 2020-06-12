#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "DAC8830_V3.h"

extern double DAC_Coeff;
int StringToDouble(char* str, int length, double *val);
int usart_handle(double * val,int* mode);
int main(void)
{ 
 
	u8 t;
	u8 len;	
	u16 times=0;  
	double val=0;
	int mode=3;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口 
	BEEP_Init();	
	dac_io_Initl();						//初始化DAC
	delay_ms(100);
	dac_output(DAC_CH1,0.00f);			//测试DAC1
	dac_output(DAC_CH2,0.00f);			//测试DAC2	
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			if(usart_handle(&val,&mode)==0)
			{
				if(mode==0)
				{
					DAC_Coeff = val;
					printf("设置校正系数--校正系数:%.4f \r\n",val);
					BEEP=1;
					delay_ms(50);
					BEEP=0;
					delay_ms(50);
					BEEP=1;
					delay_ms(50);
					BEEP=0;
				}
				else
				{
					if(mode==1)
					{
						dac_output(DAC_CH1,val);			
						dac_output(DAC_CH2,0.0f);			
						LED0=0;
						LED1=1;
					}
					else
					{
						dac_output(DAC_CH2,val);			
						dac_output(DAC_CH1,0.0f);		
						LED0=1;
						LED1=0;						
					}
					printf("设置通道:%d;电压值:%.4f \r\n",mode,val);
				}
			}
		}
	}
}

int usart_handle(double * val,int* mode)
{
	
	u8 len;	
//	double val=0;
	if(USART_RX_STA&0x8000)
		{			
			len=USART_RX_STA&0x3fff;
			
			if(USART_RX_BUF[0]=='$')
				{
						if(USART_RX_BUF[1]=='+')
						{
							StringToDouble(&USART_RX_BUF[2],len-2,val);
							*mode=1;
						}
						else if(USART_RX_BUF[1]=='-')
						{
							StringToDouble(&USART_RX_BUF[2],len-2,val);
							*mode=2;
						}
						else if(USART_RX_BUF[1]=='/')
						{
							StringToDouble(&USART_RX_BUF[2],len-2,val);
							*mode=0;
						}
						else
						{
							USART_RX_STA=0;
							return -2;
						}							
				}
			else
			{
				USART_RX_STA=0;
				return -1;
			}
				
			//	StringToDouble(USART_RX_BUF,len,val);	
					USART_RX_STA=0;
		}
			
				 
			return 0;
			
}

//字符串转小数
int StringToDouble(char* str, int length, double *val)
{ 
	int i;
	int pointpos=length;	//小数点位置
	int val_temp_int=0;		//整数部分
	double val_temp_double=0;		//整数部分
	double val_temp=0;		//整数部分
	for(i=0;i<length;i++)	//寻找小数点
	{
		if( str[i]=='.' )
		{
			if(i==0)
			{
				return -1;		//小数点不能再第一位，若是，返回错误
			}
			else
			{
				pointpos = i;	//设置小数点位置
				break;
			}
		}
	}
	
	for(i=0;i<pointpos;i++)	//计算整数位
	{
		val_temp_int = val_temp_int * 10 + (str[i] - '0');
	}
	for(i=length-1;i>pointpos;i--)	//计算小数位
	{
		val_temp_double = (val_temp_double + (str[i] - '0')) * 0.1 ;
	}
	*val = (double)val_temp_int + val_temp_double;
	return 0;
	
}




