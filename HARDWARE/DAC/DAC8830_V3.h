#ifndef  __DAC8830_V3_H__
#define  __DAC8830_V3_H__

#include "dac_spi.h"
/*****************************参数定义*********************************/
//1.基准电压

#define DAC_VREF		5.0f					//5.0V

//2.输出参数

#define CODE_MAX		0xFFFF					//65536



//3.DAC通道定义

#define DAC_CH1			0
#define DAC_CH2			1

/*****************************接口函数*********************************/

void dac_output(unsigned char ch,float Votage);	//DAC输出函数

#endif



