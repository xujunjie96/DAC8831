#ifndef  __DAC8830_V3_H__
#define  __DAC8830_V3_H__

#include "dac_spi.h"
/*****************************��������*********************************/
//1.��׼��ѹ

#define DAC_VREF		5.0f					//5.0V

//2.�������

#define CODE_MAX		0xFFFF					//65536



//3.DACͨ������

#define DAC_CH1			0
#define DAC_CH2			1

/*****************************�ӿں���*********************************/

void dac_output(unsigned char ch,float Votage);	//DAC�������

#endif



