#ifndef __key_h__
#define __key_h__

#include"header.h"
#include"mp3.h"
#include"delay.h"
#include"voice.h"
/*定义两个按键*/
sbit Key_1 = P2^6;
sbit Key_2 = P2^5;


extern void Scankey();
#endif