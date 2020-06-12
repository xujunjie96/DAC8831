#ifndef  __IO_SPI_H__
#define  __IO_SPI_H__

#include "delay.h"
/*****************************端口定义*********************************/
//1.端口定义

#define 	CS1			PGout(15)				//片选1
#define 	CS2			PGout(14)				//片选2
#define 	SCK			PBout(3)				//时钟
#define 	SDI			PBout(5)				//输入
#define 	SDO			PBin(4)					//输出

/*****************************接口函数*********************************/

void spi_io_Initl(void);						//初始化SPI端口电平	
void spi_Write_Byte(unsigned char _1Byte);		//单字节写函数
unsigned char spi_Read_Byte(void);				//单字节读函数

#endif


