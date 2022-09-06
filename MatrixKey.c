#include <REGX52.H>
#include "Delay.h"

/**
  * @brief   矩阵键盘读取按键键码
  * @param   无
  * @retrval KeyNumber 按下按键的键码值
	           如果按下按键不放，程序会停留在此函数while(),松手的一瞬间，返回按键键码，没有按键按下时返回0
*/
unsigned char MatrixKey()
{  
    unsigned char KeyNumber=0;
	  
	  P1_0=P1_1=P1_2=P1_3=1;P2_0=P2_1=P2_2=P2_3=1;
	  P1_0=0;
	  if(P2_3==0){Delay(20);while(P2_3==0);Delay(20);KeyNumber=1;}
	  if(P2_2==0){Delay(20);while(P2_2==0);Delay(20);KeyNumber=5;}
	  if(P2_1==0){Delay(20);while(P2_1==0);Delay(20);KeyNumber=9;}
	  if(P2_0==0){Delay(20);while(P2_0==0);Delay(20);KeyNumber=13;}
		
	  P1_0=P1_1=P1_2=P1_3=1;P2_0=P2_1=P2_2=P2_3=1;
	  P1_1=0;
	  if(P2_3==0){Delay(20);while(P2_3==0);Delay(20);KeyNumber=2;}
	  if(P2_2==0){Delay(20);while(P2_2==0);Delay(20);KeyNumber=6;}
	  if(P2_1==0){Delay(20);while(P2_1==0);Delay(20);KeyNumber=10;}
	  if(P2_0==0){Delay(20);while(P2_0==0);Delay(20);KeyNumber=14;}
		
	  P1_0=P1_1=P1_2=P1_3=1;P2_0=P2_1=P2_2=P2_3=1;
	  P1_2=0;
	  if(P2_3==0){Delay(20);while(P2_3==0);Delay(20);KeyNumber=3;}
	  if(P2_2==0){Delay(20);while(P2_2==0);Delay(20);KeyNumber=7;}
	  if(P2_1==0){Delay(20);while(P2_1==0);Delay(20);KeyNumber=11;}
	  if(P2_0==0){Delay(20);while(P2_0==0);Delay(20);KeyNumber=15;}
		
	  P1_0=P1_1=P1_2=P1_3=1;P2_0=P2_1=P2_2=P2_3=1;
	  P1_3=0;
	  if(P2_3==0){Delay(20);while(P2_3==0);Delay(20);KeyNumber=4;}
	  if(P2_2==0){Delay(20);while(P2_2==0);Delay(20);KeyNumber=8;}
	  if(P2_1==0){Delay(20);while(P2_1==0);Delay(20);KeyNumber=12;}
	  if(P2_0==0){Delay(20);while(P2_0==0);Delay(20);KeyNumber=16;}
	  
	  return KeyNumber;
		
}
	