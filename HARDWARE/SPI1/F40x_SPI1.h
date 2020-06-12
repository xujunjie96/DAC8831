#ifndef  __F40X_SPI1_H__
#define  __F40X_SPI1_H__

#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "Delay.h"
/****************************引脚定义*********************************/
//1.SPI2引脚定义

#define SPI1_CS1	PGout(15)					//SPI片选1
#define SPI1_CS2	PGout(14)					//SPI片选2

/*****************************接口函数*********************************/

void SPI1_Initl(void);							//SPI初始化
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);	//SPI速度设置
u8 SPI1_ReadWriteByte(u8 TxData);				//单字节读写函数

#endif


