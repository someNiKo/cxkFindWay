#include "include/draw.h"
#include <math.h>

#define PI acos(-1)
#define kun_beidai_y 5*tan(PI/3)

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

}





















/*****************
画菜单函数
******************/
void DrawMenu()
{

}

/*****************
画按键函数
******************/
void DrawButton()
{

}

/*****************
画箱子函数
******************/
void DrawBox()
{
    
}