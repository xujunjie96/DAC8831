

#include "F40x_SPI1.h"

/**********************************************************************
* 名称 : SPI1_Initl(void)
* 功能 : SPI1初始化函数(主机模式)
* 输入 : 无
* 输出 ：无
* 说明 : SPI配置成主机模式 	
***********************************************************************/
void SPI1_Initl(void)
{	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA				//使能GPIO时钟
						 | RCC_AHB1Periph_GPIOB
						 | RCC_AHB1Periph_GPIOC
						 | RCC_AHB1Periph_GPIOD
						 | RCC_AHB1Periph_GPIOE
						 | RCC_AHB1Periph_GPIOF
						 | RCC_AHB1Periph_GPIOG
						 | RCC_AHB1Periph_GPIOH
						 | RCC_AHB1Periph_GPIOI,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//使能SPI1时钟

	//1.GPIOFB3,4,5初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3				//PB3 -- SCK
								| GPIO_Pin_4				//PB4 -- SDO
								| GPIO_Pin_5;				//PB5 -- SDI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//初始化

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1); 	//PB3复用为 SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1); 	//PB4复用为 SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1); 	//PB5复用为 SPI1

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14				//PG14 -- CS2
								| GPIO_Pin_15;				//PG15 -- CS1		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽式输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_Init(GPIOG, &GPIO_InitStructure);					//初始化		

	//2.初始化GPI1
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);		//复位SPI1
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);	//停止复位SPI1

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				//串行同步时钟的空闲状态为低电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;			//串行同步时钟的第一个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;				//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;				//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure); 				 	//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

	SPI_Cmd(SPI1, ENABLE); 									//使能SPI外设

	SPI1_ReadWriteByte(0xff);								//启动传输		 
}   
/**********************************************************************
* 名称 : PI1_SetSpeed(u8 SPI_BaudRatePrescaler)
* 功能 : SPI1速度设置函数
* 输入 : SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
* 输出 ：无
* 说明 : SPI速度=fAPB2/分频系数
		 fAPB2时钟一般为84Mhz：
***********************************************************************/
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI1->CR1&=0XFFC7;										//位3-5清零，用来设置波特率
	SPI1->CR1|=SPI_BaudRatePrescaler;						//设置SPI1速度 
	SPI_Cmd(SPI1,ENABLE); 									//使能SPI1
} 
/**********************************************************************
* 名称 : SPI1_ReadWriteByte(u8 TxData)
* 功能 : SPI1读写一个字节
* 输入 : TxData -- 写入数据
* 输出 ：读取到的数据
* 说明 : 无
***********************************************************************/
u8 SPI1_ReadWriteByte(u8 TxData)
{		 			 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  
		SPI_I2S_SendData(SPI1, TxData); 					//通过外设SPIx发送一个byte  数据	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  

	return SPI_I2S_ReceiveData(SPI1); 						//返回通过SPIx最近接收的数据	 		    
}




