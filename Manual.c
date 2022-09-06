//#include <REGX52.H>
//#include "Buzzer.h"
//#include "LCD1602.h"
////手动演奏模块
//unsigned int ManFreq[]={0,190,170,151,143,127,113,100,95,		//第0位为空，之后每一位分别与按键序号对应
//												   95, 85, 75, 71, 63, 56, 50,47};	//弹奏对应的16个共15种频率（已转为周期形式）
//unsigned char code ManF_Node[][10]={"000","do-","re-","mi-","fa-","so-","la-","si-","do ",
//																	"do ","re ","mi ","fa ","so ","la ","si ","do+"};//频率对应的音符

//void ManualPlay(unsigned int KeyNum)
//{
//		LCD_ShowString(1,1,"Manual:       ");				
//		if(KeyNum)
//		{
//				LCD_ShowNum(2,1,KeyNum,2);
//				LCD_ShowString(2,4,ManF_Node[KeyNum]);
//				Buzzer_Freq(ManFreq[KeyNum]);
//		}
//}