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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
	BEEP_Init();	
	dac_io_Initl();						//��ʼ��DAC
	delay_ms(100);
	dac_output(DAC_CH1,0.00f);			//����DAC1
	dac_output(DAC_CH2,0.00f);			//����DAC2	
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			if(usart_handle(&val,&mode)==0)
			{
				if(mode==0)
				{
					DAC_Coeff = val;
					printf("����У��ϵ��--У��ϵ��:%.4f \r\n",val);
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
					printf("����ͨ��:%d;��ѹֵ:%.4f \r\n",mode,val);
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

//�ַ���תС��
int StringToDouble(char* str, int length, double *val)
{ 
	int i;
	int pointpos=length;	//С����λ��
	int val_temp_int=0;		//��������
	double val_temp_double=0;		//��������
	double val_temp=0;		//��������
	for(i=0;i<length;i++)	//Ѱ��С����
	{
		if( str[i]=='.' )
		{
			if(i==0)
			{
				return -1;		//С���㲻���ٵ�һλ�����ǣ����ش���
			}
			else
			{
				pointpos = i;	//����С����λ��
				break;
			}
		}
	}
	
	for(i=0;i<pointpos;i++)	//��������λ
	{
		val_temp_int = val_temp_int * 10 + (str[i] - '0');
	}
	for(i=length-1;i>pointpos;i--)	//����С��λ
	{
		val_temp_double = (val_temp_double + (str[i] - '0')) * 0.1 ;
	}
	*val = (double)val_temp_int + val_temp_double;
	return 0;
	
}




