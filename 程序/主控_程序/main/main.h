#ifndef __main_h__
#define __main_h__
#include"stc12c5axx.h"
#include"header.h"

/*MP3和蓝牙串口通道控制*/
sbit Re_A = P1^4;  
sbit Re_B = P1^5;

/********************************************/
/* Re_A = 1; Re_B = 0; 时选择为蓝牙连接
/* Re_A = 1; Re_B = 1; 时选择为MP3连接 
/********************************************/
#define En_Blu {Re_B = 0;Re_A = 1;}/*开启蓝牙通道*/
#define En_Mp3 {Re_B = 1;Re_A = 1;}/*开启MP3通道*/

static uchar Recv_buf[10] = {0} ;/*发送数组*/
static uchar Send_buf[10] = {0} ;/*接收数组*/


extern uchar mode;
extern uchar flag ;
#endif