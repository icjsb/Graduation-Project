#include"blueteeth.h"

/*****************************************************************************************************
 - 功能描述： 串口2、蓝牙发送一帧数据
 - 隶属模块： 内部 
 - 参数说明： 
 - 返回说明： 
 - 注：无     
*****************************************************************************************************/
void SendBlue(uchar len)
{
    uchar i = 0 ;	
    for(i=0; i<len; i++)		/*数据*/
    {
		UART_2SendOneByte(Send_buf[i]) ;
    }
}


/********************************************************************************************
 - 功能描述： 串口2向外发送命令[包括控制和查询](蓝牙模块使用)
 - 隶属模块： 外部
 - 参数说明： 

 - 返回说明：
 - 注：       
********************************************************************************************/
void Uart_SendBlue(uchar dat1 ,uchar dat2 , uchar dat3)
{
	Send_buf[0] = 0x55;		 /*起始:U */
	Send_buf[1] = 0x53;		 /*起始:S */
    Send_buf[2] = dat1;    //
    Send_buf[3] = dat2;    //
    Send_buf[4] = dat3;    //
	Send_buf[5] = 0x7e;      /*结束:~ */
	Send_buf[6] = 0x66;     /*结束:f */
    SendBlue(7);            /*发送此帧数据*/
}
