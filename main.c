#include "include/graphics.h"
#include "include/extgraph.h"
#include "include/genlib.h"
#include "include/simpio.h"
#include "include/imgui.h"
#include "include/draw.h"
#include "include/find.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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
}KUN = {0, 0, 1, 0};

typedef enum{
    FPS,
    KUN_a,
} Mytimer;

void KeyboardEventProcess(int key,int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

void display();

void DrawMenu();
void DrawButton();
void DrawBox();

void Main()
{
	SetWindowTitle("CXK finding way");
	SetWindowSize(1920,1080);
	InitGraphics();
	
	double screen_x = GetWindowWidth();
	double screen_y = GetWindowHeight();

	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(FPS,100);  //启动10fps/s计时器

	//初始化坤的坐标
	KUN.x = screen_x/2;
	KUN.y = screen_y/2;
	DrawKUN(KUN.x, KUN.y, KUN.fps);

}


/********************
键盘消息回调函数
**********************/
void KeyboardEventProcess(int key,int event)
{
    uiGetKeyboard(key, event);
    switch(event){
		case KEY_DOWN:
			switch(key){
				case VK_w:
				case VK_W:
				case VK_UP:
					KUN.x = KUN.x;
					KUN.y = KUN.y + KUN.MOVE;
					break;
				case VK_a:
				case VK_A:
				case VK_LEFT:
					KUN.x = KUN.x - KUN.MOVE;
					KUN.y = KUN.y;
					break;
				case VK_s:
				case VK_S:
				case VK_DOWN:
					KUN.x = KUN.x;
					KUN.y = KUN.y - KUN.MOVE;
					break;
				case VK_d:
				case VK_D:
				case VK_RIGHT:
					KUN.x = KUN.x + KUN.MOVE;
					KUN.y = KUN.y;
					break;				
			}
			break;
		case KEY_UP:
			KUN.MOVE = 1;
			break;
	}

    display();
}

/********************
字符消息回调函数
**********************/
void CharEventProcess(char c)
{
    uiGetChar(c);
    display();
}

/********************
鼠标消息回调函数
**********************/
void MouseEventProcess(int x, int y, int button, int event)
{
    uiGetMouse(x, y, button, event);
    display();
}

/********************
定时器消息回调函数
**********************/
void TimerEventProcess(int timerID)
{
    switch (timerID)
    {
    case FPS:
        if(KUN.fps < 9){
            KUN.fps += 1;
        }else{
            KUN.fps = 0;
        }
        display();
        break;
    case KUN_a:

        break;    
    default:
        break;
    }
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
    
    //画坤
    DrawKUN(KUN.x, KUN.y, KUN.fps);
}
