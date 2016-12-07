#include"stc12c5axx.h"
#include"intrins.h"
#include"delay.h"
#include"main.h"
#include"header.h"
#include"mp3.h"
#include"key.h"
#include"voice.h"
#include"blueteeth.h"
#include"serial.h"
#include"ds3231.h"

/*语音识别返回值标志位：flag，模式切换标志位：mode*/
uchar flag ,mode;

/*****************主函数******************/
void main()
{
	uchar cache,poem,song,c;
	c=0;/*陈奕迅歌曲*/
	poem = 17;/*古诗*/
	song = 41;/*歌曲*/
	En_Mp3;
	busy = 1;   						/*MP3判忙标志位置高电平*/
	mode = 0;
    UartInit();							/*串行口初始化*/
	delay200ms();
	delay200ms();
	delay200ms();
	Uart_SendCMD(0x06,0x00,0x00,0x0e);	/*设置MP3音量为9*/
	delay50ms();
	Uart_SendCMD(0x0f,0x00,0x02,0x01);	/*播放语音*/
	Voice_Init();
	Uart_SendYuYin(0xa9,0x01,0x00);		/*配置识别组*/
	delay800ms();
	while(!busy);
	Uart_SendYuYin(0xaa,0x00,0x00);		/*识别开始*/
	while(1)
	{
		Scankey();
		switch(mode)
		{
			case 0:
					if(flag==1)
					{
						flag = 0; 
					
						if(Recv_buf[1]	== 0x00 )/*识别为001组001号：你好*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x04);/*你好呀*/ 
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x01 )/*识别为001组002号：你叫什么名字*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x0c);/*我叫小溪*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x02 )/*识别为001组003号：你的主人是谁*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x0d);/*我的主人是马攀*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x03 )/*识别为001组004号：你是谁*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x01);/*我是智能家居助手小溪*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x04 )/*识别为001组005号：你太傻了*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x06);/*你说什么我没带眼镜听不清*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x05 )/*识别为001组006号：1+1等于几*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x0e);/*一加一等于二*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x06 )/*识别为001组007号：你几岁了*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x05);/*我今年一岁了*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x07 )/*识别为001组008号：你家在哪里*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x08);/*我来自郑州大学西亚斯国际学院*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x08 )/*识别为001组009号：你很聪明呀*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x0b);/*我也这么觉得*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x09)/*识别为001组010号：你会游泳吗*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x0a);/*我当然会游泳啦*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x0a)/*识别为001组011号：我要拆了你*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x06);/*你说什么我没戴眼镜听不清*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if((Recv_buf[1] == 0x0b)||(Recv_buf[1] == 37)||(Recv_buf[1] == 53))/*识别为001组012号：唱首歌吧*/
						{
							if(song>52)
								song=41;
							Uart_SendCMD(0x0f,0x00,0x02,song);/*歌曲*/
							song++;
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1] == 38)/*识别为薛之谦*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,50);/*演员*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1] == 39)/*识别为王力宏*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,44);/*大城小爱*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1] == 40)/*识别为林俊杰*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,42);/*小酒窝*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1] == 41)/*识别为李荣浩*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,45);/*李白*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 42 )/*识别为苏打绿*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,47);/*小情歌*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	==  43)/*识别为陈奕迅*/
						{
							c++;
							if(c%2 == 1)
							{
								Uart_SendCMD(0x0f,0x00,0x02,41);/*红玫瑰*/
							}
							if(c%2 == 0)
							{
								Uart_SendCMD(0x0f,0x00,0x02,48);/*十年*/
							}
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	==  44)/*识别为至少还有你*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,51);/*至少还有你*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	==  45)/*识别为会呼吸的痛*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,52);/*会呼吸的痛*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	==  46)/*识别为红玫瑰*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,41);/*红玫瑰*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	==  47)/*识别为小酒窝*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,42);/*小酒窝*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 48 )/*识别为时间都去哪了*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,43);/*时间都去哪了*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 49 )/*识别为大城小爱*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,44);/*大城小爱*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 50 )/*识别为演员*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,50);/*演员*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 51 )/*识别为童话*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,46);/*童话*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if((Recv_buf[1] == 14)||(Recv_buf[1] == 15)||(Recv_buf[1] == 23))/*识别为现在几点了*/
						{
							mode = 2;
						}
						
						
						
						if(Recv_buf[1]	== 0x0c)/*识别为001组013号：说话小点声*/
						{
							Uart_SendCMD(0x06,0x00,0x00,0x0a);
							delay50ms();
							Uart_SendCMD(0x0f,0x00,0x02,0x07);/*好的主人*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x0d)/*识别为001组014号：说话大点声*/
						{
							Uart_SendCMD(0x06,0x00,0x00,0x12);/*设置音量为20*/
							delay50ms();
							Uart_SendCMD(0x0f,0x00,0x02,0x07);/*好的主人*/
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if((Recv_buf[1]	== 0x10)||(Recv_buf[1]	== 52))/*识别为001组017号：背首古诗*/
						{
							if(poem>34)
								poem = 17;
							Uart_SendCMD(0x0f,0x00,0x02,poem);/*背古诗*/
							poem++;
							delay800ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						/**/
						if(Recv_buf[1]	== 0x11)/*识别为001组018号：打开台灯*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x03);/*台灯已打开*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x31,0x31,0x33);/*打开台灯*/
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x12)/*识别为001组019号：打开风扇*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x01);/*风扇已打开*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x31,0x31,0x32);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x1b)/*识别为001组028号：打开红灯*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x0d);/*红灯已打开*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x31,0x31,0x38);/*打开红灯*/
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x1d)/*识别为001组030号：打开绿灯*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x0b);/*绿灯已打开*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x31,0x31,0x37);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x1c)/*识别为001组029号：打开蓝灯*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x09);/*好的主人*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x31,0x31,0x36);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x24)/*识别为001组037号：打开电视*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x05);/*好的主人*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x31,0x31,0x34);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x21)/*识别为001组034号：打开热水器*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x07);/*热水器已打开*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x31,0x31,0x35);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						/**/
						if(Recv_buf[1]	== 0x1a)/*识别为001组027号：关闭台灯*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x04);/*台灯已关闭*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x30,0x31,0x33);/*关闭台灯*/
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x19)/*识别为001组026号：关闭风扇*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x02);/*风扇已关闭*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x30,0x31,0x32);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x1e)/*识别为001组031号：关闭红灯*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x0e);/*红灯已关闭*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x30,0x31,0x38);/*关闭红灯*/
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x20)/*识别为001组033号：关闭绿灯*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x0c);/*绿灯已关闭*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x30,0x31,0x37);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x1f)/*识别为001组032号：关闭蓝灯*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x0a);/*蓝灯已关闭*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x30,0x31,0x36);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
						if(Recv_buf[1]	== 0x23)/*识别为001组036号：关闭电视*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x06);/*电视已关闭*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x30,0x31,0x34);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						if(Recv_buf[1]	== 0x22)/*识别为001组035号：关闭热水器*/
						{
							Uart_SendCMD(0x0f,0x00,0x05,0x08);/*热水器已关闭*/
							delay800ms();
							En_Blu;
							delay50ms();
							Uart_SendBlue(0x30,0x31,0x35);
							En_Mp3;
							delay50ms();
							while(!busy);
							flag = 0; 
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						else
						{
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}

					}break;
						
			case 1:/*口令模式*/
					if(flag==1)
					{
						flag = 0; 
					
						if(Recv_buf[1]	== 0x18 )/*识别为天王盖地虎*/
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x27);/*煎饼两块五*/ 
							delay800ms();
							while(!busy);
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
							while(1)
							{
								if(flag==1)
								{
									flag = 0; 
								
									if(Recv_buf[1]	== 0x00 )/*识别为001组001号：你好*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x04);/*你好呀*/ 
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x01 )/*识别为001组002号：你叫什么名字*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x0c);/*我叫小溪*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x02 )/*识别为001组003号：你的主人是谁*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x0d);/*我的主人是马攀*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x03 )/*识别为001组004号：你是谁*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x01);/*我是智能家居助手小溪*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x04 )/*识别为001组005号：你太傻了*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x06);/*你说什么我没带眼镜听不清*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x05 )/*识别为001组006号：1+1等于几*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x0e);/*一加一等于二*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x06 )/*识别为001组007号：你几岁了*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x05);/*我今年一岁了*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x07 )/*识别为001组008号：你家在哪里*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x08);/*我来自郑州大学西亚斯国际学院*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x08 )/*识别为001组009号：你很聪明呀*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x0b);/*我也这么觉得*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x09)/*识别为001组010号：你会游泳吗*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x0a);/*我当然会游泳啦*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x0a)/*识别为001组011号：我要拆了你*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x06);/*我当然会游泳啦*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x0b)/*识别为001组012号：唱首歌吧*/
									{
										Uart_SendCMD(0x0f,0x00,0x02,0x26);/*小螺号*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x0c)/*识别为001组013号：说话小点声*/
									{
										Uart_SendCMD(0x06,0x00,0x00,0x0a);
										delay50ms();
										Uart_SendCMD(0x0f,0x00,0x02,0x07);/*好的主人*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x0d)/*识别为001组014号：说话大点声*/
									{
										Uart_SendCMD(0x06,0x00,0x00,0x12);/*设置音量为20*/
										delay50ms();
										Uart_SendCMD(0x0f,0x00,0x02,0x07);/*好的主人*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x10)/*识别为001组017号：背首诗歌*/
									{
										poem++;
										if(poem>34)
											poem = 17;
										Uart_SendCMD(0x0f,0x00,0x02,poem);/*好的主人*/
										delay800ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									/**/
									if(Recv_buf[1]	== 0x11)/*识别为001组018号：打开台灯*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x03);/*台灯已打开*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x31,0x31,0x33);/*打开台灯*/
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x12)/*识别为001组019号：打开风扇*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x01);/*风扇已打开*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x31,0x31,0x32);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x1b)/*识别为001组028号：打开红灯*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x0d);/*红灯已打开*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x31,0x31,0x38);/*打开红灯*/
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x1d)/*识别为001组030号：打开绿灯*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x0b);/*绿灯已打开*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x31,0x31,0x37);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x1c)/*识别为001组029号：打开蓝灯*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x09);/*好的主人*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x31,0x31,0x36);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x24)/*识别为001组037号：打开电视*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x05);/*好的主人*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x31,0x31,0x34);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x21)/*识别为001组034号：打开热水器*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x07);/*热水器已打开*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x31,0x31,0x35);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									/**/
									if(Recv_buf[1]	== 0x1a)/*识别为001组027号：关闭台灯*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x04);/*台灯已关闭*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x30,0x31,0x33);/*关闭台灯*/
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x19)/*识别为001组026号：关闭风扇*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x02);/*风扇已关闭*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x30,0x31,0x32);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x1e)/*识别为001组031号：关闭红灯*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x0e);/*红灯已关闭*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x30,0x31,0x38);/*关闭红灯*/
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x20)/*识别为001组033号：关闭绿灯*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x0c);/*绿灯已关闭*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x30,0x31,0x37);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x1f)/*识别为001组032号：关闭蓝灯*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x0a);/*蓝灯已关闭*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x30,0x31,0x36);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									
									if(Recv_buf[1]	== 0x23)/*识别为001组036号：关闭电视*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x06);/*电视已关闭*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x30,0x31,0x34);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
									if(Recv_buf[1]	== 0x22)/*识别为001组035号：关闭热水器*/
									{
										Uart_SendCMD(0x0f,0x00,0x05,0x08);/*热水器已关闭*/
										delay800ms();
										En_Blu;
										delay50ms();
										Uart_SendBlue(0x30,0x31,0x35);
										En_Mp3;
										delay50ms();
										while(!busy);
										flag = 0; 
										Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
										break;
									}
																	
									else
										break;

								}
							}
							
						}
						else
						{
							Uart_SendCMD(0x0f,0x00,0x02,0x28);/*请说出正确口令*/ 
							delay800ms();
							while(!busy);
							Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
						}
						
					}
					break;

			case 2:/*语音报时模式*/
				{
					cache = BCD2HEX(read_random(0x06));
					Uart_SendCMD(0x0f,0x00,0x06,cache);/*年份*/
					delay800ms();
					cache = BCD2HEX(read_random(0x05));
					while(!busy);
			
					
					Uart_SendCMD(0x0f,0x00,0x08,cache);/*月份*/
					delay800ms();
					cache = BCD2HEX(read_random(0x04));
					while(!busy);
			
					
					Uart_SendCMD(0x0f,0x00,0x09,cache);/*日期*/
					delay800ms();
					cache = BCD2HEX(read_random(0x03));
					while(!busy);
			
					
					Uart_SendCMD(0x0f,0x00,0x07,cache);/*星期*/
					delay800ms();
					cache = BCD2HEX(read_random(0x02));
					if(cache == 0)cache = 24;/*0点即是24点*/
					while(!busy);
			
					
					Uart_SendCMD(0x0f,0x00,0x0a,cache);/*小时*/
					delay800ms();
					cache = BCD2HEX(read_random(0x01));
					if(cache == 0)cache = 60;/*零分即是整点*/
					while(!busy);
			
					
					Uart_SendCMD(0x0f,0x00,0x0b,cache);/*分钟*/
					delay800ms();
					while(!busy);
					
					Uart_SendCMD(0x0f,0x00,0x01,0xa9);/*温度*/
					delay800ms();
					cache = read_random(0x11);
					while(!busy);
					
					if(cache>127)
					{
						Uart_SendCMD(0x0f,0x00,0x01,0xb4);/*零下*/
						delay800ms();
						while(!busy);
						Uart_SendCMD(0x0f,0x00,0x01,(~cache+1));/*温度*/
						delay800ms();
						while(!busy);
					}
					else
					{
						Uart_SendCMD(0x0f,0x00,0x01,cache);/*温度*/
						delay800ms();
						while(!busy);
					}
					
					Uart_SendCMD(0x0f,0x00,0x01,0xaa);/*摄氏度*/
					delay800ms();
					while(!busy);
					
					
					Uart_SendYuYin(0xaa,0x00,0x00);/*打开识别*/
					flag = 0;
					mode = 0;
				}
					break;
					
			default:
					break;
		}
		
	}
}
/************串行口1中断处理函数*************/
void UART_1Interrupt () interrupt 4
{
	uchar i;
	if(RI == 1) 
	{  //如果收到.  
		RI = 0;      //清除标志.   
		Recv_buf[i] = SBUF;  //接收.
		i++; 
		if(Recv_buf[i-3]==0x5a)  /*当i=3时候，Recv_buf[0]=0x5a,收到正确数据flag置1*/
		{
			i = 0;
			flag=1;
		}
		
	}
}  

/************串行口2中断处理函数*************/
void UART_2Interrupt() interrupt 8
{
	uchar temp2;
	if(S2CON&S2RI)
	{
		S2CON&=~S2RI;
		temp2=S2BUF;
	}
}

