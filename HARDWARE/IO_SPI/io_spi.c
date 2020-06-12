/**********************************************************************	 
* ��˾���� : ����ϵ�·������޹�˾
* ģ������ ��IOģ��SPI
* ϵͳ��Ƶ : 168 MHz
* ������   : eysmcu
* �޸���   : eysmcu 
* �������� : 2020��3��14��
* �Ա���ַ : http://mindesigner.taobao.com
* �Ա�ID�� : eysmcu
* ����汾 : Keil UV5 14.0.0

						  ��Ȩ���� @ �����
***********************************************************************/

#include "io_spi.h"

/**********************************************************************
* ���� : spi_io_Initl(void)
* ���� : SPI�˿ڳ�ʼ��
* ���� : ��
* ��� ����
* ˵�� : ��
***********************************************************************/
void spi_io_Initl(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	//1.ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA			//ʹ��GPIOʱ��
						 | RCC_AHB1Periph_GPIOB
						 | RCC_AHB1Periph_GPIOC
						 | RCC_AHB1Periph_GPIOD
						 | RCC_AHB1Periph_GPIOE
						 | RCC_AHB1Periph_GPIOF
						 | RCC_AHB1Periph_GPIOG
						 | RCC_AHB1Periph_GPIOH
						 | RCC_AHB1Periph_GPIOI,ENABLE); 
	
	//2.����˿ڶ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3			//PB3 -- SCK
								| GPIO_Pin_5;			//PB5 -- SDI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//����ʽ���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ��	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14			//PG14 -- CS2
								| GPIO_Pin_15;			//PG15 -- CS1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//����ʽ���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOG, &GPIO_InitStructure);				//��ʼ��	
	
	//3.����˿ڶ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;			//PB4 -- SDO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ��		
	
	//3.���ö˿ڳ�ʼ��ƽ
	CS1 = 1;CS2 = 1;	
	SCK = 0;											//����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ	
	SDI = 1;
}
/**********************************************************************
* ���� : spi_Write_Byte(unsigned char _1Byte)
* ���� : ���ֽ�д����
* ���� : _1Byte -- ���ֽ�����
* ��� ����
* ˵�� : ��
***********************************************************************/
void spi_Write_Byte(unsigned char _1Byte)
{
	unsigned char x = 0x00;
	SCK = 0;										//SCK = 0
	for(x = 0;x < 8;x ++)
	{
		if((_1Byte & 0x80) == 0x80)					
			SDI = 1;								//SDI = 1
		else SDI = 0;								//SDI = 0
		
		SCK = 1;			delay_us(1);			//SCK = 1
		SCK = 0;			delay_us(1);			//SCK = 0
		_1Byte = _1Byte << 1;	
	}	
}
/**********************************************************************
* ���� : spi_Read_Byte(void)
* ���� : ���ֽڶ�����
* ���� : ��
* ��� ��_1Byte -- ����
* ˵�� : ��
***********************************************************************/
unsigned char spi_Read_Byte(void)
{
	unsigned char _1Byte = 0x00,x = 0x00;
	SCK = 0;										//SCK = 0
	for(x = 0;x < 8;x ++)
	{
		_1Byte = _1Byte << 1;
		SCK = 1;			delay_us(1);			//SCK = 1
		if(SDO == 1)								//SDO = 1
			 _1Byte = _1Byte + 0x01;
		else _1Byte = _1Byte & 0xFE;				//SDO = 0
		SCK = 0;			delay_us(1);			//SCK = 0		
	}
	return(_1Byte);									//����ֵ
}
	





