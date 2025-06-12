#include <REGX52.H>
#include "INTRINS.h"

//蜂鸣器端口
sbit Buzzer=P3^7;


void Delayus(unsigned int x10us)		//@12.000MHz
{
	while(x10us--)
	{
		unsigned char i;

		_nop_();
		i = 2;
		while (--i);
	}
}

/**
  * @brief 		蜂鸣器发声
  * @param		ms，发声时长
  * @retrval	无
  
*/

void Buzzer_Freq(unsigned int Key)
{
		unsigned int i;
		for(i=0;i<90;i++)
		{
				Buzzer=!Buzzer;
				Delayus(Key);

		}
}