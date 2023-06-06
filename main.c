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
#include <omp.h>  //openMP进行优化

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

typedef struct map{
	struct map *prev;  //上一个节点的地址
	BOX listMap[20][30];  //该节点的地图
	int X;
	int Y;
	int KUNX;
	int KUNY;
	bool canfind;
	struct map *next;  //下一个节点的地址
} Map;  //存贮历史地图数据的双向链表

Map *head = NULL, *end = NULL;

BOX nowMap[20][30];  //当前地图
BOX lastMap[20][30];  //上一个地图（用作撤销）

typedef enum{
    FPS,
    KUN_a,
	FPS_ALL,
	FLASH,
} Mytimer;

static bool isKUN_a = 0;  //坤是否可以加速
static bool fps_flag = 1;  //坤动画重播标志
static bool isCtrl = 0;  //ctrl键是否被按下
static bool canKUNdisplay = 1;  //drawKUN函数是否可以被调用
static bool canMapdisplay = 0;  //地图可以显示吗
static bool canKUNmove[4] = {1, 1, 1, 1};  //坤可以动吗？(0上1下2左3右)
static bool canfind = 0;  //可以机器求解吗

//来自draw.c:

extern double Mx, My;
extern bool isMClick;
extern bool MenuList1State[4];
extern bool MenuList2State[4];
extern bool MenuList3State;
extern bool isFlash;
extern bool isFlashing[10];

extern double mapStartX, mapStartY;
extern double width;

//传送给draw.c:
char mapx[10] = "宽度:10";
char mapy[10] = "高度:10";

//地图长宽
int nowMapx = 10;
int nowMapy = 10;
int startX, startY;  //起点坐标
int endX, endY;  //终点坐标

//消息回调函数声明

void KeyboardEventProcess(int key,int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

//画图函数声明

void display();

void DrawMenu();
void DrawBox();

void KUNmoveJUDGE();

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

	//初始化地图
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

	startTimer(FPS, 100);  //启动10fps/s计时器
	startTimer(KUN_a, 200);  //启动加速度定时器
	startTimer(FPS_ALL, 30);  //屏幕60帧定时器
	startTimer(FLASH, 400);  //启动光标闪烁定时器

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
字符消息回调函数
**********************/
void CharEventProcess(char c)
{
	//删除和回车见KeyBoardEvent
	if(isFlashing[0]){
		//得到宽度
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
		//得到高度
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
		KUNmoveJUDGE();
		break;    
	default:
        break;
    }
	return;
}

/*************
判断坤是否可移动
**************/
void KUNmoveJUDGE()
{
	if(canMapdisplay){
		//坐标变换
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
		//即将出界判断
		bool corrected = 1;
		//左方出界
		if(X < 0){
			canKUNmove[2] = 0;
			canKUNmove[3] = 1;
			corrected = 0;
		}
		//右方出界
		if(X > nowMapx - 1){
			canKUNmove[3] = 0;
			canKUNmove[2] = 1;
			corrected = 0;
		}
		//下方出界
		if(KUN.y - mapStartY < 20){
			canKUNmove[1] = 0;
			canKUNmove[0] = 1;
			corrected = 0;
		}
		//上方出界
		if(Y > nowMapy - 1){
			canKUNmove[0] = 0;
			canKUNmove[1] = 1;
			corrected = 0;
		}

	if(corrected){
		//当不是障碍物且头上是障碍
		if(Y + 1 <= nowMapy - 1 && nowMap[Y][X].state != 1 && nowMap[Y + 1][X].state == 1 ){		
			if((width - fmod(KUN.y - mapStartY, width)) <= 14){
				canKUNmove[0] = 0;
				canKUNmove[1] = 1;
				corrected = 0;
			}		
		}
		//当不是障碍物且下方是障碍
		if(Y - 1 >= 0 && nowMap[Y][X].state != 1 && nowMap[Y - 1][X].state == 1){		
			if(fmod(KUN.y - mapStartY - 15, width) <= 25){
				canKUNmove[1] = 0;
				canKUNmove[0] = 1;
				corrected = 0;		
			}		
		}
		//当不是障碍物且右方是障碍
		if(X + 1 <= nowMapx - 1 && nowMap[Y][X].state != 1 && nowMap[Y][X + 1].state == 1){		
			if((width - fmod(KUN.x - mapStartX, width)) <= 14){
				canKUNmove[3] = 0;
				canKUNmove[2] = 1;
				corrected = 0;		
			}		
		}
		//当不是障碍物且左方是障碍
		if(X - 1 >= 0 && nowMap[Y][X].state != 1 && nowMap[Y][X - 1].state == 1){		
			if(fmod(KUN.x - mapStartX, width) <= 14){
				canKUNmove[2] = 0;
				canKUNmove[3] = 1;
				corrected = 0;
			}		
		}																
	}
		//恢复
		if(corrected){
			canKUNmove[0] = 1;
			canKUNmove[1] = 1;
			canKUNmove[2] = 1;
			canKUNmove[3] = 1;
		}		
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

	//画舞台
	DrawStage();
    
    //画地图
	if(canMapdisplay) DrawBox();

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

	//menulist3
	if(MenuList3State) menu3fun1();
	
	//画坤
    if(canKUNdisplay){
		DrawKUN(KUN.x, KUN.y, KUN.fps, KUN.direction);
	} 

	//偶像练习生
	if(!canMapdisplay && !MenuList2State[0]){
		SetPenColor("Black");
		SetPointSize(150);
		SetFont("文道机械黑");
		MovePen(400, 300);
		DrawTextString("偶像练习生");
	}

}

/*********************工具********************/

/********************
将地图编码并保存
成功 return 1
失败 return 0
......
*********************/
bool encode()
{
	FILE *p;
	int X = 0, Y = 0;
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
	if((p = fopen("GameMap.txt", "a")) == NULL){
		p = fopen("GameMap.txt", "w");
		fprintf(p, "%d %d %2d %2d %d                                               \n", nowMapx, nowMapy, X, Y, canfind);
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 30; j++){
				fprintf(p, "%d ", nowMap[i][j].state);
			}
			fprintf(p, "\n");
		}
		fclose(p);
		return 1;  //没找到文件就新建一个
	}else{
		fprintf(p, "%d %d %2d %2d %d                                               \n", nowMapx, nowMapy, X, Y, canfind);
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
解码地图文件
成功 return *HEAD
失败 return NULL
***********************/
bool decode(FILE *fp)
{
	Map *mp = (Map *)malloc(sizeof(Map));
	if(head == NULL){  //第一次建立链表
		mp->prev = NULL;  //当前节点之前为空
		mp->next = NULL;  //当前之后节点为空
		end = mp;         //尾节点为当前节点
		head = mp;		  //头节点为当前节点
	}else{             //不是第一次建立链表
		mp->prev = end;   //当前节点之前为尾节点 
		mp->next = NULL;  //当前节点之后为空
		end->next = mp;   //尾节点下一个为当前节点
		end = mp;         //尾节点为当前节点
	}
	
	for(int i = 0; i < 21; i++){
		char str[62];
		char *pstr = str;
		fgets(str, 62, fp);
		if(i == 0){
			mp->X = *pstr - '0';
			pstr += 1;
			mp->X = mp->X * 10 + *pstr - '0';
			pstr += 2;
			
			mp->Y = *pstr - '0';
			pstr += 1;
			mp->Y = mp->Y * 10 + *pstr - '0';
			pstr += 1;
			while(*pstr == ' '){
				pstr += 1;
			}
			
			mp->KUNX = *pstr - '0';
			pstr += 1;
			if(*pstr >= '0' && *pstr <= '9'){
				mp->KUNX = mp->KUNX * 10 + *pstr - '0';
			}
			pstr += 1;
			while(*pstr == ' '){
				pstr += 1;
			}
			
			mp->KUNY = *pstr - '0';
			pstr += 1;
			if(*pstr >= '0' && *pstr <= '9'){
				mp->KUNY = mp->KUNY * 10 + *pstr - '0';
			}
			pstr += 1;
			while(*pstr == ' '){
				pstr += 1;
			}			
			
			mp->canfind = *pstr - '0';			
		}else{
			for(int j = 0; j < 30; j++){
				//处理地图数据
			mp->listMap[i - 1][j].state = *pstr - '0';
			mp->listMap[i - 1][j].x = j + 1;
			mp->listMap[i - 1][j].y = i;
			//移动字符串指针 pstr
			pstr += 2;
			}
		}
	}
	return 1;
}

/*******************
文件偏移量指向某行的工具
*********************/
void setOffsetToLineStart(FILE* file, int line, int lineLength)
{
    fseek(file, 0, SEEK_SET);  // 将文件指针移动到文件开头

    for (int i = 1; i < line; i++) {
        fseek(file, lineLength + 2, SEEK_CUR);  // 向后偏移 lineLength 个字节，并跳过换行符 '\n'
    }
}


/*********************
获取文件有效行数的工具
**********************/
int countValidLines(FILE* file)
{
    int count = 0;
    char buffer[100]; // 适当选择缓冲区大小

    // 逐行读取文件内容
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // 检查行是否有效
        // 这里可以根据实际需要添加更多的条件来判断行的有效性
        if (buffer[0] != '\n' && buffer[0] != '\0') {
            count++;
        }
    }

    // 返回有效行数
    return count;
}

/************
交换新老地图工具
**************/
void mapcopy(bool flag)
{
	if(flag){  //老->现在
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 30; j++){
				nowMap[i][j] = lastMap[i][j];
			}
		}
	}else{  //现在->老
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 30; j++){
				lastMap[i][j] = nowMap[i][j];
			}
		}			
	}
}

/***********************菜单功能***********************/
/*****************
菜单列表一：1-新的开始
*****************/
void menu1fun1()  
{
	static bool other = 1; 
	static bool flag = 1;
	if(other){
		MenuList2State[1] = 0;
		MenuList2State[0] = 0;
		MenuList1State[3] = 0;
		flag = 1;
		other = 0;
	}
	
	canKUNdisplay = 1;
	canMapdisplay = 1;
	
	static bool isFinish = 0;
	
	if(flag){
		//更改坤的初始位置  只执行一次
		KUN.x = mapStartX + startX * width - width/2;
		KUN.y = mapStartY + startY * width - width/2 + 15;
		flag = 0;		
	}	
	
	//坐标变换
	int X = 0, Y = 0;  //坤的矩阵坐标
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

	//结束条件判断
	static int times = 0;  //跑30次
	if(nowMap[Y][X].state == 3 && times <= 30){
		SetPenColor("MRed2");
		SetPointSize(200);
		SetFont("千图小兔体");
		MovePen(700, 500);
		DrawTextString("成功!");
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
		canfind = 0;
		if(showtimes >= 20){
			showtimes = 0;
			mapcopy(1);
			canKUNdisplay = 1;
			canfind = 1;
		}
	}

	static bool canfind1 = 0;
	int walls = 0;
	for(int i = 0; i < nowMapy; i++){
		for(int j = 0; j < nowMapx; j++){
			if(nowMap[i][j].state == 1){
				walls++;
			}
		}
	}

	if(max(abs(X + 1 - endX), abs(Y + 1 - endY)) <= 5 && canfind == 0 && ((double)walls/(double)(nowMapx*nowMapy) > 0.75)){
		canfind1 = 1;
	}else if(max(abs(X + 1 - endX), abs(Y + 1 - endY)) > 5 && canfind == 0){
		canfind1 = 0;
	}

	if(data && isMClick && (canfind || canfind1)){
		canKUNdisplay = 0;
		showtimes = 1;
		Findfun(Maze, data, X + 1, Y + 1);
		//保护数据
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
菜单列表一：2-重新开始
*****************/
void menu1fun2()
{
	MenuList1State[0] = 1;
	MenuList1State[1] = 0;  //只执行一次
}

/*****************
菜单列表一：3-保存游戏
*****************/
void menu1fun3()
{
	canMapdisplay = 0;
	mapcopy(0);
	encode();
	MenuList2State[2] = 0;
	exit(0);	
}

/*****************
菜单列表一：4-打开存档
*****************/
void menu1fun4()
{
	static bool other = 1; 
	if(other){
		MenuList2State[1] = 0;
		MenuList2State[0] = 0;
		MenuList1State[0] = 0;
		other = 0;
	}	
	
	canKUNdisplay = 1;
	canMapdisplay = 1;

	static bool isFinish = 0;

		
	//记得读取文件有效行数
	int data = DrawMenu1fun4();
	static Map *now = NULL, *lastnow = NULL;
	if(now == NULL){
		now = head;
	}
	if(now != lastnow){
		//得到起始坐标
		nowMapx = now->X;
		nowMapy = now->Y;
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
		
		//更改坤的初始位置  
		KUN.x = mapStartX + (now->KUNX + 1) * width - width/2;
		KUN.y = mapStartY + (now->KUNY + 1) * width - width/2 + 15;

		//是否可以寻路
		canfind = now->canfind;
		
		//复制地图
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 30; j++){
				nowMap[i][j] = now->listMap[i][j];
				if(nowMap[i][j].state == 2){
					startX = j + 1;
					startY = i + 1;
				}else if(nowMap[i][j].state == 3){
					endX = j + 1;
					endY = i + 1;
				}
			}
		}		
			
	}

	if(data && isMClick){
		FILE *fp = fopen("GameMap.txt", "r");
		rewind(fp);
		int maps = countValidLines(fp) / 21;
		for(int i = 0; i < maps; i++){
			setOffsetToLineStart(fp, 1 + 21 * i, 60);
			decode(fp);
		}
		fclose(fp);
		lastnow = now;
		if(now == NULL){
			now = head;
		}
		Map *p = head;
		switch (data)
		{
		case 1:  //next
			if(now->next != NULL) now = now->next;
			else now = head;
			break;
		case 2:  //prev
			if(now->prev != NULL) now = now->prev;
			else now = end;
			break;
		case 3:  //删除
			p = now;
			now->prev->next = now->next;
			now->next->prev = now->prev;
			now = now->prev;
			free(p);
			//删除文件中的没写			
			break;
		default:
			break;
		}
		
	}

	if(MenuList2State[2] || MenuList2State[3] || MenuList2State[0] || MenuList2State[1] || MenuList1State[0]) isFinish = 1;
	
	if(isFinish){
		now = NULL;
		lastnow = NULL;
		//free
		Map *p = head;
		Map *q;
		while(p != NULL){
			q = p;
			p = p->next;
			free(q);
		}		
		other = 1;
		canKUNdisplay = 0;
		canMapdisplay = 0;	
		isFinish = 0;
		MenuList1State[3] = 0;
	}	
}

/*****************
菜单列表二：1-创建地图
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
菜单列表二：2-编辑地图
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
	//得到起始坐标
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
	//坐标变换
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
			canfind = 0;
			if(isMClick) nowMap[Y][X].state = 0;  //修改格子为空白
			break;
		case 2:
			canfind = 0;
			if(isMClick) nowMap[Y][X].state = 1;  //修改格子为障碍
			break;
		case 3:
			canfind = 0;
			if(isMClick){
				nowMap[startY - 1][startX - 1].state = 0;  //起点改为空白
				nowMap[Y][X].state = 2;  //修改格子为起点
				startX = X + 1;  //刷新起点
				startY = Y + 1;
			} 
			break;
		case 4:
			canfind = 0;
			if(isMClick){
				nowMap[endY - 1][endX - 1].state = 0;  //终点改为空白
				nowMap[Y][X].state = 3;  //修改格子为终点
				endX = X + 1;  //刷新终点
				endY = Y + 1;
			}
			break;
		default:
			break;
		}

	}

	if(data == 5){
		canfind = 1;
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
菜单列表二：3-保存地图
*****************/
void menu2fun3()
{
	canMapdisplay = 0;
	mapcopy(0);
	encode();
	MenuList2State[2] = 0;
}

/*****************
菜单列表二：4-撤销
*****************/
void menu2fun4()
{
	canMapdisplay = 1;
	mapcopy(1);
	MenuList2State[3] = 0;
}

/*****************
菜单列表三：1-帮助
*****************/
void menu3fun1()
{
	char command[256];
    snprintf(command, sizeof(command), "start %s", "help.txt");
    system(command);
	MenuList3State = 0;
}