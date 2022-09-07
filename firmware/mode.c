#include <REGX52.H>
#include "Delay.h"

unsigned int FY;//模式变量，为0时弹奏模式，为1时播放模式
unsigned int mode()
{
		if(P3_3==0){
				Delay(20);while(P3_3==0);Delay(20);//消抖
				FY = 0;
		}	
		else if(P3_2==0){
				Delay(20);while(P3_2==0);Delay(20);//消抖 
				FY = 1;	
		}			
		return FY;
		
}
