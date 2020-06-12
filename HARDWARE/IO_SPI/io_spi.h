#ifndef  __IO_SPI_H__
#define  __IO_SPI_H__

#include "delay.h"
/*****************************�˿ڶ���*********************************/
//1.�˿ڶ���

#define 	CS1			PGout(15)				//Ƭѡ1
#define 	CS2			PGout(14)				//Ƭѡ2
#define 	SCK			PBout(3)				//ʱ��
#define 	SDI			PBout(5)				//����
#define 	SDO			PBin(4)					//���

/*****************************�ӿں���*********************************/

void spi_io_Initl(void);						//��ʼ��SPI�˿ڵ�ƽ	
void spi_Write_Byte(unsigned char _1Byte);		//���ֽ�д����
unsigned char spi_Read_Byte(void);				//���ֽڶ�����

#endif


