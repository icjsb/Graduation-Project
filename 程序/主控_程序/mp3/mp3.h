#ifndef __mp3_h__
#define __mp3_h__

#include"header.h"
#include"main.h"
#include"serial.h"
/*MP3判忙标志位，默认高电平，忙时输出低电平*/
sbit busy = P1^0;

extern void Uart_SendCMD(uchar CMD ,uchar feedback , uchar dath , uchar datl);
#endif