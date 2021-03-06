#include"ds3231.h"
bit ack;	//应答标志位

uchar BCD2HEX(uchar val)
{
	return	((val>>4)*10)+(val&0x0f);
}


uchar HEX2BCD(uchar val)
{
	return	(((val%100)/10)<<4)|(val%10);
}


void Delay5US() 
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 24;
	while (--i);
}
/*******************************************************/
/**
/**  I2C开始信号
/**
/*******************************************************/
void Start_I2C()
{
    SDA=1;                  //发送起始条件的数据信号
    SCL=1;
    Delay5US();             //起始条件建立时间大于4.7us,延时     
    SDA=0;                  //发送起始信号
    Delay5US();             // 起始条件锁定时间大于4μs		        
    SCL=0;                  //钳住I2C总线，准备发送或接收数据
}												   
/**********************************************************************/
/**
/**  I2C停止信号
/**
/**********************************************************************/
void Stop_I2C()
{
    SDA=0;                  //发送结束条件的数据信号
    SCL=1;                  //结束条件建立时间大于4us
    Delay5US();											     
    SDA=1;                  //发送I2C总线结束信号
}												   
/**********************************************************************/
/**
/**  I2C发送字节
/**
/**********************************************************************/
void SendByte(uchar c)
{
    uchar BitCnt;
   
    for(BitCnt=0;BitCnt<8;BitCnt++)         //要传送的数据长度为8位
    {
        if((c<<BitCnt)&0x80)
            SDA=1;                          //判断发送位
        else 
            SDA=0;     
        SCL=1;                            //置时钟线为高，通知被控器开始接收数据位
        Delay5US();                       //保证时钟高电平周期大于4μs   
        SCL=0;
    }
    SDA=1;                                  //8位发送完后释放数据线，准备接收应答位
    SCL=1;
    Delay5US();
    if(SDA==1)
        ack=0;    
    else
        ack=1;                              //判断是否接收到应答信号
    SCL=0;
    Delay5US();
}	   
/**********************************************************************/
/**
/**  I2C接收字节
/**
/**********************************************************************/
uchar RcvByte()
{
   uchar retc;
   uchar BitCnt;
 
   retc=0;
   SDA=1;                           //置数据线为输入方式
   for(BitCnt=0;BitCnt<8;BitCnt++)
   {
        SCL=0;                      //置时钟线为低，准备接收数据位       
        Delay5US();                 //时钟低电平周期大于4.7μs		       
        SCL=1;                      //置时钟线为高使数据线上数据有效
        Delay5US();
        retc=retc<<1;
        if(SDA==1)
            retc=retc+1;            //读数据位,接收的数据位放入retc中
        Delay5US();
   }
   SCL=0;
   return(retc);
}			    

void Ack_I2C(bit a)
{
	SDA	= a;  
    SCL=1;		      
    Delay5US();             //时钟低电平周期大于4μs    
    SCL=0;                  //清时钟线，钳住I2C总线以便继续接收
    Delay5US();   
}					    

uchar write_byte(uchar addr, uchar write_data)
{
    Start_I2C();
    SendByte(DS3231_WriteAddress);
    if (ack == 0)
        return 0;
   
    SendByte(addr);   
    if (ack == 0)
        return 0;
   
    SendByte(write_data);
    if (ack == 0)
        return 0;
   
    Stop_I2C();
    Delay5US();      
    Delay5US();      
    return 1;
}					  
/**********************************************************************/
/**
/**  I2C读取当前地址
/**
/**********************************************************************/
uchar read_current()
{
    uchar read_data;
    Start_I2C();
    SendByte(DS3231_ReadAddress);
    if(ack==0)
        return(0);	      
    read_data = RcvByte();
    Ack_I2C(1);
    Stop_I2C();
    return read_data;
}						 
/**********************************************************************/
/**
/**  I2C读取随机地址数据
/**
/**********************************************************************/
uchar read_random(uchar random_addr)
{
    Start_I2C();
    SendByte(DS3231_WriteAddress);
    if(ack==0)
        return(0);	    
    SendByte(random_addr);
    if(ack==0)
        return(0);			    
    return(read_current());
}				  

void ModifyTime(uchar yea,uchar mon,uchar da,uchar hou,uchar min,uchar sec)
{
    uchar temp=0;
   
    temp=HEX2BCD(yea);
    write_byte(DS3231_YEAR,temp);   //修改年
   
    temp=HEX2BCD(mon);
    write_byte(DS3231_MONTH,temp);  //修改月
   
    temp=HEX2BCD(da);
    write_byte(DS3231_DAY,temp);    //修改日
   
    temp=HEX2BCD(hou);
    write_byte(DS3231_HOUR,temp);   //修改时
   
    temp=HEX2BCD(min);
    write_byte(DS3231_MINUTE,temp); //修改分
   
    temp=HEX2BCD(sec);
    write_byte(DS3231_SECOND,temp); //修改秒
}
