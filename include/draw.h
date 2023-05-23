#ifndef draw_h
#define draw_h

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
//#include "imgui.h"

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


typedef struct box{
	double x;  //一个格子的横坐标
	double y;  //一个格子的纵坐标（左下角坐标）
	int state;  //这个格子的状态：0是空 1是障碍 2是待编辑
} BOX;


void DrawKUN(double x, double y, int fps, bool direction);
void DrawStage(void);
void DrawMenu();
void DrawBox();
int DrawMenu2fun1();























#endif