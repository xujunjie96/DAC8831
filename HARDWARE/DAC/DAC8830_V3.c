

#include "DAC8830_V3.h"

/**********************************************************************
* ���� : dac_write_reg(unsigned int n_Data)
* ���� : DAC д���ݺ���
* ���� : n_Data -- ����
* ��� ����
* ˵�� : ��
***********************************************************************/
void dac_write_reg(unsigned int n_Data)
{
	dac_Write_Byte(n_Data >> 8);
	dac_Write_Byte(n_Data >> 0);
}
/**********************************************************************
* ���� : dac_output(unsigned char ch,float Votage)
* ���� : DAC ��ѹ�������
* ���� : ch -- ͨ����Votage -- ��ѹֵ
* ��� ����

***********************************************************************/
double DAC_Coeff	=	1.050420f;					//У��ϵ��
void dac_output(unsigned char ch,float Votage)
{
	unsigned int REG_Value = 0x00;			//����Ĵ�������

	if(Votage >= 0 && Votage <= DAC_VREF)	//������VREF
	{
		REG_Value = (unsigned int)((float)Votage * CODE_MAX * DAC_Coeff / DAC_VREF);		//���Գ���ʹ�õ�VREF = 5V(REF195G)

		spi_cs_cfg(ch,0);	delay_us(1);	//CS = 0
		
		dac_write_reg(REG_Value);			//д������
		
		spi_cs_cfg(ch,1);	delay_us(1);	//CS = 1
	}	
}



