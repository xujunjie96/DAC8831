#ifndef  __DAC_SPI_H__
#define  __DAC_SPI_H__

#include "io_spi.h"							//ģ��SPI
#include "F40x_SPI1.h"						//Ӳ��SPI1
#include "DAC8830_V3.h"
/****************************�ӿڶ���*********************************/
//1.SPI�ӿڶ���

#define SW_SPI		0						//ģ��SPI
#define HW_SPI		1						//Ӳ��SPI

#define SPI_MODE	HW_SPI	

/*****************************�ӿں���*********************************/

void dac_io_Initl(void);					//�˿ڳ�ʼ��
void spi_cs_cfg(unsigned char ch,unsigned char Level);		//Ƭѡ���
void dac_Write_Byte(unsigned char _1Byte);	//���ֽ�д����

#endif


