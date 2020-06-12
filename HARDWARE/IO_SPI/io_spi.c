/**********************************************************************	 
* 公司名称 : 麦恩迪电路设计有限公司
* 模块名称 ：IO模拟SPI
* 系统主频 : 168 MHz
* 创建人   : eysmcu
* 修改人   : eysmcu 
* 创建日期 : 2020年3月14日
* 淘宝网址 : http://mindesigner.taobao.com
* 淘宝ID号 : eysmcu
* 软件版本 : Keil UV5 14.0.0

						  版权所有 @ 麦恩迪
***********************************************************************/

#include "io_spi.h"

/**********************************************************************
* 名称 : spi_io_Initl(void)
* 功能 : SPI端口初始化
* 输入 : 无
* 输出 ：无
* 说明 : 无
***********************************************************************/
void spi_io_Initl(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	//1.时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA			//使能GPIO时钟
						 | RCC_AHB1Periph_GPIOB
						 | RCC_AHB1Periph_GPIOC
						 | RCC_AHB1Periph_GPIOD
						 | RCC_AHB1Periph_GPIOE
						 | RCC_AHB1Periph_GPIOF
						 | RCC_AHB1Periph_GPIOG
						 | RCC_AHB1Periph_GPIOH
						 | RCC_AHB1Periph_GPIOI,ENABLE); 
	
	//2.输出端口定义
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3			//PB3 -- SCK
								| GPIO_Pin_5;			//PB5 -- SDI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽式输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//初始化	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14			//PG14 -- CS2
								| GPIO_Pin_15;			//PG15 -- CS1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽式输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOG, &GPIO_InitStructure);				//初始化	
	
	//3.输入端口定义
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;			//PB4 -- SDO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//初始化		
	
	//3.设置端口初始电平
	CS1 = 1;CS2 = 1;	
	SCK = 0;											//串行同步时钟的空闲状态为低电平	
	SDI = 1;
}
/**********************************************************************
* 名称 : spi_Write_Byte(unsigned char _1Byte)
* 功能 : 单字节写函数
* 输入 : _1Byte -- 单字节数据
* 输出 ：无
* 说明 : 无
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
* 名称 : spi_Read_Byte(void)
* 功能 : 单字节读函数
* 输入 : 无
* 输出 ：_1Byte -- 数据
* 说明 : 无
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
	return(_1Byte);									//返回值
}
	





