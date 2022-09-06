#include <REGX52.H>
#include "Delay.h"				//延时函数模块
#include "LCD1602.h"			//LCD1602显示模块
#include "MatrixKey.h"		//矩阵键盘模块
#include "MODE.h"					//模式选择模块
#include "Buzzer.h"				//蜂鸣器模块（针对Manual手动模式）
#include "Timer0.h"				//定时器模块（针对AutoPlay模式，初始化）

//宏定义AutoFreq[]频率索引为音符，方便识谱,分别为L、M、H，
#define	P0	0	//休止符
#define	L1	1	//低音L
#define	L1_	2	//'_'表示升半音
#define	L2	3
#define	L2_	4
#define	L3	5
#define	L4	6
#define	L4_	7
#define	L5	8
#define	L5_	9
#define	L6	10
#define	L6_	11
#define	L7	12
#define	M1	13	//中音M
#define	M1_	14
#define	M2	15
#define	M2_	16
#define	M3	17
#define	M4	18
#define	M4_	19
#define	M5	20
#define	M5_	21
#define	M6	22
#define	M6_	23	
#define	M7	24
#define	H1	25	//高音H
#define	H1_	26
#define	H2	27
#define	H2_	28
#define	H3	29
#define	H4	30	
#define	H4_	31
#define	H5	32	
#define	H5_	33
#define	H6	34
#define	H6_	35
#define	H7	36

#define SPEED		500	//宏定义四分音符时常为500ms
sbit Buzzer=P3^7;
sbit LED1=P3^5; //手动模式指示灯manual
sbit LED2=P3^4; //自动模式指示灯auto

//手动演奏模块
unsigned int ManFreq[]={0,190,170,151,143,127,113,100,95,		//第0位为空，之后每一位分别与按键序号对应
												   95, 85, 75, 71, 63, 56, 50,47};	//弹奏对应的16个共15种频率（已转为周期形式）
unsigned char code ManF_Node[][10]={"000","do-","re-","mi-","fa-","so-","la-","si-","do ",
																	"do ","re ","mi ","fa ","so ","la ","si ","do+"};//频率对应的音符

void ManualPlay(unsigned int KeyNum)
{
		LCD_ShowString(1,1,"Manual:         ");				
		if(KeyNum)
		{
				LCD_ShowString(2,1,"                  ");				
				LCD_ShowNum(2,1,KeyNum,2);
				LCD_ShowString(2,4,ManF_Node[KeyNum]);
				Buzzer_Freq(ManFreq[KeyNum]);//延时函数在文件 
		}
}		

//自动播放模块
unsigned char FreqSelect;
unsigned int code AutoFreq[]={//基于C大调
		0,//休止符
		63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64528,//低音
	  64582,64633,64686,64732,64778,64820,64860,64898,64934,64968,65000,65032,//中音
		65059,65085,65111,65134,65157,65178,65198,65217,65235,65252,65268,65284 //高音
};

//以16分音符为基准时长记为1,音符后的数值表示音高持续时间
//Music1《天空之城》
unsigned char code Music1[]={		//(音高，时长）
//1
		P0,4,P0,4,P0,4,M6,2,M7,2,		//每一行为一小节,
		H1,4+2,M7,2,H1,4,H3,4,
		M7,4+4+4,M3,2,M3,2,	
//2
		M6,4+2,M5,2,M6,4,H1,4,		
		M5,4+4+4,M3,4,		
		M4,4+2,M3,2,M4,4,H1,4,
//3
		M3,4+4,P0,2,H1,2,H1,2,H1,2,		
		M7,4+2,M4_,2,M4_,4,M7,4,		
		M7,4+4,P0,4,M6,2,M7,2,
//4
		H1,4+2,M7,2,H1,4,H3,4,		
		M7,4+4+4,M3,2,M3,2,		
		M6,4+2,M5,2,M6,4,H1,6,
//5
		M5,4+4+4,M2,2,M3,2,		
		M4,4,H1,2,M7,2+2,H1,2+4,		
		H2,2,H2,2,H3,2,H1,2+4+4,
//6
		H1,2,M7,2,M6,2,M6,2,M7,4,M5_,4,		
		M6,4+4+4,H1,2,H2,2,		
		H3,4+2,H2,2,H3,4,H5,4,
//7
		H2,4+4+4,M5,2,M5,2,		
		H1,4+2,M7,2,H1,4,H3,4,		
		H3,4+4+4,
//8
		M6,2,M7,2,H1,4,M7,4,H2,2,H2,2,		
		H1,4+2,M5,2+4+4,		
		H4,4,H3,4,H2,4,H1,4,	
//9
		H3,4+4+4,H3,4,		
		H6,4+4,H5,4,H5,4,		
		H3,2,H2,2,H1,4+4,P0,2,H1,2,
//10
		H2,4,H1,2,H2,2,H2,4,H5,4,		
		H3,4+4+4,H3,4,		
		H6,4+4,H5,4+4,
//11
		H3,2,H2,2,H1,4+4,P0,2,H1,2,		
		H2,4,H1,2,H2,2+4,M7,4,		
		M6,4+4+4,M6,2,M7,2,
	
		0xff //结束
};
//Music2 《我的祖国》
unsigned char code Music2[]={		//(音高，时长）
//1
		M1,2,M2,2,L6,2,L5,2,M5,6,M6,2,//每一行为一小节,
		M3,2,M5,2,H1,2,M6,2,M5,8,
		M5,4,M6,2,M5,2,M3,2,M2,2,M3,4,
		M5,2,M3,2,L6,2,M1,2,M2,8,
//2
		M2,2,M5,2,M3,2,M1,2,L6,4,L5,2,L6,2,
		M2,2,M6,2,M5,2,M6,2,M3,6,M2,2,
		M1,2,M2,1,M2,1,M3,2,M5,1,M5,1,H1,2,M6,2,M5,4,
//3
		M5,2,L6,2,M1,2,M2,2,M4,6,M6,1,M6,1,
		M5,3,M6,1,M3,2,M2,2,M1,8,
		M1,8,P0,4,M5,2,M5,2,
		H1,8,H2,6,H1,2,
		M6,2,H1,2,M5,2,M7,2,M6,8,
//4
		M5,4,M3,4,H1,4,M6,3,M6,1,
		M5,2,M6,2,M1,2,M2,2,M3,8,
		M3,4,M3,2,M5,2,M6,4,M6,2,H1,2,
		H2,4,H3,2,H1,2,H2,4+2,H1,2,
//5
		H2,2,M3,2,M5,2,M6,2,M7,2,H2,1,H2,1,M6,2,M7,2,
		M5,16,
		H2,2,M7,2,M6,2,M5,2,M3,2,M5,1,M5,1,M6,2,H2,2,
		H1,16,
		
			0xff //结束
};

//Music3 《前前前世》
unsigned char code Music3[]={		//(音高，时长）
//1
		M1,1,M2,1,M3,2,H1,2,M5,2,H2,3,M5,1,H3,1,M5,1,H5,2,
		H5,2,H1,2,H3,2,H1,2,H4,2,H3,2,H1,4,
		M1,1,M2,1,M3,2,H1,2,M5,2,H2,3,M5,1,H3,1,M5,1,H5,2,
		H5,2,H1,2,H3,2,H1,2,H4,2,H3,2,H1,4,
		
			0xff //结束
};

void Autoplay(unsigned int Key)
{
		if(Key==1)//播放 Music1
		{
				unsigned char MusicSelect=0;
				while(LED2==0 && Key==1)
				{				
						LCD_ShowString(2,1,"Music1: ~~       ");						
						if(Music1[MusicSelect]!=0xff)//判断是否结束
						{
								FreqSelect=Music1[MusicSelect];
								MusicSelect++;
								Delay(SPEED/4*Music1[MusicSelect]);//音符延时
								MusicSelect++;
								TR0=0;	//定时器关闭
								Delay(5);
								TR0=1;	//定时器打开（此操作隔离音符）
						}
						else //退出
						{
								TR0=0; //定时器关闭 
								FreqSelect=0;
								Key=0;
						}
				}
		}
		
		if(Key==2)//播放 Music2
		{
				unsigned char MusicSelect=0;
				while(LED2==0 && Key==2)
				{				
						LCD_ShowString(2,1,"Music2: ~~       ");						
						if(Music2[MusicSelect]!=0xff)//判断是否结束
						{
								FreqSelect=Music2[MusicSelect];
								MusicSelect++;
								Delay(SPEED/4*Music2[MusicSelect]);//音符延时
								MusicSelect++;
								TR0=0;	//定时器关闭
								Delay(5);
								TR0=1;	//定时器打开（此操作隔离音符）
						}
						else //退出
						{
								TR0=0; //定时器关闭 
								FreqSelect=0;
								Key=0;							
						}
				}
		}	
		if(Key==3)//播放 Music2
		{
				unsigned char MusicSelect=0;
				while(LED2==0 && Key==3)
				{				
						LCD_ShowString(2,1,"Music2: ~~       ");						
						if(Music3[MusicSelect]!=0xff)//判断是否结束
						{
								FreqSelect=Music3[MusicSelect];
								MusicSelect++;
								Delay(SPEED/4*Music3[MusicSelect]);//音符延时
								MusicSelect++;
								TR0=0;	//定时器关闭
								Delay(5);
								TR0=1;	//定时器打开（此操作隔离音符）
						}
						else //退出
						{
								TR0=0; //定时器关闭 
								FreqSelect=0;
								Key=0;							
						}
				}
		}	
		
}	


unsigned int KeyNum,Key;
void main()
{
		LCD_Init();//LCD1602初始化
		LCD_ShowString(1,4,"Welcome to");
		LCD_ShowString(2,4,"Music box!");
		Delay(1500);
		LCD_ShowString(1,1,"Select mode:     ");
		LCD_ShowString(2,1,"Yel:Man Gre:Auto    ");//黄灯为手动弹奏，绿灯为自动播放 
		Delay(1500);
	
		while(1)
		{						
				LED1 = 1;	LED2 = 1;
				LED1 = mode();	LED2 = !mode();//mode()模式函数，返回值为0时弹奏模式，为1时播放模式
				
				if(LED1==0)	//ManualPlay手动弹奏
				{	
						KeyNum = MatrixKey();
						ManualPlay(KeyNum);
				}				
				else if(LED2==0)	//Auto自动播放
				{
						Key = MatrixKey();
						LCD_ShowString(1,1,"Automatic:        ");						
						Timer0Init();	//定时器初始化
						Autoplay(Key);
				}
		}
}

void Timer0_Routine() interrupt 1
{
		if(AutoFreq[FreqSelect])//判断休止符
		{
				TL0 = AutoFreq[FreqSelect]%256;		//设置定时初值
				TH0 = AutoFreq[FreqSelect]/256;		//设置定时初值
				Buzzer=!Buzzer;
		}
}