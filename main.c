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
#include <math.h>
#include <omp.h>  //openMP�����Ż�

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

typedef struct map{
	struct map *prev;  //��һ���ڵ�ĵ�ַ
	BOX listMap[20][30];  //�ýڵ�ĵ�ͼ
	struct map *next;  //��һ���ڵ�ĵ�ַ
} Map;  //������ʷ��ͼ���ݵ�˫������

Map *head = NULL, *end = NULL;

BOX nowMap[20][30];  //��ǰ��ͼ
BOX lastMap[20][30];  //��һ����ͼ������������

typedef enum{
    FPS,
    KUN_a,
	FPS_ALL,
	FLASH,
} Mytimer;

static bool isKUN_a = 0;  //���Ƿ���Լ���
static bool fps_flag = 1;  //�������ز���־
static bool isCtrl = 0;  //ctrl���Ƿ񱻰���
static bool canKUNdisplay = 1;  //drawKUN�����Ƿ���Ա�����
static bool canMapdisplay = 0;  //��ͼ������ʾ��
static bool canKUNmove[4] = {1, 1, 1, 1};  //�����Զ���(0��1��2��3��)

//����draw.c:

extern double Mx, My;
extern bool isMClick;
extern bool MenuList1State[4];
extern bool MenuList2State[4];
extern bool MenuList3State;
extern bool isFlash;
extern bool isFlashing[10];

extern double mapStartX, mapStartY;
extern double width;

//���͸�draw.c:
char mapx[10] = "���:10";
char mapy[10] = "�߶�:10";

//��ͼ����
int nowMapx = 10;
int nowMapy = 10;
int startX, startY;  //�������
int endX, endY;  //�յ�����

//��Ϣ�ص���������

void KeyboardEventProcess(int key,int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

//��ͼ��������

void display();

void DrawMenu();
void DrawBox();

void KUNmoveJUDGE();

//�˵����ܺ�������

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

	//��ʼ����ͼ
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 30; j++){
			if(i % 2 == 0) nowMap[i][j].state = 0;
			else if(j%3 == 0) nowMap[i][j].state = 1;
			nowMap[i][j].y = i + 1;
			nowMap[i][j].x = j + 1;
			lastMap[i][j].state = 0;
			lastMap[i][j].y = i + 1;
			lastMap[i][j].x = j + 1;			
		}
	}
	nowMap[0][0].state = 2;
	nowMap[3][3].state = 3;
	startX = 1;
	startY = 1;
	endX = 4;
	endY = 4; 

	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);

	startTimer(FPS, 100);  //����10fps/s��ʱ��
	startTimer(KUN_a, 200);  //�������ٶȶ�ʱ��
	startTimer(FPS_ALL, 30);  //��Ļ60֡��ʱ��
	startTimer(FLASH, 400);  //���������˸��ʱ��

	DefineColor("Purple", .6, .6, .95);
	DefineColor("DYellow", 1, .76, 0);
	DefineColor("MCyan", .63, .86, .95);
	DefineColor("Wood", .85, .79, .77);
	DefineColor("Face", .87, .73, .75);
	DefineColor("MLPink", .95, .68, .625);
	DefineColor("MDPink", .95, .65, .625);
	DefineColor("MGray1", .9, .9, .9);
	DefineColor("MGray2", .7, .7, .7);
	DefineColor("MGreen1", .46, .98, .55);
	DefineColor("MGreen2", .29, .61, .35);
	DefineColor("MYellow1", 1, 1, .33);
	DefineColor("MYellow2", 1, .8, .32);
	DefineColor("MRed1", 1, .4, .3);
	DefineColor("MRed2", .875, .16, .16);
	DefineColor("MOrange1", .95, .56, .22);
	DefineColor("MOrange2", .95, .74, .36);	

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
					if(canKUNmove[0]){
						KUN.x = KUN.x;
						KUN.y = KUN.y + KUN.MOVE;
						isKUN_a = 1;
					}
					break;
				case VK_a:
				case VK_A:
				case VK_LEFT:
					if(canKUNmove[2]){
						KUN.x = KUN.x - KUN.MOVE;
						KUN.y = KUN.y;
						isKUN_a = 1;
					}
					KUN.direction = 1;					
					break;
				case VK_s:
				case VK_S:
				case VK_DOWN:
					if(!isCtrl && canKUNmove[1]){
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
					if(canKUNmove[3]){
						KUN.x = KUN.x + KUN.MOVE;
						KUN.y = KUN.y;
						isKUN_a = 1;
					}
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
				case VK_DELETE:
				case VK_BACK:
					if(strlen(mapx) > 5 && isFlashing[0]){
						char *p = mapx;
						*(p + strlen(mapx) - 1) = '\0';
						isFlashing[0] = 1;
					}
					if(strlen(mapy) > 5 && isFlashing[1]){
						char *p = mapy;
						*(p + strlen(mapy) - 1) = '\0';
						isFlashing[1] = 1;
					}
			}
			break;
		case KEY_UP:
			isKUN_a = 0;
			KUN.MOVE = 1;
			isCtrl = 0;
			switch (key)
			{
				case VK_RETURN:
					if(isFlashing[0]){
						isFlashing[0] = 0;
					}
					if(isFlashing[1]){
						isFlashing[1] = 0;
					}					
				default:
					break;
			}
			break;
	}

    //display();
	return;
}

/********************
�ַ���Ϣ�ص�����
**********************/
void CharEventProcess(char c)
{
	//ɾ���ͻس���KeyBoardEvent
	if(isFlashing[0]){
		//�õ����
		int nx = strlen(mapx);
		int x = 0;
		char *px = mapx;
		if(c >= '0' && c <= '9'){
			*(px + nx) = c;
			*(px + nx +1) = '\0';
		}
		for(int i = 5; *(px + i) != '\0'; i++){
			x = x * 10 + *(px + i) - '0';
		}
		nowMapx = x;
	}
	if(isFlashing[1]){
		//�õ��߶�
		int ny = strlen(mapy);
		int y = 0;
		char *py = mapy;
		if(c >= '0' && c <= '9'){
			*(py + ny) = c;
			*(py + ny +1) = '\0';
		}
		for(int i = 5; *(py + i) != '\0'; i++){
			y = y * 10 + *(py + i) - '0';
		}
		nowMapy = y;		
	}

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
	return;
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
        break;
    case KUN_a:  //���˶����ٶȵ�ʵ��
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
		KUNmoveJUDGE();
		break;    
	default:
        break;
    }
	return;
}

/*************
�ж����Ƿ���ƶ�
**************/
void KUNmoveJUDGE()
{
	if(canMapdisplay){
		//����任
		int X = 0, Y = 0;
		if(KUN.x - mapStartX > 0){
			X = (int)((KUN.x - mapStartX) / width);
		}else{
			X = -1;
		}
		if(KUN.y - mapStartY > 0){
			Y = (int)((KUN.y - mapStartY - 15) / width);
		}else{
			Y = -1;
		}		
		//���������ж�
		bool corrected = 1;
		//�󷽳���
		if(X < 0){
			canKUNmove[2] = 0;
			canKUNmove[3] = 1;
			corrected = 0;
		}
		//�ҷ�����
		if(X > nowMapx - 1){
			canKUNmove[3] = 0;
			canKUNmove[2] = 1;
			corrected = 0;
		}
		//�·�����
		if(KUN.y - mapStartY < 20){
			canKUNmove[1] = 0;
			canKUNmove[0] = 1;
			corrected = 0;
		}
		//�Ϸ�����
		if(Y > nowMapy - 1){
			canKUNmove[0] = 0;
			canKUNmove[1] = 1;
			corrected = 0;
		}

	if(corrected){
		//�������ϰ�����ͷ�����ϰ�
		if(Y + 1 <= nowMapy - 1 && nowMap[Y][X].state != 1 && nowMap[Y + 1][X].state == 1 ){		
			if((width - fmod(KUN.y - mapStartY, width)) <= 14){
				canKUNmove[0] = 0;
				canKUNmove[1] = 1;
				corrected = 0;
			}		
		}
		//�������ϰ������·����ϰ�
		if(Y - 1 >= 0 && nowMap[Y][X].state != 1 && nowMap[Y - 1][X].state == 1){		
			if(fmod(KUN.y - mapStartY - 15, width) <= 25){
				canKUNmove[1] = 0;
				canKUNmove[0] = 1;
				corrected = 0;		
			}		
		}
		//�������ϰ������ҷ����ϰ�
		if(X + 1 <= nowMapx - 1 && nowMap[Y][X].state != 1 && nowMap[Y][X + 1].state == 1){		
			if((width - fmod(KUN.x - mapStartX, width)) <= 14){
				canKUNmove[3] = 0;
				canKUNmove[2] = 1;
				corrected = 0;		
			}		
		}
		//�������ϰ����������ϰ�
		if(X - 1 >= 0 && nowMap[Y][X].state != 1 && nowMap[Y][X - 1].state == 1){		
			if(fmod(KUN.x - mapStartX, width) <= 14){
				canKUNmove[2] = 0;
				canKUNmove[3] = 1;
				corrected = 0;
			}		
		}																
	}
		//�ָ�
		if(corrected){
			canKUNmove[0] = 1;
			canKUNmove[1] = 1;
			canKUNmove[2] = 1;
			canKUNmove[3] = 1;
		}		
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
    
    //����ͼ
	if(canMapdisplay) DrawBox();

	//���˵�
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
	
	//����
    if(canKUNdisplay){
		DrawKUN(KUN.x, KUN.y, KUN.fps, KUN.direction);
	} 

	//������
	/*MovePen(300, 540);
	SetPenColor("Black");
	SetPenSize(1);
	DrawLine(1000,0);
	MovePen(960, 100);
	DrawLine(0,900);*?
	return;*/
}

/*********************����********************/

/********************
����ͼ���벢����
�ɹ� return 1
ʧ�� return 0
......
*********************/
bool encode()
{
	FILE *p;
	if((p = fopen("GameMap.txt", "a")) == NULL){
		p = fopen("GameMap.txt", "w");
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 30; j++){
				fprintf(p, "%d ", nowMap[i][j].state);
			}
			fprintf(p, "\n");
		}
		fclose(p);
		return 1;  //û�ҵ��ļ����½�һ��
	}else{
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 30; j++){
				fprintf(p, "%d ", nowMap[i][j].state);
			}
			fprintf(p, "\n");
		}
	}
	if(fclose(p) == -1){
		return 0;
	}else{
		return 1;
	}
}

/**********************
�����ͼ�ļ�
�ɹ� return *HEAD
ʧ�� return NULL
***********************/
bool decode()
{
	FILE *fp;
	if((fp = fopen("GameMap.txt", "r")) == NULL){
		return 0;
	}
	
	Map *mp = (Map *)malloc(sizeof(Map));
	if(head == NULL){  //��һ�ν�������
		mp->prev = NULL;  //��ǰ�ڵ�֮ǰΪ��
		mp->next = NULL;  //��ǰ֮��ڵ�Ϊ��
		end = mp;         //β�ڵ�Ϊ��ǰ�ڵ�
		head = mp;		  //ͷ�ڵ�Ϊ��ǰ�ڵ�
	}else{             //���ǵ�һ�ν�������
		mp->prev = end;   //��ǰ�ڵ�֮ǰΪβ�ڵ� 
		mp->next = NULL;  //��ǰ�ڵ�֮��Ϊ��
		end->next = mp;   //β�ڵ���һ��Ϊ��ǰ�ڵ�
		end = mp;         //β�ڵ�Ϊ��ǰ�ڵ�
	}
	
	for(int i = 0; i < 20; i++){
		char str[62];
		char *pstr = str;
		fgets(str, 62, fp);
		for(int j = 0; j < 30; j++){
			//�����ͼ����
			mp->listMap[i][j].state = *pstr - '0';
			mp->listMap[i][j].x = j + 1;
			mp->listMap[i][j].y = i + 1;
			//�ƶ��ַ���ָ�� pstr
			pstr += 2;
		}
	}
	fclose(fp);
	return 1;
}

/*******************
�ļ�ƫ����ָ��ĳ�еĹ���
*********************/
void setOffsetToLineStart(FILE* file, int line, int lineLength)
{
    long offset = (line - 1) * lineLength;
    fseek(file, offset, SEEK_SET);
}

/*********************
��ȡ�ļ���Ч�����Ĺ���
**********************/
int countValidLines(FILE* file)
{
    int count = 0;
    char buffer[100]; // �ʵ�ѡ�񻺳�����С

    // ���ж�ȡ�ļ�����
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // ������Ƿ���Ч
        // ������Ը���ʵ����Ҫ��Ӹ�����������ж��е���Ч��
        if (buffer[0] != '\n' && buffer[0] != '\0') {
            count++;
        }
    }

    // ������Ч����
    return count;
}

/************
�������ϵ�ͼ����
**************/
void mapcopy(bool flag)
{
	if(flag){  //��->����
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 30; j++){
				nowMap[i][j] = lastMap[i][j];
			}
		}
	}else{  //����->��
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 30; j++){
				lastMap[i][j] = nowMap[i][j];
			}
		}			
	}
}

/***********************�˵�����***********************/
/*****************
�˵��б�һ��1-�µĿ�ʼ
*****************/
void menu1fun1()  
{
	static bool other = 1; 
	if(other){
		MenuList2State[1] = 0;
		MenuList2State[0] = 0;
		other = 0;
	}
	
	canKUNdisplay = 1;
	canMapdisplay = 1;
	
	static bool flag = 1;
	static bool isFinish = 0;
	
	if(flag){
		//�������ĳ�ʼλ��  ִֻ��һ��
		KUN.x = mapStartX + startX * width - width/2;
		KUN.y = mapStartY + startY * width - width/2 + 15;
		flag = 0;		
	}	
	
	//����任
	int X = 0, Y = 0;  //���ľ�������
	if(KUN.x - mapStartX > 0){
		X = (int)((KUN.x - mapStartX) / width);
	}else{
		X = 0;
	}
	if(KUN.y - mapStartY > 0){
		Y = (int)((KUN.y - mapStartY - 15) / width);
	}else{
		Y = 0;
	}

	//���������ж�
	static int times = 0;  //��30��
	if(nowMap[Y][X].state == 3 && times <= 30){
		SetPenColor("MRed2");
		SetPointSize(200);
		SetFont("ǧͼС����");
		MovePen(700, 500);
		DrawTextString("�ɹ�!");
		times++;
		if(times == 30) isFinish = 1;
	}	

	int data = DrawMenu1fun1();

	int **Maze = (int **)malloc((nowMapy + 2) * sizeof(int *));
	for(int i = 0; i <= nowMapy + 1; i++){
		Maze[i] = (int *)malloc((nowMapx + 2) * sizeof(int));
	}
	for(int i = 0; i <= nowMapy + 1; i++){
		Maze[i][0] = 1;
		Maze[i][nowMapx + 1] = 1;
	}
	for(int j = 0; j <= nowMapx + 1; j++){
		Maze[0][j] = 1;
		Maze[nowMapy + 1][j] = 1;
	}
	for(int i = 0; i < nowMapy; i++){
		for(int j = 0; j < nowMapx; j++){
			Maze[i + 1][j + 1] = nowMap[i][j].state;
		}
	}	

	static int showtimes = 0;
	if(showtimes){
		showtimes++;
		if(showtimes >= 20){
			showtimes = 0;
			mapcopy(1);
			canKUNdisplay = 1;
		}
	}

	if(data && isMClick){
		printf("%d\n",data);
		canKUNdisplay = 0;
		showtimes = 1;
		Findfun(Maze, data, X + 1, Y + 1);
		//��������
		mapcopy(0);
		for(int i = 0; i < nowMapy; i++){
			for(int j = 0; j < nowMapx; j++){
				nowMap[i][j].state = Maze[i + 1][j + 1]; 
			}
		}		
	}

	//free 
    for (int i = 0; i <= nowMapy + 1; i++) free(Maze[i]);
	free(Maze);	
	
	if(MenuList2State[2] || MenuList2State[3] || MenuList2State[0] || MenuList2State[1]) isFinish = 1;

	if(isFinish){
		flag = 1;
		other = 1;
		canKUNdisplay = 0;
		canMapdisplay = 0;
		times = 0;
		showtimes = 0;		
		isFinish = 0;
		MenuList1State[0] = 0;
	}
}

/*****************
�˵��б�һ��2-���¿�ʼ
*****************/
void menu1fun2()
{
	canKUNdisplay = 1;
	canMapdisplay = 1;
	MenuList1State[1] = 0;  //ִֻ��һ��
}

/*****************
�˵��б�һ��3-������Ϸ
*****************/
void menu1fun3()
{
	
}

/*****************
�˵��б�һ��4-�򿪴浵
*****************/
void menu1fun4()
{
	//�ǵö�ȡ�ļ���Ч����
}

/*****************
�˵��б����1-������ͼ
*****************/
void menu2fun1()
{
	canKUNdisplay = 0;
	canMapdisplay = 0;
	static bool isFinish = 0;
	static bool other = 1; 
	if(other){
		MenuList2State[1] = 0;
		MenuList1State[0] = 0;
		other = 0;
	}	
	switch (DrawMenu2fun1())
	{
	case 0:
		isFinish = 1;
		break;
	case 1:
		nowMapx = 10;
		char *p = mapx;
		*(p + 5) = '1';
		*(p + 6) = '0';
		*(p + 7) = '\0';		
		nowMapy = 10;
		p = mapy;
		*(p + 5) = '1';
		*(p + 6) = '0';
		*(p + 7) = '\0';		
		isFinish = 1;
	default:
		break;
	}
	if(MenuList1State[0] || MenuList1State[2] || MenuList2State[1] || MenuList2State[2] || MenuList2State[3]){
		isFinish = 1;
	}
	
	if(isFinish){
		canKUNdisplay = 1;
		MenuList2State[0] = 0;
		if(nowMapx > 30 || nowMapx < 10) nowMapx = 10;
		if(nowMapy > 30 || nowMapy < 10) nowMapy = 10;
		other = 1;
		isFinish = 0;
	}
}


/*****************
�˵��б����2-�༭��ͼ
*****************/
void menu2fun2()
{
	
	canMapdisplay = 1;
	canKUNdisplay = 1;
	static bool isFinish = 0;
	static bool other = 1; 
	if(other){
		MenuList2State[0] = 0;
		MenuList1State[0] = 0;
		other = 0;
	}	
	
	int X = 0, Y = 0;
	//�õ���ʼ����
	if(nowMapx % 2 == 0){
		mapStartX = 960 - (nowMapx / 2) * width;
	}else{
		mapStartX = 960 - (nowMapx / 2) * width - width / 2;
	}
	if(nowMapy % 2 == 0){
		mapStartY = 540 - (nowMapy / 2) * width;
	}else{
		mapStartY = 540 - (nowMapy / 2) * width - width / 2;
	}	
	//����任
	X = (int)((Mx - mapStartX) / width);
	Y = (int)((My - mapStartY) / width);
	
	int data = DrawMenu2fun2();
	
	
	if(Mx >= mapStartX && X <= nowMapx - 1 && Y >= 0 && Y <= nowMapy){
		switch (data)
		{
		case 0:
			/* code */
			break;
		case 1:
			if(isMClick) nowMap[Y][X].state = 0;  //�޸ĸ���Ϊ�հ�
			break;
		case 2:
			if(isMClick) nowMap[Y][X].state = 1;  //�޸ĸ���Ϊ�ϰ�
			break;
		case 3:
			if(isMClick){
				nowMap[startY - 1][startX - 1].state = 0;  //����Ϊ�հ�
				nowMap[Y][X].state = 2;  //�޸ĸ���Ϊ���
				startX = X + 1;  //ˢ�����
				startY = Y + 1;
			} 
			break;
		case 4:
			if(isMClick){
				nowMap[endY - 1][endX - 1].state = 0;  //�յ��Ϊ�հ�
				nowMap[Y][X].state = 3;  //�޸ĸ���Ϊ�յ�
				endX = X + 1;  //ˢ���յ�
				endY = Y + 1;
			}
			break;
		default:
			break;
		}

	}

	if(data == 5){
		if(isInMenu(0, 140, 70) && isMClick){
			int **reMaze = (int**)malloc((nowMapy) * sizeof(int *));
			for (int i = 0; i < nowMapy; i++) {
				reMaze[i] = (int*)calloc(nowMapx, sizeof(int));
			}
			randommap(reMaze, nowMapx, nowMapy);			
			for(int i = 0; i < nowMapy; i++){
				for(int j = 0; j < nowMapx; j++){
					nowMap[i][j].state = reMaze[i][j];
					if(reMaze[i][j] == 2){
						startX = j + 1;
						startY = i + 1;
					}else if(reMaze[i][j] == 3){
						endX = j + 1;
						endY = i + 1;
					}
				}
			}
			for (int i = 0; i < nowMapy; i++) free(reMaze[i]);
			free(reMaze);
		}		
	}

	if(MenuList2State[2] || MenuList2State[3] || MenuList2State[0] || MenuList1State[0] || MenuList1State[1]) isFinish = 1;

	if(isFinish){
		MenuList2State[1] = 0;
		other = 1;
		isFinish = 0;
	}
}

/*****************
�˵��б����3-�����ͼ
*****************/
void menu2fun3()
{
	canMapdisplay = 0;
	mapcopy(0);
	encode();
	MenuList2State[2] = 0;
}

/*****************
�˵��б����4-����
*****************/
void menu2fun4()
{
	canMapdisplay = 1;
	mapcopy(1);
	MenuList2State[3] = 0;
}

/*****************
�˵��б�����1-����
*****************/
void menu3fun1()
{
	
}