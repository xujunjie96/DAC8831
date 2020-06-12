
#include "dac_spi.h"

/**********************************************************************
* 名称 : dac_io_Initl(void)
* 功能 : DAC端口初始化
* 输入 : 无
* 输出 ：无
* 说明 : 无
***********************************************************************/
void dac_io_Initl(void)
{
#if(SPI_MODE == SW_SPI)								//模拟SPI
	spi_io_Initl();
#elif(SPI_MODE == HW_SPI)							//硬件SPI
	SPI1_Initl();							
#endif		
}
/**********************************************************************
* 名称 : spi_cs_cfg(unsigned char ch,unsigned char Level)
* 功能 : CS片选输出函数
* 输入 : ch -- 通道，Level -- 输出电平0或1
* 输出 ：无
* 说明 : 无
***********************************************************************/
void spi_cs_cfg(unsigned char ch,unsigned char Level)
{
#if(SPI_MODE == SW_SPI)								//模拟SPI
	if(ch == DAC_CH1)
		CS1 = Level;
	else 
		CS2 = Level;
#elif(SPI_MODE == HW_SPI)							//硬件SPI	 
	if(ch == DAC_CH1)
		SPI1_CS1 = Level;
	else 
		SPI1_CS2 = Level;
#endif
}
/**********************************************************************
* 名称 : dac_Write_Byte(unsigned char _1Byte)
* 功能 : 单字节写函数
* 输入 : _1Byte -- 单字节数据
* 输出 ：无
* 说明 : 无
***********************************************************************/
void dac_Write_Byte(unsigned char _1Byte)
{
#if(SPI_MODE == SW_SPI)								//模拟SPI
	spi_Write_Byte(_1Byte);
#elif(SPI_MODE == HW_SPI)							//硬件SPI
	SPI1_ReadWriteByte(_1Byte);
#endif
}


