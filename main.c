#include "include/graphics.h"
#include "include/extgraph.h"
#include "include/genlib.h"
#include "include/simpio.h"
#include "include/draw.h"
#include "include/find.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

//A~Z的VK
#define   VK_A	0x41 
#define   VK_B	0x42 
#define   VK_C	0x43 
#define   VK_D	0x44 
#define   VK_E	0x45 
#define   VK_F	0x46 
#define   VK_G	0x47 
#define   VK_H	0x48 
#define   VK_I	0x49 
#define   VK_J	0x4A 
#define   VK_K	0x4B 
#define   VK_L	0x4C 
#define   VK_M	0x4D 
#define   VK_N	0x4E 
#define   VK_O	0x4F 
#define   VK_P	0x50 
#define   VK_Q	0x51 
#define   VK_R	0x52 
#define   VK_S	0x53 
#define   VK_T	0x54 
#define   VK_U	0x55 
#define   VK_V	0x56 
#define   VK_W	0x57 
#define   VK_X	0x58 
#define   VK_Y	0x59 
#define   VK_Z	0x5A  

//a~z的VK
#define   VK_a	0x61 
#define   VK_b	0x62 
#define   VK_c	0x63 
#define   VK_d	0x64 
#define   VK_e	0x65 
#define   VK_f	0x66 
#define   VK_g	0x67 
#define   VK_h	0x68 
#define   VK_i	0x69 
#define   VK_j	0x6A 
#define   VK_k	0x6B 
#define   VK_l	0x6C 
#define   VK_m	0x6D 
#define   VK_n	0x6E 
#define   VK_o	0x6F 
#define   VK_p	0x70 
#define   VK_q	0x71 
#define   VK_r	0x72 
#define   VK_s	0x73 
#define   VK_t	0x74 
#define   VK_u	0x75 
#define   VK_v	0x76 
#define   VK_w	0x77 
#define   VK_x	0x78 
#define   VK_y	0x79 
#define   VK_z	0x7A

static struct kun{
    double x;  //坤的横坐标
    double y;  //坤的纵坐标
    double MOVE;  //坤的移动速度
    int fps;  //坤动画的帧数
	bool direction;
}KUN = {0, 0, 1, 0, 0};

typedef struct box{
	double x;  //一个格子的横坐标
	double y;  //一个格子的纵坐标（左下角坐标）
	int state;  //这个格子的状态：0是空 1是障碍 2是待编辑
} BOX;

typedef enum{
    FPS,
    KUN_a,
	FPS_ALL,
	FLASH,
} Mytimer;

static bool isKUN_a = 0;  //坤是否可以加速
static bool fps_flag = 1;  //坤动画重播标志
static bool isCtrl = 0;  //ctrl键是否被按下
static bool canKUNmove = 1;  //坤可以动吗？
static bool canKUNdisplay = 1;  //drawKUN函数是否可以被调用

//来自draw.c:

extern double Mx, My;
extern bool isMClick;
extern bool MenuList1State[4];
extern bool MenuList2State[4];
extern bool MenuList3State;
extern bool isFlash;

//传送给draw.c:
char mapx[10] = "宽度:";
char mapy[10] = "高度:";

//地图长宽
int nowMapx;
int nowMapy;

//消息回调函数声明

void KeyboardEventProcess(int key,int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

//画图函数声明

void display();

void DrawMenu();
void DrawBox();

//菜单功能函数声明

void menu1fun1();
void menu1fun2();
void menu1fun3();
void menu1fun4();
void menu2fun1();
void menu2fun2();
void menu2fun3();
void menu2fun4();
void menu3fun1();

void Main()
{
	SetWindowTitle("CXK finding way");
	SetWindowSize(1920,1080);
	InitGraphics();
	//InitConsole();
	
	double screen_x = GetWindowWidth();
	double screen_y = GetWindowHeight();

	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(FPS, 100);  //启动10fps/s计时器
	startTimer(KUN_a, 200);  //启动加速度定时器
	startTimer(FPS_ALL, 8);  //屏幕60帧定时器
	startTimer(FLASH, 400);  //启动光标闪烁定时器

	DefineColor("Purple", .6, .6, .95);
	DefineColor("DYellow", 1, .76, 0);
	DefineColor("MCyan", .63, .86, .95);
	DefineColor("Wood", .74, .69, .68);
	DefineColor("Face", .87, .73, .75);
	DefineColor("MLPink", .95, .68, .625);
	DefineColor("MDPink", .95, .65, .625);

	//初始化坤的坐标
	KUN.x = screen_x/2;
	KUN.y = screen_y/2;
	DrawKUN(KUN.x, KUN.y, KUN.fps, KUN.direction);

}


/********************
键盘消息回调函数
**********************/
void KeyboardEventProcess(int key,int event)
{
    switch(event){
		case KEY_DOWN:
			switch(key){
				case VK_w:
				case VK_W:
				case VK_UP:
					if(canKUNmove){
						KUN.x = KUN.x;
						KUN.y = KUN.y + KUN.MOVE;
						isKUN_a = 1;
					}
					break;
				case VK_a:
				case VK_A:
				case VK_LEFT:
					if(canKUNmove){
						KUN.x = KUN.x - KUN.MOVE;
						KUN.y = KUN.y;
						isKUN_a = 1;
						KUN.direction = 1;
					}					
					break;
				case VK_s:
				case VK_S:
				case VK_DOWN:
					if(!isCtrl && canKUNmove){
						KUN.x = KUN.x;
						KUN.y = KUN.y - KUN.MOVE;
						isKUN_a = 1;
					}else{
						if(key != VK_DOWN){
							if(isCtrl) MenuList2State[2] = 1;
						}
					}					
					break;
				case VK_d:
				case VK_D:
				case VK_RIGHT:
					if(canKUNmove){
						KUN.x = KUN.x + KUN.MOVE;
						KUN.y = KUN.y;
						isKUN_a = 1;
						KUN.direction = 0;
					}					
					break;
				case VK_N:
				case VK_n:
					if(isCtrl) MenuList1State[0] = 1;
					break;
				case VK_M:
				case VK_m:
					if(isCtrl) MenuList1State[1] = 1;
					break;
				case VK_I:
				case VK_i:
					if(isCtrl) MenuList1State[2] = 1;
					break;
				case VK_O:
				case VK_o:
					if(isCtrl) MenuList1State[3] = 1;
					break;
				case VK_J:
				case VK_j:
					if(isCtrl) MenuList2State[0] = 1;
					break;
				case VK_K:
				case VK_k:
					if(isCtrl) MenuList2State[1] = 1;
					break;
				case VK_Z:
				case VK_z:
					if(isCtrl) MenuList2State[3] = 1;
					break;
				case VK_H:
				case VK_h:
					if(isCtrl) MenuList3State = 1;
					break;													
				case VK_CONTROL:
					isCtrl = 1;
				
			}
			break;
		case KEY_UP:
			isKUN_a = 0;
			KUN.MOVE = 1;
			isCtrl = 0;
			break;
	}

    display();
	return;
}

/********************
字符消息回调函数
**********************/
void CharEventProcess(char c)
{
	/*if(canEdit){
		int nx = strlen(mapx);
		int x = 0, y = 0;
		char *px = mapx;
		if(c >= '0' && c <= '9'){
			*(px + nx) = c;
			*(px + nx +1) = '\0';
		}
		for(int i = 6; *(px + i) != '\0'; i++){
			x = x * 10 + *(px + i) - '0';
		}
		nowMapx = x; 
	}*/

}

/********************
鼠标消息回调函数
**********************/
void MouseEventProcess(int x, int y, int button, int event)
{
	Mx = ScaleXInches(x);
	My = ScaleYInches(y);
	switch (event)
	{
	case BUTTON_DOWN:
		switch (button)
		{
		case LEFT_BUTTON:
			isMClick = 1;
			break;
		
		default:
			break;
		}
		break;
	case BUTTON_UP:
		isMClick = 0;
		break;
	default:
		break;
	}
	return;
}

/********************
定时器消息回调函数
**********************/
void TimerEventProcess(int timerID)
{
    switch (timerID)
    {
    case FPS:
		if(fps_flag){
			if(KUN.fps == 9){
				fps_flag = !fps_flag;
			}			
			if(KUN.fps < 9){
            	KUN.fps += 1;
        	}	
		}
		if(!fps_flag){
			if(KUN.fps == 0){
				fps_flag = !fps_flag;
			}
			if(KUN.fps > 0){
				KUN.fps -= 1;
			}
		}
        display();
        break;
    case KUN_a:  //坤运动加速度的实现
		if(isKUN_a == 1 && KUN.MOVE < 4){
			KUN.MOVE += 1;
		}else if(isKUN_a == 1 && KUN.MOVE < 9){
			KUN.MOVE += 2;
		}
		break;
	case FLASH:
		isFlash = !isFlash;
		break;		
	case FPS_ALL:
		display();
		break;    
	default:
        break;
    }
	return;
}



/*****************
刷新显示函数，依赖全局变量
放在每个消息回调函数的最后
最上层图层在函数最下部分
******************/
void display()
{
    //清屏
    DisplayClear();

	//画舞台
	DrawStage();
    
    //画菜单
	DrawMenu();

	//menulist1
	if(MenuList1State[0]) menu1fun1();
	if(MenuList1State[1]) menu1fun2();
	if(MenuList1State[2]) menu1fun3();
	if(MenuList1State[3]) menu1fun4();
	
	//menulist2
	if(MenuList2State[0]) menu2fun1();
	if(MenuList2State[1]) menu2fun2();
	if(MenuList2State[2]) menu2fun3();
	if(MenuList2State[3]) menu2fun4();
	
	//画坤
    if(canKUNdisplay) DrawKUN(KUN.x, KUN.y, KUN.fps, KUN.direction);

	//字
	/*MovePen(300, 300);
	SetPenColor("Black");
	SetPointSize(100);
	SetFont("千图小兔体");
	string a = "偶像练习生";
	DrawTextString(a);*/
	return;
}


/*****************
菜单列表一：1-新的开始
*****************/
void menu1fun1()  
{
	canKUNdisplay = 1;
}

/*****************
菜单列表一：2-重新开始
*****************/
void menu1fun2()
{
	canKUNdisplay = 1;
}

/*****************
菜单列表一：3-保存游戏
*****************/
void menu1fun3()
{
	
}

/*****************
菜单列表一：4-打开存档
*****************/
void menu1fun4()
{
	
}

/*****************
菜单列表二：1-创建地图
*****************/
void menu2fun1()
{
	canKUNdisplay = 0;
	static bool isFinish = 0;
	switch (DrawMenu2fun1())
	{
	case 0:
		isFinish = 1;
		break;
	case 1:
		isFinish = 1;
	default:
		break;
	}

	if(isFinish){
		canKUNdisplay = 1;
		MenuList2State[0] = 0;
		isFinish = 0;
	}
}

/*****************
菜单列表二：2-编辑地图
*****************/
void menu2fun2()
{
	canKUNdisplay = 0;
}

/*****************
菜单列表二：3-保存地图
*****************/
void menu2fun3()
{
	
}

/*****************
菜单列表二：4-撤销
*****************/
void menu2fun4()
{
	
}

/*****************
菜单列表三：1-帮助
*****************/
void menu3fun1()
{
	
}