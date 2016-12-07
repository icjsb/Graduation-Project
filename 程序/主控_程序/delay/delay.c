#include "delay.h"

void delay10ms(void)   //Îó²î -0.000000000001us
{
    unsigned char a,b,c;
    for(c=5;c>0;c--)
        for(b=89;b>0;b--)
            for(a=247;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
void delay50ms(void)   //Îó²î -0.000000000006us
{
    unsigned char a,b,c;
    for(c=254;c>0;c--)
        for(b=229;b>0;b--)
            for(a=8;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
void delay200ms(void)   //Îó²î -0.000000000025us
{
    unsigned char a,b,c,n;
    for(c=187;c>0;c--)
        for(b=217;b>0;b--)
            for(a=53;a>0;a--);
    for(n=2;n>0;n--);
}
void delay800ms(void)   //Îó²î -0.0000000001us
{
    unsigned char a,b,c,n;
    for(c=249;c>0;c--)
        for(b=220;b>0;b--)
            for(a=160;a>0;a--);
    for(n=14;n>0;n--);
    _nop_();  //if Keil,require use intrins.h
}
