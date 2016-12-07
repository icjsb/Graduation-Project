#ifndef __voice_h__
#define __voice_h__

#include"header.h"
#include"main.h"
#include"delay.h"
#include"serial.h"
extern void Uart_SendYuYin(uchar YS,uchar YL,uchar YH);
extern void Voice_Init();
#endif