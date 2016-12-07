#ifndef __serial_h__
#define __serial_h__

#include"header.h"
#include"stc12c5axx.h"

/*串口2宏定义*/
#define S2RI 0x01	//串口2接收中断请求标志位
#define S2TI 0x02	//串口2发送中断请求标志位
extern void UartInit();
extern void UART_2SendOneByte(uchar c);
extern void UART_1SendOneByte(uchar c);
#endif