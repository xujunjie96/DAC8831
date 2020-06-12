#ifndef  __DAC_SPI_H__
#define  __DAC_SPI_H__

#include "io_spi.h"							//模拟SPI
#include "F40x_SPI1.h"						//硬件SPI1
#include "DAC8830_V3.h"
/****************************接口定义*********************************/
//1.SPI接口定义

#define SW_SPI		0						//模拟SPI
#define HW_SPI		1						//硬件SPI

#define SPI_MODE	HW_SPI	

/*****************************接口函数*********************************/

void dac_io_Initl(void);					//端口初始化
void spi_cs_cfg(unsigned char ch,unsigned char Level);		//片选输出
void dac_Write_Byte(unsigned char _1Byte);	//单字节写函数

#endif


