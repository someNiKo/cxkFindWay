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
	double x;  //һ�����ӵĺ�����
	double y;  //һ�����ӵ������꣨���½����꣩
	int state;  //������ӵ�״̬��0�ǿ� 1���ϰ� 2�Ǵ��༭
} BOX;


void DrawKUN(double x, double y, int fps, bool direction);
void DrawStage(void);
void DrawMenu();
void DrawBox();
int DrawMenu2fun1();























#endif