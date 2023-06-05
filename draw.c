#include "include/draw.h"
#include <math.h>
#include <string.h>

#define PI acos(-1)
#define kun_beidai_y 5*tan(PI/3)
#define TextCW TextStringWidth("啊")
#define TextEW TextStringWidth("A")

//坤动画的10帧
void fps0(double x, double y, bool direction);
void fps1(double x, double y, bool direction);
void fps2(double x, double y, bool direction);
void fps3(double x, double y, bool direction);
void fps4(double x, double y, bool direction);
void fps5(double x, double y, bool direction);
void fps6(double x, double y, bool direction);
void fps7(double x, double y, bool direction);
void fps8(double x, double y, bool direction);
void fps9(double x, double y, bool direction);

bool isInMenu(double x, double y, double high);
double MovingY(double y1, double y2, int t);
void DrawOneMenu(double x, double y, double high, char *color1, char *text, char *color2);

bool isInButton(double x, double y, double width, double high);
bool DrawOneButton(double x, double y, double width, double high, int pointsize, char *color, 
									char *color1, char *text, char *color2, bool isEditing, int ID);

bool isInBox(double x, double y, double width);
bool DrawOneBox(double x, double y, double width, int state, bool isChoosing);									

double Mx, My;  //鼠标位置
bool isMClick = 0;  //鼠标是否单击
bool isMenuList1 = 0;  //第一个菜单列表是否展开
bool isMenuList2 = 0;  //第二个菜单列表是否展开
bool isMenuList3 = 0;  //第三个菜单列表是否展开
bool MenuList1State[4] = {0};  //第一个菜单列表选项
bool MenuList2State[4] = {0};  //第二个菜单列表选项
bool MenuList3State = 0;  //第三个菜单列表选项

bool isFlash = 1;
bool isFlashing[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

double mapStartX = 1, mapStartY = 1;  //地图绘制开始的坐标
double width = 100;  //地图一个箱子宽度                  //这是我遇到过最离谱的BUG

//来自于main.c:
extern char mapx[10];
extern char mapy[10];
extern int nowMapx;
extern int nowMapy;
extern BOX nowMap[20][30];

/**************
传入坤的坐标和方向
***************/
void DrawKUN(double x, double y, int fps, bool direction)
{
	switch (fps)
	{
	case 0:
		fps0(x, y, direction);
		break;
	case 1:
		fps1(x, y, direction);
		break;
	case 2:
		fps2(x, y, direction);
		break;		
	case 3:
		fps3(x, y, direction);
		break;
	case 4:
		fps4(x, y, direction);
		break;
	case 5:
		fps5(x, y, direction);
		break;
	case 6:
		fps6(x, y, direction);
		break;
	case 7:
		fps7(x, y, direction);
		break;
	case 8:
		fps8(x, y, direction);
		break;
	case 9:
		fps9(x, y, direction);
		break;
	default:
		break;
	}
	return;	
}

void fps0(double x, double y, bool direction)
{	
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y);    //坤头半径为10像素
	DrawArc(10,0,360);
	
	//画左坤头
	MovePen(x,y+10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y+10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 12);
	DrawLine(-15, -10);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 15, y - 22);
	DrawArc(5, 0, 360);
	EndFilledRegion();

	//画右手
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10);
	DrawLine(15, -10);

	if(direction){
	//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15);
	DrawLine(-7, -7);
	DrawLine(7, -7);
	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15);
	DrawLine(-5, -7);
	DrawLine(5, -7);
	}else{
	//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15);
	DrawLine(7, -7);
	DrawLine(-7, -7);
	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15);
	DrawLine(5, -7);
	DrawLine(-5, -7);
	}
	return;
}

void fps1(double x, double y, bool direction)
{	
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 1);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 1);    //坤头半径为10像素
	DrawArc(10,0,360);	
	
	//画左坤头
	MovePen(x,y - 1 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y - 1 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y - 1;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y - 1;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 1);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 1);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 1);
	DrawLine(-14, -10.5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 11, y - 25);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//画右手
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10 - 1);
	DrawLine(14, -10.5);

	if(direction){
			//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 1);
	DrawLine(-8, -6.5);
	DrawLine(8, -6.5);
	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 1);
	DrawLine(-6, -6.5);
	DrawLine(6, -6.5);
	}else{
			//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 1);
	DrawLine(8, -6.5);
	DrawLine(-8, -6.5);
	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 1);
	DrawLine(6, -6.5);
	DrawLine(-6, -6.5);
	}
	return;	
}

void fps2(double x, double y, bool direction)
{
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 2);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 2);    //坤头半径为10像素
	DrawArc(10,0,360);
	
	//画左坤头
	MovePen(x,y - 2 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y - 2 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y - 2;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y - 2;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 2);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 2);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 2);
	DrawLine(-13, -11);

	//画右手
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10 - 2);
	DrawLine(13, -11);

	if(direction){
			//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 2);
	DrawLine(-9, -6);
	DrawLine(9, -6);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 8, y - 28);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//画右鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 2);
	DrawLine(-7, -6);
	DrawLine(7, -6);
	}else{
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 2);
	DrawLine(7, -6);
	DrawLine(-7, -6);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 8, y - 28);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//画左鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x - 6, y - kun_beidai_y - 15 - 2);
	DrawLine(9, -6);
	DrawLine(-9, -6);
	}
	return;
}

void fps3(double x, double y, bool direction)
{
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 3);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 3);    //坤头半径为10像素
	DrawArc(10,0,360);	
	
	//画左坤头
	MovePen(x,y - 3 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y - 3 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y - 3;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y - 3;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 3);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 3);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 3);
	DrawLine(-11.5, -12);

	//画右手
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10 - 3);
	DrawLine(11.5, -12);

	if(direction){
	//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 3);
	DrawLine(-10, -5.5);
	DrawLine(9, -5.5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 4, y - 32);
	DrawArc(5, 0, 360);
	EndFilledRegion();	
	
	//画右鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 3);
	DrawLine(-8, -5.5);
	DrawLine(7.5, -5.5);
	}else{
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 3);
	DrawLine(8, -5.5);
	DrawLine(-7.5, -5.5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 4, y - 32);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//画左鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x - 6, y - kun_beidai_y - 15 - 3);
	DrawLine(10, -5.5);
	DrawLine(-9, -5.5);
	}
	return;
}

void fps4(double x, double y, bool direction)
{
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 4);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 4);    //坤头半径为10像素
	DrawArc(10,0,360);	
	
	//画左坤头
	MovePen(x,y - 4 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y - 4 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y - 4;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y - 4;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 4);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 4);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 4);
	DrawLine(-10, -13);

	//画右手
	MovePen(x + 10, y - 10 - 4);
	DrawLine(10, -13);

	if(direction){
	//画左鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x - 6, y - kun_beidai_y - 15 - 4);
	DrawLine(-11, -5);
	DrawLine(9, -5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x, y - 35);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//画右鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 4);
	DrawLine(-9, -5);
	DrawLine(8, -5);
	}else{
	//画右鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 4);
	DrawLine(9, -5);
	DrawLine(-8, -5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x, y - 35);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//画左鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x - 6, y - kun_beidai_y - 15 - 4);
	DrawLine(11, -5);
	DrawLine(-9, -5);
	}
	return;
}

void fps5(double x, double y, bool direction)
{
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 4);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 4);    //坤头半径为10像素
	DrawArc(10,0,360);	
	
	//画左坤头
	MovePen(x,y - 4 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y - 4 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y - 4;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y - 4;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 4);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 4);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 4);
	DrawLine(-10, -13);

	//画右手
	MovePen(x + 10, y - 10 - 4);
	DrawLine(10, -13);

	if(direction){
	//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 4);
	DrawLine(-11, -5);
	DrawLine(9, -5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 2, y - 35);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//画右鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 4);
	DrawLine(-9, -5);
	DrawLine(8, -5);
	}else{	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 4);
	DrawLine(9, -5);
	DrawLine(-8, -5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 2, y - 35);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//画左鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x - 6, y - kun_beidai_y - 15 - 4);
	DrawLine(11, -5);
	DrawLine(-9, -5);	
	}
	return;
}

void fps6(double x, double y, bool direction)
{
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 3);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 3);    //坤头半径为10像素
	DrawArc(10,0,360);	
	
	//画左坤头
	MovePen(x,y - 3 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y - 3 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y - 3;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y - 3;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 3);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 3);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 3);
	DrawLine(-11.5, -12);

	//画右手
	MovePen(x + 10, y - 10 - 3);
	DrawLine(11.5, -12);

	if(direction){
			//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 3);
	DrawLine(-10, -5.5);
	DrawLine(9, -5.5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 8, y - 32);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//画右鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 3);
	DrawLine(-8, -5.5);
	DrawLine(7.5, -5.5);
	}else{
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 3);
	DrawLine(8, -5.5);
	DrawLine(-7.5, -5.5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 8, y - 32);
	DrawArc(5, 0, 360);
	EndFilledRegion();

	//画左鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x - 6, y - kun_beidai_y - 15 - 3);
	DrawLine(10, -5.5);
	DrawLine(-9, -5.5);
	}
	return;
}

void fps7(double x, double y, bool direction)
{
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 2);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 2);    //坤头半径为10像素
	DrawArc(10,0,360);
	
	//画左坤头
	MovePen(x,y - 2 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y - 2 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y - 2;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y - 2;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 2);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 2);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 2);
	DrawLine(-13, -11);

	//画右手
	MovePen(x + 10, y - 10 - 2);
	DrawLine(13, -11);

	if(direction){
			//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 2);
	DrawLine(-9, -6);
	DrawLine(9, -6);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 14, y - 28);
	DrawArc(5, 0, 360);
	EndFilledRegion();	
	
	//画右鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 2);
	DrawLine(-7, -6);
	DrawLine(7, -6);
	}else{
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 2);
	DrawLine(7, -6);
	DrawLine(-7, -6);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 14, y - 28);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//画左鸡脚
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x - 6, y - kun_beidai_y - 15 - 2);
	DrawLine(9, -6);
	DrawLine(-9, -6);
	}
	return;
}

void fps8(double x, double y, bool direction)
{
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 1);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 1);    //坤头半径为10像素
	DrawArc(10,0,360);
	
	//画左坤头
	MovePen(x,y - 1 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y - 1 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y - 1;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y - 1;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 1);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 1);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 1);
	DrawLine(-14, -10.5);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 20, y - 24);
	DrawArc(5, 0, 360);
	EndFilledRegion();

	//画右手
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10 - 1);
	DrawLine(14, -10.5);

	if(direction){
			//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 1);
	DrawLine(-8, -6.5);
	DrawLine(8, -6.5);
	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 1);
	DrawLine(-6, -6.5);
	DrawLine(6, -6.5);
	}else{
			//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15 - 1);
	DrawLine(8, -6.5);
	DrawLine(-8, -6.5);
	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15 - 1);
	DrawLine(6, -6.5);
	DrawLine(-6, -6.5);
	}
	return;
}

void fps9(double x, double y, bool direction)
{
	//画坤脸
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y);    //坤头半径为10像素
	DrawArc(10,0,360);
	
	//画左坤头
	MovePen(x,y+10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//画右坤头
	MovePen(x,y+10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//填充左坤头
	SetPenColor("Gray");
	double px = x-15, py = y;
	int i = 1;
	while(i < 5){
		MovePen(px + 1, py - 1);
		DrawLine(15 - i, 15 - i);
		px = px + 1;
		py = py - 1;
		i += 1;
	}
	
	//填充右坤头
	px = x+15; py = y;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//画背带裤
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y);
	DrawLine(0,-15);

	//画左手
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10);
	DrawLine(-15, -10);

	//篮球
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 26, y - 24);
	DrawArc(5, 0, 360);
	EndFilledRegion();

	//画右手
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10);
	DrawLine(15, -10);

	if(direction){
	//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15);
	DrawLine(-7, -7);
	DrawLine(7, -7);
	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15);
	DrawLine(-5, -7);
	DrawLine(5, -7);
	}else{
	//画左鸡脚
	MovePen(x - 6, y - kun_beidai_y - 15);
	DrawLine(7, -7);
	DrawLine(-7, -7);
	
	//画右鸡脚
	MovePen(x + 6, y - kun_beidai_y - 15);
	DrawLine(5, -7);
	DrawLine(-5, -7);
	}
	return;
}


void DrawStage(void)
{
	SetPenSize(1);
	SetPenColor("Purple");
	StartFilledRegion(1);
	MovePen(0, 1080);
	DrawLine(50, 0);
	DrawLine(250, -250);
	DrawLine(0, -150);
	DrawLine(-300, 300);
	DrawLine(0, 100);
	EndFilledRegion();

	StartFilledRegion(1);	
	SetPenSize(1);
	SetPenColor("MCyan");
	MovePen(30, 980 - 30);
	DrawLine(750, -750);
	DrawLine(-200, 0);
	DrawLine(-550, 550);
	DrawLine(0, 200);	
	EndFilledRegion();

	StartFilledRegion(1);
	SetPenColor("Wood");
	SetPenSize(1);
	MovePen(0, 200);
	DrawLine(1920, 0);
	DrawLine(0, -200);
	DrawLine(-1920, 0);
	DrawLine(0, 200);
	EndFilledRegion();
	return;
}

/*****************
画菜单函数
******************/
void DrawMenu()
{
	//绘制第一个菜单列表——“游戏”
	if(isInMenu(0, 980, 150) == 0){
		DrawOneMenu(0, 980, 150, "MLPink", "游戏", "White");
	}else{
		DrawOneMenu(0, 980, 150, "MDPink", "游戏", "White");
	}
	
	//绘制“游戏”菜单列表元素——“新的开始”、“重新开始”、“保存游戏”、“打开存档”
	if(isMClick && isMenuList1){
		if(isInMenu(30, 950, 150)) MenuList1State[0] = 1;
		if(isInMenu(60, 920, 150)) MenuList1State[1] = 1;
		if(isInMenu(90, 890, 150)) MenuList1State[2] = 1;
		if(isInMenu(120, 860, 150)) MenuList1State[3] = 1;
		isMenuList1 = 0;
	}

	if(isInMenu(0, 980, 150) && isMClick){
		DrawOneMenu(30, 950, 150, "MDPink", "新的开始", "Black");
		DrawOneMenu(60, 920, 150, "MDPink", "重新开始", "Black");
		DrawOneMenu(90, 890, 150, "MDPink", "保存游戏", "Black");
		DrawOneMenu(120, 860, 150, "MDPink", "打开存档", "Black");						
		isMenuList1 = 1;
	}
	
	if(isMenuList1){
		if(isInMenu(30, 950, 150) == 0){
			DrawOneMenu(30, 950, 150, "MLPink", "新的开始", "Black");
		}else{
			DrawOneMenu(30, 950, 150, "MDPink", "新的开始", "Black");
			DrawOneMenu(30, 800, 150, "MDPink", "CTRL+N", "Black");
		}

		if(isInMenu(60, 920, 150) == 0){
			DrawOneMenu(60, 920, 150, "MLPink", "重新开始", "Black");
		}else{
			DrawOneMenu(60, 920, 150, "MDPink", "重新开始", "Black");
			DrawOneMenu(60, 770, 150, "MDPink", "CTRL+M", "Black");			
		}

		if(isInMenu(90, 890, 150) == 0){
			DrawOneMenu(90, 890, 150, "MLPink", "保存游戏", "Black");
		}else{
			DrawOneMenu(90, 890, 150, "MDPink", "保存游戏", "Black");
			DrawOneMenu(90, 740, 150, "MDPink", "CTRL+I", "Black");
		}					
	
		if(isInMenu(120, 860, 150) == 0){
			DrawOneMenu(120, 860, 150, "MLPink", "打开存档", "Black");
		}else{
			DrawOneMenu(120, 860, 150, "MDPink", "打开存档", "Black");
			DrawOneMenu(120, 710, 150, "MDPink", "CTRL+O", "Black");			
		}	
	}


	//绘制第二个列表菜单——“工具”
	if(isInMenu(0, 830, 150) == 0){
		DrawOneMenu(0, 830, 150, "MLPink", "工具", "White");
	}else{
		DrawOneMenu(0, 830, 150, "MDPink", "工具", "White");
	}

	//绘制“工具”菜单列表元素——“创建地图”、“编辑地图”、“保存地图”、“撤销”
	if(isMClick && isMenuList2){
		if(isInMenu(30, 800, 150)) MenuList2State[0] = 1;
		if(isInMenu(60, 770, 150)) MenuList2State[1] = 1;
		if(isInMenu(90, 740, 150)) MenuList2State[2] = 1;
		if(isInMenu(120, 710, 150)) MenuList2State[3] = 1;
		isMenuList2 = 0;
	}

	if(isInMenu(0, 830, 150) && isMClick){
		DrawOneMenu(30, 800, 150, "MDPink", "创建地图", "Black");
		DrawOneMenu(60, 770, 150, "MDPink", "编辑地图", "Black");
		DrawOneMenu(90, 740, 150, "MDPink", "保存地图", "Black");
		DrawOneMenu(120, 710, 150, "MDPink", "撤销", "Black");						
		isMenuList2 = 1;
	}

	if(isMenuList2){
		if(isInMenu(30, 800, 150) == 0){
			DrawOneMenu(30, 800, 150, "MLPink", "创建地图", "Black");
		}else{
			DrawOneMenu(30, 800, 150, "MDPink", "创建地图", "Black");
			DrawOneMenu(30, 650, 150, "MDPink", "CTRL+J", "Black");
		}

		if(isInMenu(60, 770, 150) == 0){
			DrawOneMenu(60, 770, 150, "MLPink", "编辑地图", "Black");
		}else{
			DrawOneMenu(60, 770, 150, "MDPink", "编辑地图", "Black");
			DrawOneMenu(60, 620, 150, "MDPink", "CTRL+K", "Black");			
		}

		if(isInMenu(90, 740, 150) == 0){
			DrawOneMenu(90, 740, 150, "MLPink", "保存地图", "Black");
		}else{
			DrawOneMenu(90, 740, 150, "MDPink", "保存地图", "Black");
			DrawOneMenu(90, 590, 150, "MDPink", "CTRL+S", "Black");
		}					
	
		if(isInMenu(120, 710, 150) == 0){
			DrawOneMenu(120, 710, 150, "MLPink", "撤销", "Black");
		}else{
			DrawOneMenu(120, 710, 150, "MDPink", "撤销", "Black");
			DrawOneMenu(120, 560, 150, "MDPink", "CTRL+Z", "Black");			
		}	
	}

	//绘制第三个列表菜单——“帮助”
	if(isInMenu(0, 680, 150) == 0){
		DrawOneMenu(0, 680, 150, "MLPink", "帮助", "White");
	}else{
		DrawOneMenu(0, 680, 150, "MDPink", "帮助", "White");
		DrawOneMenu(30, 650, 150, "MDPink", "CTRL+H", "White");
	}

	if(isMClick && isInMenu(0, 680, 150)){
		MenuList3State = 1;
	}					

	return;
}

/****************
是否在某菜单选项内
*****************/
bool isInMenu(double x, double y, double high)
{
	if(Mx >= x && Mx <= x + 30 && My >= -1*(Mx - x) + y - high && My <= -1*(Mx - x) + y){
		return 1;
	}else{
		return 0;
	}
}

/*******************
试图做一个插值函数用于动画
*******************/
double MovingY(double y1, double y2, int t)
{
	return 0;
}

/*****************
绘制一个菜单选项
******************/
void DrawOneMenu(double x, double y, double high, char *color, char *text, char *color2)
{
	//画方块
	StartFilledRegion(1);	
	SetPenSize(1);
	SetPenColor(color);
	MovePen(x, y);
	DrawLine(30, -30);
	DrawLine(0, -1 * high);
	DrawLine(-30, 30);
	DrawLine(0, high);	
	EndFilledRegion();

	//画边框
	SetPenSize(3);
	SetPenColor("White");
	MovePen(x, y);
	DrawLine(30, -30);
	DrawLine(0, -1 * high);
	DrawLine(-30, 30);
	DrawLine(0, high);	

	if(*text == 'C'){
		//写英文
		int n = strlen(text);
		char s[2] = {'\0', '\0'};
		char *p = text;
		SetPenColor(color2);
		SetPointSize(20);
		SetFont("Stencil");
		for(int i = 1; i <= n; i++){
			s[0] = p[i - 1];
			MovePen(x + 15 - TextEW / 2, y - high / 2 + n / 2 * (TextEW + 3) - i * (TextEW + 3) - 15);
			DrawTextString(s);
		}
	}else{
		//写中文
		int n = strlen(text) / 2;  //获取字符串长度
		char s[3] = {'\0', '\0', '\0'};
		char *p = text;
		SetPenColor(color2);
		SetPointSize(20);
		SetFont("千图小兔体");
		for(int i = 1; i <= n; i++){
			s[0] = p[2 * (i - 1)];
			s[1] = p[2 * (i - 1) + 1];
			MovePen(x + 15 - TextCW / 2, y - high / 2 + n / 2 * TextCW - i * TextCW - 15);
			DrawTextString(s);
		}	
	}
	return;
}


/*****************
画一个按钮
******************/
bool DrawOneButton(double x, double y, double Width, double high, int pointsize, char *color, 
									char *color1, char *text, char *color2, bool isEditing, int ID)
{
	//画背景	
	if(isInButton(x, y, Width, high)){
		StartFilledRegion(1);	
		SetPenSize(1);
		SetPenColor(color1);
		MovePen(x, y);
		DrawLine(Width, 0);
		DrawLine(0, high);
		DrawLine(-1 * Width, 0);
		DrawLine(0, -1 * high);	
		EndFilledRegion();		
	}else{
		StartFilledRegion(1);	
		SetPenSize(1);
		SetPenColor(color);
		MovePen(x, y);
		DrawLine(Width, 0);
		DrawLine(0, high);
		DrawLine(-1 * Width, 0);
		DrawLine(0, -1 * high);	
		EndFilledRegion();
	}

	if(isEditing){
		char puttext[100] = {'\0'};
		char *p = puttext;
		int n = strlen(text);
		strcpy(puttext, text);	
		if(isInButton(x, y, Width, high) && isMClick){
			isFlashing[ID] = 1;
		}
		if((!isInButton(x, y, Width, high)) && isMClick){
			isFlashing[ID] = 0;
		}
		if(isFlashing[ID]){
			if(isFlash){
				*(p + n) = '_';
				*(p + n + 1) = '\0'; 
			}else{
				*(p + n) = ' ';
				*(p + n + 1) = '\0';
			}
		}
		//double w = TextStringWidth(puttext);
		SetPenColor(color2);
		SetPointSize(pointsize);
		SetFont("千图小兔体");
		MovePen(x + TextEW, y + (high - TextCW) / 2 + 5);
		DrawTextString(puttext);
		if(isInButton(x, y, Width, high) && isMClick){
			return 1;
		}
		return 0;
	}else{
		double w = TextStringWidth(text);
		SetPenColor(color2);
		SetPointSize(pointsize);
		SetFont("千图小兔体");
		MovePen(x + (Width - w) / 2, y + (high - TextCW) / 2 + 5);
		DrawTextString(text);
		if(isInButton(x, y, Width, high) && isMClick){
			return 0;
		}else{
			return 1;
		}
	}
}

/******************
是否在按钮内
*******************/
bool isInButton(double x, double y, double Width, double high)
{
	if(Mx >= x && My >= y && Mx <= x + Width && My <= y + high) return 1;
	else return 0;
}


/*****************
画箱子函数
******************/
void DrawBox()
{
    width = min(1800 / nowMapx, 1050 / nowMapy);
	double px, py;  //画笔坐标

	//初始化画笔坐标
	if(nowMapx % 2 == 0){
		px = 960 - (nowMapx / 2) * width;
		mapStartX = px;
	}else{
		px = 960 - (nowMapx / 2) * width - width / 2;
		mapStartX = px;
	}
	if(nowMapy % 2 == 0){
		py = 540 - (nowMapy / 2) * width;
		mapStartY = py;
	}else{
		py = 540 - (nowMapy / 2) * width - width / 2;
		mapStartY = py;
	}	

	//利用画笔画地图
	for(int i = 1; i <= nowMapy; i++){
		#pragma omp for
		for(int j = 1; j <= nowMapx; j++){
			DrawOneBox(px, py, width, nowMap[i-1][j-1].state, 0);
			px += width;
		}
		//返回行首
		if(nowMapx % 2 == 0){
			px = 960 - nowMapx / 2 * width;
		}else{
			px = 960 - nowMapx / 2 * width - width / 2;
		}
		py += width;
	}
}

/***************
画一个箱子
****************/
bool DrawOneBox(double x, double y, double Width, int state, bool isChoosing)
{
	//设置相应的颜色
	char *color;
	switch (state)
	{
	case 0:  //空的
		if(isInBox(x, y, Width) || isChoosing) color = "MGray2";
		else color = "MGray1";
		break;
	case 1:  //障碍
		if(isInBox(x, y, Width) || isChoosing) color = "MGreen1";
		else color = "MGreen2";
		break;
	case 2:  //起点
		if(isInBox(x, y, Width) || isChoosing) color = "MYellow1";
		else color = "MYellow2";
		break;
	case 3:  //终点
		if(isInBox(x, y, Width) || isChoosing) color = "MRed1";
		else color = "MRed2";
		break;
	default:  //路径
		if(isInBox(x, y, Width) || isChoosing) color = "MOrange1";
		else color = "MOrange2";		
		break;
	}

	//绘制方块
	StartFilledRegion(1);	
	SetPenSize(1);
	SetPenColor(color);
	MovePen(x, y);
	DrawLine(Width, 0);
	DrawLine(0, Width);
	DrawLine(-1 * Width, 0);
	DrawLine(0, -1 * Width);	
	EndFilledRegion();
	//绘制边框	
	if(isChoosing){
		SetPenSize(1);
		SetPenColor("Gray");
		MovePen(x, y);
		DrawLine(Width, 0);
		DrawLine(0, Width);
		DrawLine(-1 * Width, 0);
		DrawLine(0, -1 * Width);
	}else{
		SetPenSize(1);
		SetPenColor("MLPink");
		MovePen(x, y);
		DrawLine(Width, 0);
		DrawLine(0, Width);
		DrawLine(-1 * Width, 0);
		DrawLine(0, -1 * Width);		
	}
	if(isInBox(x, y, Width) && isMClick) return 1;
	else return 0;			
}

/***************
判断是否再箱子内
***************/
bool isInBox(double x, double y, double Width)
{
	if(Mx >= x && Mx <= x + Width && My >= y && My <= y + Width) return 1;
	else return 0;
}

/***************
绘制 创建地图 界面
*****************/
int DrawMenu2fun1()
{
	if(DrawOneButton(500, 70, 200, 40, 20, "MDPink", "MLPink", "确定", "White", 0, 0) == 0){
		if(isFlashing[0]) isFlashing[0] = 0;
		if(isFlashing[1]) isFlashing[1] = 0;
		return 0;  //单击了确定按钮
	}
	if(DrawOneButton(1220, 70, 200, 40, 20, "MDPink", "MLPink", "取消", "White", 0, 0) == 0){
		return 1;  //单击了取消按钮
	}
	DrawOneButton(600, 330, 710, 40, 20, "MLPink", "MLPink", "（长度范围: 10~30    高度范围: 10~20）", "White", 0, 0);
	
	if(isFlashing[0] == 0){
		if(nowMapx > 30){
			char *p = mapx;
			nowMapx = 30;
			*(p + 5) = '3';
			*(p + 6) = '0';
			*(p + 7) = '\0';
		}else if(nowMapx < 10){
			char *p = mapx;
			nowMapx = 10;
			*(p + 5) = '1';
			*(p + 6) = '0';
			*(p + 7) = '\0';			
		}
	}
	if(isFlashing[1] == 0){
		if(nowMapy > 20){
			char *p = mapy;
			nowMapy = 20;
			*(p + 5) = '2';
			*(p + 6) = '0';
			*(p + 7) = '\0';
		}else if(nowMapy < 10){
			char *p = mapy;
			nowMapy = 10;
			*(p + 5) = '1';
			*(p + 6) = '0';
			*(p + 7) = '\0';			
		}
	}	

	static int f = 0; 
	if(DrawOneButton(600, 400, 230, 60, 28, "MDPink", "MLPink", mapx, "White", 1, 0) == 1){
		f = 2;  //单击了输入框1
	}
	if(DrawOneButton(1080, 400, 230, 60, 28, "MDPink", "MLPink", mapy, "White", 1, 1) == 1){
		f = 3;  //单击了输入框2
	}	
	
	
	switch (f)
	{
	case 2:
		return 2;
		break;
	case 3:
		return 3;
	default:
		break;
	}
	return 5;
}

/***************
绘制编辑一个提示语
*****************/
void DrawOneTips(double x, double y, double high, char *color, char *text, char *color2, bool ischoose)
{
	//画方块
	StartFilledRegion(1);	
	SetPenSize(1);
	SetPenColor(color);
	MovePen(x, y);
	DrawLine(30, -30);
	DrawLine(0, -1 * high);
	DrawLine(-30, 30);
	DrawLine(0, high);	
	EndFilledRegion();

	//画边框
	//非选中情况
	if(!ischoose){
		SetPenSize(3);
		SetPenColor("MCyan");
		MovePen(x, y);
		DrawLine(30, -30);
		DrawLine(0, -1 * high);
		DrawLine(-30, 30);
		DrawLine(0, high);
	}else{
		SetPenSize(3);
		SetPenColor("Purple");
		MovePen(x, y);
		DrawLine(30, -30);
		DrawLine(0, -1 * high);
		DrawLine(-30, 30);
		DrawLine(0, high);
	}

	//写文字
	int n = strlen(text) / 2;  //获取字符串长度
	char s[3] = {'\0', '\0', '\0'};
	char *p = text;
	SetPenColor(color2);
	SetPointSize(20);
	SetFont("千图小兔体");
	for(int i = 1; i <= n; i++){
		s[0] = p[2 * (i - 1)];
		s[1] = p[2 * (i - 1) + 1];
		MovePen(x + 15 - TextCW / 2, y - high / 2 + n / 2 * TextCW - i * TextCW - 15);
		DrawTextString(s);
	}		
}

/***************
绘制 编辑地图 界面
*****************/
int DrawMenu2fun2()
{
	static bool isEditing[5] = {0, 0, 0, 0, 0};
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
	bool flag = 0;  //鼠标是否在地图内
	if(Mx >= mapStartX && X <= nowMapx - 1 && Y >= 0 && Y <= nowMapy) flag = 1;
	//更改编辑状态
	if((isInMenu(0, 420, 70) && isMClick) || (flag && isEditing[0])){
		isEditing[0] = 1;
		isEditing[1] = 0;
		isEditing[2] = 0;
		isEditing[3] = 0;
		isEditing[4] = 0;
	}else if((isInMenu(0, 350, 70) && isMClick) || (flag && isEditing[1])){
		isEditing[0] = 0;
		isEditing[1] = 1;
		isEditing[2] = 0;
		isEditing[3] = 0;
		isEditing[4] = 0;		
	}else if((isInMenu(0, 280, 70) && isMClick) || (flag && isEditing[2])){
		isEditing[0] = 0;
		isEditing[1] = 0;
		isEditing[2] = 1;
		isEditing[3] = 0;
		isEditing[4] = 0;		
	}else if((isInMenu(0, 210, 70) && isMClick) || (flag && isEditing[3])){
		isEditing[0] = 0;
		isEditing[1] = 0;
		isEditing[2] = 0;
		isEditing[3] = 1;
		isEditing[4] = 0;		
	}else if((isInMenu(0, 140, 70) && isMClick) || (flag && isEditing[4])){
		isEditing[0] = 0;
		isEditing[1] = 0;
		isEditing[2] = 0;
		isEditing[3] = 0;
		isEditing[4] = 1;			
	}else if(isMClick){
		isEditing[0] = 0;
		isEditing[1] = 0;
		isEditing[2] = 0;
		isEditing[3] = 0;
		isEditing[4] = 0;		
	}
			
	//画提示方块
	if(isInMenu(0, 420, 70) == 0){
		DrawOneTips(0, 420, 70, "MGray1", "空白", "Black", isEditing[0]);
	}else{
		DrawOneTips(0, 420, 70, "MGray2", "空白", "Black", isEditing[0]);
	}
	if(isInMenu(0, 350, 70) == 0){
		DrawOneTips(0, 350, 70, "MGreen2", "障碍", "White", isEditing[1]);
	}else{
		DrawOneTips(0, 350, 70, "MGreen1", "障碍", "White", isEditing[1]);
	}	
	if(isInMenu(0, 280, 70) == 0){
		DrawOneTips(0, 280, 70, "MYellow2", "起点", "Black", isEditing[2]);
	}else{
		DrawOneTips(0, 280, 70, "MYellow1", "起点", "Black", isEditing[2]);
	}
	if(isInMenu(0, 210, 70) == 0){
		DrawOneTips(0, 210, 70, "MRed2", "终点", "Black", isEditing[3]);
	}else{
		DrawOneTips(0, 210, 70, "MRed1", "终点", "Black", isEditing[3]);
	}
	if(isInMenu(0, 140, 70) == 0){
		DrawOneTips(0, 140, 70, "Black", "随机", "White", isEditing[4]);
	}else{
		DrawOneTips(0, 140, 70, "White", "随机", "Black", isEditing[4]);
	}

	if(isEditing[0]){
		return 1;  //空白
	}else if(isEditing[1]){
		return 2;  //障碍
	}else if(isEditing[2]){
		return 3;  //起点
	}else if(isEditing[3]){
		return 4;  //终点
	}else if(isEditing[4]){
		return 5;  //随机
	}else{
		return 0;
	}
}

/***************
绘制 开始游戏 界面
*****************/
int DrawMenu1fun1()
{
	static bool isEditing[3] = {0, 0, 0};
	
	if((isInMenu(0, 420, 70)) && isMClick){
		isEditing[0] = 1;
		isEditing[1] = 0;
		isEditing[2] = 0;
	}else if((isInMenu(0, 350, 70)) && isMClick){
		isEditing[0] = 0;
		isEditing[1] = 1;
		isEditing[2] = 0;		
	}else if((isInMenu(0, 280, 70)) && isMClick){
		isEditing[0] = 0;
		isEditing[1] = 0;
		isEditing[2] = 1;		
	}else if(isMClick){
		isEditing[0] = 0;
		isEditing[1] = 0;
		isEditing[2] = 0;		
	}

	
	//画提示方块
	if(isInMenu(0, 420, 70) == 0){
		DrawOneTips(0, 420, 70, "MOrange1", "提示", "White", isEditing[0]);
	}else{
		DrawOneTips(0, 420, 70, "MOrange2", "提示", "White", isEditing[0]);
	}
	if(isInMenu(0, 350, 70) == 0){
		DrawOneTips(0, 350, 70, "Morange1", "最短", "White", isEditing[1]);
	}else{
		DrawOneTips(0, 350, 70, "MOrange2", "最短", "White", isEditing[1]);
	}	
	if(isInMenu(0, 280, 70) == 0){
		DrawOneTips(0, 280, 70, "MOrange1", "其他", "White", isEditing[2]);
	}else{
		DrawOneTips(0, 280, 70, "MOrange2", "其他", "White", isEditing[2]);
	}

	
	static bool iscontine = 0;
	if(isMClick == 0) iscontine = 0;
	if((isEditing[0] || isEditing[1] || isEditing[2]) && iscontine){
		return 0;
	}
	if(isMClick) iscontine = 1;

	if(isEditing[0]){
		return 1;  //提示
	}else if(isEditing[1]){
		return 2;  //最短
	}else if(isEditing[2]){
		return 3;  //其他
	}else{
		return 0;
	}
}