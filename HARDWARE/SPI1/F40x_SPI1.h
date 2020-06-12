#ifndef  __F40X_SPI1_H__
#define  __F40X_SPI1_H__

#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "Delay.h"
/****************************���Ŷ���*********************************/
//1.SPI2���Ŷ���

#define SPI1_CS1	PGout(15)					//SPIƬѡ1
#define SPI1_CS2	PGout(14)					//SPIƬѡ2

/*****************************�ӿں���*********************************/

void SPI1_Initl(void);							//SPI��ʼ��
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);	//SPI�ٶ�����
u8 SPI1_ReadWriteByte(u8 TxData);				//���ֽڶ�д����

#endif


