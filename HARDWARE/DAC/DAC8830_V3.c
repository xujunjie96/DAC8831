

#include "DAC8830_V3.h"

/**********************************************************************
* 名称 : dac_write_reg(unsigned int n_Data)
* 功能 : DAC 写数据函数
* 输入 : n_Data -- 数据
* 输出 ：无
* 说明 : 无
***********************************************************************/
void dac_write_reg(unsigned int n_Data)
{
	dac_Write_Byte(n_Data >> 8);
	dac_Write_Byte(n_Data >> 0);
}
/**********************************************************************
* 名称 : dac_output(unsigned char ch,float Votage)
* 功能 : DAC 电压输出函数
* 输入 : ch -- 通道，Votage -- 电压值
* 输出 ：无

***********************************************************************/
double DAC_Coeff	=	1.050420f;					//校正系数
void dac_output(unsigned char ch,float Votage)
{
	unsigned int REG_Value = 0x00;			//输出寄存器数据

	if(Votage >= 0 && Votage <= DAC_VREF)	//最高输出VREF
	{
		REG_Value = (unsigned int)((float)Votage * CODE_MAX * DAC_Coeff / DAC_VREF);		//测试程序使用的VREF = 5V(REF195G)

		spi_cs_cfg(ch,0);	delay_us(1);	//CS = 0
		
		dac_write_reg(REG_Value);			//写入数据
		
		spi_cs_cfg(ch,1);	delay_us(1);	//CS = 1
	}	
}



