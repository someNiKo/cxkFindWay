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

//A~Z��VK
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

//a~z��VK
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
    double x;  //���ĺ�����
    double y;  //����������
    double MOVE;  //�����ƶ��ٶ�
    int fps;  //��������֡��
	bool direction;
}KUN = {0, 0, 1, 0, 0};

typedef struct box{
	double x;  //һ�����ӵĺ�����
	double y;  //һ�����ӵ������꣨���½����꣩
	int state;  //������ӵ�״̬��0�ǿ� 1���ϰ� 2�Ǵ��༭
} BOX;

static bool isKUN_a = 0;
static bool fps_flag = 1;
static bool isCtrl = 0;

extern double Mx, My;
extern bool isMClick;
extern bool MenuList1State[4];

typedef enum{
    FPS,
    KUN_a,
	FPS_ALL,
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
	//InitConsole();
	
	double screen_x = GetWindowWidth();
	double screen_y = GetWindowHeight();

	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(FPS, 100);  //����10fps/s��ʱ��
	startTimer(KUN_a, 200);  //�������ٶȶ�ʱ��
	startTimer(FPS_ALL, 8);  //��Ļ60֡��ʱ��

	DefineColor("Purple", .6, .6, .95);
	DefineColor("DYellow", 1, .76, 0);
	DefineColor("MCyan", .63, .86, .95);
	DefineColor("Wood", .74, .69, .68);
	DefineColor("Face", .87, .73, .75);
	DefineColor("MLPink", .95, .68, .625);
	DefineColor("MDPink", .95, .65, .625);

	//��ʼ����������
	KUN.x = screen_x/2;
	KUN.y = screen_y/2;
	DrawKUN(KUN.x, KUN.y, KUN.fps, KUN.direction);

}


/********************
������Ϣ�ص�����
**********************/
void KeyboardEventProcess(int key,int event)
{
    switch(event){
		case KEY_DOWN:
			switch(key){
				case VK_w:
				case VK_W:
				case VK_UP:
					KUN.x = KUN.x;
					KUN.y = KUN.y + KUN.MOVE;
					isKUN_a = 1;
					break;
				case VK_a:
				case VK_A:
				case VK_LEFT:
					KUN.x = KUN.x - KUN.MOVE;
					KUN.y = KUN.y;
					isKUN_a = 1;
					KUN.direction = 1;
					break;
				case VK_s:
				case VK_S:
				case VK_DOWN:
					KUN.x = KUN.x;
					KUN.y = KUN.y - KUN.MOVE;
					isKUN_a = 1;
					break;
				case VK_d:
				case VK_D:
				case VK_RIGHT:
					KUN.x = KUN.x + KUN.MOVE;
					KUN.y = KUN.y;
					isKUN_a = 1;
					KUN.direction = 0;
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
}

/********************
�ַ���Ϣ�ص�����
**********************/
void CharEventProcess(char c)
{
    //display();
}

/********************
�����Ϣ�ص�����
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
	
}

/********************
��ʱ����Ϣ�ص�����
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
    case KUN_a:  //���˶����ٶȵ�ʵ��
		if(isKUN_a == 1 && KUN.MOVE < 4){
			KUN.MOVE += 1;
		}else if(isKUN_a == 1 && KUN.MOVE < 9){
			KUN.MOVE += 2;
		}
		break;
	case FPS_ALL:
		display();    
	default:
        break;
    }
}



/*****************
ˢ����ʾ����������ȫ�ֱ���
����ÿ����Ϣ�ص����������
���ϲ�ͼ���ں������²���
******************/
void display()
{
    //����
    DisplayClear();

	//����̨
	DrawStage();
    
    //���˵�
	DrawMenu();
	
	//����
    DrawKUN(KUN.x, KUN.y, KUN.fps, KUN.direction);

	//��
	MovePen(300, 300);
	SetPenColor("Black");
	SetPointSize(100);
	SetFont("�ĵ���е��");
	string a = "ż����ϰ��";
	DrawTextString(a);
	
	return;
}