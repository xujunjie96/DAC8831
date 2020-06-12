
#include "dac_spi.h"

/**********************************************************************
* ���� : dac_io_Initl(void)
* ���� : DAC�˿ڳ�ʼ��
* ���� : ��
* ��� ����
* ˵�� : ��
***********************************************************************/
void dac_io_Initl(void)
{
#if(SPI_MODE == SW_SPI)								//ģ��SPI
	spi_io_Initl();
#elif(SPI_MODE == HW_SPI)							//Ӳ��SPI
	SPI1_Initl();							
#endif		
}
/**********************************************************************
* ���� : spi_cs_cfg(unsigned char ch,unsigned char Level)
* ���� : CSƬѡ�������
* ���� : ch -- ͨ����Level -- �����ƽ0��1
* ��� ����
* ˵�� : ��
***********************************************************************/
void spi_cs_cfg(unsigned char ch,unsigned char Level)
{
#if(SPI_MODE == SW_SPI)								//ģ��SPI
	if(ch == DAC_CH1)
		CS1 = Level;
	else 
		CS2 = Level;
#elif(SPI_MODE == HW_SPI)							//Ӳ��SPI	 
	if(ch == DAC_CH1)
		SPI1_CS1 = Level;
	else 
		SPI1_CS2 = Level;
#endif
}
/**********************************************************************
* ���� : dac_Write_Byte(unsigned char _1Byte)
* ���� : ���ֽ�д����
* ���� : _1Byte -- ���ֽ�����
* ��� ����
* ˵�� : ��
***********************************************************************/
void dac_Write_Byte(unsigned char _1Byte)
{
#if(SPI_MODE == SW_SPI)								//ģ��SPI
	spi_Write_Byte(_1Byte);
#elif(SPI_MODE == HW_SPI)							//Ӳ��SPI
	SPI1_ReadWriteByte(_1Byte);
#endif
}


