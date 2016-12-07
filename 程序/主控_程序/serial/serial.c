#include"serial.h"
/****************串行口1发送****************/
void UART_1SendOneByte(uchar c)
{
    SBUF = c;
    while(!TI);	   		/*若TI=0，在此等待*/
    TI = 0;	 
}

/****************串行口2发送****************/
void UART_2SendOneByte(uchar c)
{
	S2BUF = c;
    while(!(S2CON&S2TI));   /*若S2TI=0，在此等待*/
    S2CON&=~S2TI;	  		/*S2TI=0*/
}

void UartInit()		
{						
						//串口一19200bps@22.1184MHz
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率  10位UART可变
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xDC;			//设定定时初值
	TH1 = 0xDC;			//设定定时器重装值
	ET1 = 0;			//禁止定时器1中断
	TR1 = 1;			//启动定时器1

						//串口二9600bps@22.1184MHz
	AUXR &= 0xF7;		//波特率不倍速
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0xB8;			//设定独立波特率发生器重装值
	AUXR |= 0x10;		//启动独立波特率发生器
	
	EA = 1;				//开总中断
	ES = 1;   			//开串口中断
	REN = 1;			//接收数据
}
