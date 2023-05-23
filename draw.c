#include "include/draw.h"
#include <math.h>
#include <string.h>

#define PI acos(-1)
#define kun_beidai_y 5*tan(PI/3)
#define TextCW TextStringWidth("��")
#define TextEW TextStringWidth("A")

//��������10֡
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

double Mx, My;  //���λ��
bool isMClick = 0;  //����Ƿ񵥻�
bool isMenuList1 = 0;  //��һ���˵��б��Ƿ�չ��
bool isMenuList2 = 0;  //�ڶ����˵��б��Ƿ�չ��
bool isMenuList3 = 0;  //�������˵��б��Ƿ�չ��
bool MenuList1State[4] = {0};  //��һ���˵��б�ѡ��
bool MenuList2State[4] = {0};  //�ڶ����˵��б�ѡ��
bool MenuList3State = 0;  //�������˵��б�ѡ��

bool isFlash = 1;
bool isFlashing[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//������main.c:
extern char mapx[10];
extern char mapy[10];
extern int nowMapx;
extern int nowMapy;
extern BOX nowMap[35][60];


/**************
������������ͷ���
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
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);
	
	//������ͷ
	MovePen(x,y+10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y+10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 12);
	DrawLine(-15, -10);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 15, y - 22);
	DrawArc(5, 0, 360);
	EndFilledRegion();

	//������
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10);
	DrawLine(15, -10);

	if(direction){
	//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15);
	DrawLine(-7, -7);
	DrawLine(7, -7);
	
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15);
	DrawLine(-5, -7);
	DrawLine(5, -7);
	}else{
	//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15);
	DrawLine(7, -7);
	DrawLine(-7, -7);
	
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15);
	DrawLine(5, -7);
	DrawLine(-5, -7);
	}
	return;
}

void fps1(double x, double y, bool direction)
{	
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 1);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 1);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);	
	
	//������ͷ
	MovePen(x,y - 1 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y - 1 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y - 1;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 1);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 1);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 1);
	DrawLine(-14, -10.5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 11, y - 25);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//������
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10 - 1);
	DrawLine(14, -10.5);

	if(direction){
			//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 1);
	DrawLine(-8, -6.5);
	DrawLine(8, -6.5);
	
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 1);
	DrawLine(-6, -6.5);
	DrawLine(6, -6.5);
	}else{
			//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 1);
	DrawLine(8, -6.5);
	DrawLine(-8, -6.5);
	
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 1);
	DrawLine(6, -6.5);
	DrawLine(-6, -6.5);
	}
	return;	
}

void fps2(double x, double y, bool direction)
{
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 2);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 2);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);
	
	//������ͷ
	MovePen(x,y - 2 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y - 2 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y - 2;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 2);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 2);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 2);
	DrawLine(-13, -11);

	//������
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10 - 2);
	DrawLine(13, -11);

	if(direction){
			//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 2);
	DrawLine(-9, -6);
	DrawLine(9, -6);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 8, y - 28);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//���Ҽ���
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 2);
	DrawLine(-7, -6);
	DrawLine(7, -6);
	}else{
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 2);
	DrawLine(7, -6);
	DrawLine(-7, -6);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 8, y - 28);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//���󼦽�
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
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 3);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 3);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);	
	
	//������ͷ
	MovePen(x,y - 3 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y - 3 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y - 3;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 3);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 3);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 3);
	DrawLine(-11.5, -12);

	//������
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10 - 3);
	DrawLine(11.5, -12);

	if(direction){
	//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 3);
	DrawLine(-10, -5.5);
	DrawLine(9, -5.5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 4, y - 32);
	DrawArc(5, 0, 360);
	EndFilledRegion();	
	
	//���Ҽ���
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 3);
	DrawLine(-8, -5.5);
	DrawLine(7.5, -5.5);
	}else{
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 3);
	DrawLine(8, -5.5);
	DrawLine(-7.5, -5.5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x - 4, y - 32);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//���󼦽�
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
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 4);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 4);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);	
	
	//������ͷ
	MovePen(x,y - 4 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y - 4 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y - 4;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 4);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 4);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 4);
	DrawLine(-10, -13);

	//������
	MovePen(x + 10, y - 10 - 4);
	DrawLine(10, -13);

	if(direction){
	//���󼦽�
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x - 6, y - kun_beidai_y - 15 - 4);
	DrawLine(-11, -5);
	DrawLine(9, -5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x, y - 35);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//���Ҽ���
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 4);
	DrawLine(-9, -5);
	DrawLine(8, -5);
	}else{
	//���Ҽ���
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 4);
	DrawLine(9, -5);
	DrawLine(-8, -5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x, y - 35);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//���󼦽�
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
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 4);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 4);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);	
	
	//������ͷ
	MovePen(x,y - 4 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y - 4 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y - 4;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 4);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 4);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 4);
	DrawLine(-10, -13);

	//������
	MovePen(x + 10, y - 10 - 4);
	DrawLine(10, -13);

	if(direction){
	//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 4);
	DrawLine(-11, -5);
	DrawLine(9, -5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 2, y - 35);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//���Ҽ���
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 4);
	DrawLine(-9, -5);
	DrawLine(8, -5);
	}else{	
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 4);
	DrawLine(9, -5);
	DrawLine(-8, -5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 2, y - 35);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//���󼦽�
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
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 3);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 3);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);	
	
	//������ͷ
	MovePen(x,y - 3 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y - 3 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y - 3;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 3);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 3);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 3);
	DrawLine(-11.5, -12);

	//������
	MovePen(x + 10, y - 10 - 3);
	DrawLine(11.5, -12);

	if(direction){
			//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 3);
	DrawLine(-10, -5.5);
	DrawLine(9, -5.5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 8, y - 32);
	DrawArc(5, 0, 360);
	EndFilledRegion();
	
	//���Ҽ���
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 3);
	DrawLine(-8, -5.5);
	DrawLine(7.5, -5.5);
	}else{
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 3);
	DrawLine(8, -5.5);
	DrawLine(-7.5, -5.5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 8, y - 32);
	DrawArc(5, 0, 360);
	EndFilledRegion();

	//���󼦽�
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
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 2);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 2);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);
	
	//������ͷ
	MovePen(x,y - 2 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y - 2 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y - 2;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 2);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 2);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 2);
	DrawLine(-13, -11);

	//������
	MovePen(x + 10, y - 10 - 2);
	DrawLine(13, -11);

	if(direction){
			//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 2);
	DrawLine(-9, -6);
	DrawLine(9, -6);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 14, y - 28);
	DrawArc(5, 0, 360);
	EndFilledRegion();	
	
	//���Ҽ���
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 6, y - kun_beidai_y - 15 - 2);
	DrawLine(-7, -6);
	DrawLine(7, -6);
	}else{
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 2);
	DrawLine(7, -6);
	DrawLine(-7, -6);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 14, y - 28);
	DrawArc(5, 0, 360);
	EndFilledRegion();	

	//���󼦽�
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
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y - 1);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y - 1);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);
	
	//������ͷ
	MovePen(x,y - 1 + 10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y - 1 + 10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y - 1;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y - 1);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y - 1);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10 - 1);
	DrawLine(-14, -10.5);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 20, y - 24);
	DrawArc(5, 0, 360);
	EndFilledRegion();

	//������
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10 - 1);
	DrawLine(14, -10.5);

	if(direction){
			//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 1);
	DrawLine(-8, -6.5);
	DrawLine(8, -6.5);
	
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 1);
	DrawLine(-6, -6.5);
	DrawLine(6, -6.5);
	}else{
			//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15 - 1);
	DrawLine(8, -6.5);
	DrawLine(-8, -6.5);
	
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15 - 1);
	DrawLine(6, -6.5);
	DrawLine(-6, -6.5);
	}
	return;
}

void fps9(double x, double y, bool direction)
{
	//������
	StartFilledRegion(1);
	SetPenColor("Face");
	SetPenSize(2);	
	MovePen(x+9,y);
	DrawArc(9,0,360);
	EndFilledRegion();		
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x+10,y);    //��ͷ�뾶Ϊ10����
	DrawArc(10,0,360);
	
	//������ͷ
	MovePen(x,y+10);
	DrawLine(0,5);
	DrawLine(-15,-15);
	DrawLine(5,-5);
	DrawLine(10,10);
	DrawLine(0,5);
	
	//������ͷ
	MovePen(x,y+10);
	DrawLine(0,5);
	DrawLine(15,-15);
	DrawLine(-5,-5);
	DrawLine(-10,10);
	DrawLine(0,5);

	//�������ͷ
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
	
	//�������ͷ
	px = x+15; py = y;
	i=1;
	while(i < 5){
		MovePen(px - 1, py - 1);
		DrawLine(-(15 - i), 15 - i);
		px = px - 1;
		py = py - 1;
		i += 1;
	}

	//��������
	SetPenColor("DYellow");
	SetPenSize(2);
	MovePen(x - 5, y - kun_beidai_y);
	DrawLine(0,-15);

	MovePen(x + 5, y - kun_beidai_y);
	DrawLine(0,-15);

	//������
	SetPenColor("Black");
	SetPenSize(2);
	MovePen(x - 10, y - 10);
	DrawLine(-15, -10);

	//����
	SetPenColor("Orange");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(x + 26, y - 24);
	DrawArc(5, 0, 360);
	EndFilledRegion();

	//������
	SetPenColor("Black");
	SetPenSize(2);	
	MovePen(x + 10, y - 10);
	DrawLine(15, -10);

	if(direction){
	//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15);
	DrawLine(-7, -7);
	DrawLine(7, -7);
	
	//���Ҽ���
	MovePen(x + 6, y - kun_beidai_y - 15);
	DrawLine(-5, -7);
	DrawLine(5, -7);
	}else{
	//���󼦽�
	MovePen(x - 6, y - kun_beidai_y - 15);
	DrawLine(7, -7);
	DrawLine(-7, -7);
	
	//���Ҽ���
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
���˵�����
******************/
void DrawMenu()
{
	//���Ƶ�һ���˵��б�������Ϸ��
	if(isInMenu(0, 980, 150) == 0){
		DrawOneMenu(0, 980, 150, "MLPink", "��Ϸ", "White");
	}else{
		DrawOneMenu(0, 980, 150, "MDPink", "��Ϸ", "White");
	}
	
	//���ơ���Ϸ���˵��б�Ԫ�ء������µĿ�ʼ���������¿�ʼ������������Ϸ�������򿪴浵��
	if(isMClick && isMenuList1){
		if(isInMenu(30, 950, 150)) MenuList1State[0] = 1;
		if(isInMenu(60, 920, 150)) MenuList1State[1] = 1;
		if(isInMenu(90, 890, 150)) MenuList1State[2] = 1;
		if(isInMenu(120, 860, 150)) MenuList1State[3] = 1;
		isMenuList1 = 0;
	}

	if(isInMenu(0, 980, 150) && isMClick){
		DrawOneMenu(30, 950, 150, "MDPink", "�µĿ�ʼ", "Black");
		DrawOneMenu(60, 920, 150, "MDPink", "���¿�ʼ", "Black");
		DrawOneMenu(90, 890, 150, "MDPink", "������Ϸ", "Black");
		DrawOneMenu(120, 860, 150, "MDPink", "�򿪴浵", "Black");						
		isMenuList1 = 1;
	}
	
	if(isMenuList1){
		if(isInMenu(30, 950, 150) == 0){
			DrawOneMenu(30, 950, 150, "MLPink", "�µĿ�ʼ", "Black");
		}else{
			DrawOneMenu(30, 950, 150, "MDPink", "�µĿ�ʼ", "Black");
			DrawOneMenu(30, 800, 150, "MDPink", "CTRL+N", "Black");
		}

		if(isInMenu(60, 920, 150) == 0){
			DrawOneMenu(60, 920, 150, "MLPink", "���¿�ʼ", "Black");
		}else{
			DrawOneMenu(60, 920, 150, "MDPink", "���¿�ʼ", "Black");
			DrawOneMenu(60, 770, 150, "MDPink", "CTRL+M", "Black");			
		}

		if(isInMenu(90, 890, 150) == 0){
			DrawOneMenu(90, 890, 150, "MLPink", "������Ϸ", "Black");
		}else{
			DrawOneMenu(90, 890, 150, "MDPink", "������Ϸ", "Black");
			DrawOneMenu(90, 740, 150, "MDPink", "CTRL+I", "Black");
		}					
	
		if(isInMenu(120, 860, 150) == 0){
			DrawOneMenu(120, 860, 150, "MLPink", "�򿪴浵", "Black");
		}else{
			DrawOneMenu(120, 860, 150, "MDPink", "�򿪴浵", "Black");
			DrawOneMenu(120, 710, 150, "MDPink", "CTRL+O", "Black");			
		}	
	}


	//���Ƶڶ����б�˵����������ߡ�
	if(isInMenu(0, 830, 150) == 0){
		DrawOneMenu(0, 830, 150, "MLPink", "����", "White");
	}else{
		DrawOneMenu(0, 830, 150, "MDPink", "����", "White");
	}

	//���ơ����ߡ��˵��б�Ԫ�ء�����������ͼ�������༭��ͼ�����������ͼ������������
	if(isMClick && isMenuList2){
		if(isInMenu(30, 800, 150)) MenuList2State[0] = 1;
		if(isInMenu(60, 770, 150)) MenuList2State[1] = 1;
		if(isInMenu(90, 740, 150)) MenuList2State[2] = 1;
		if(isInMenu(120, 710, 150)) MenuList2State[3] = 1;
		isMenuList2 = 0;
	}

	if(isInMenu(0, 830, 150) && isMClick){
		DrawOneMenu(30, 800, 150, "MDPink", "������ͼ", "Black");
		DrawOneMenu(60, 770, 150, "MDPink", "�༭��ͼ", "Black");
		DrawOneMenu(90, 740, 150, "MDPink", "�����ͼ", "Black");
		DrawOneMenu(120, 710, 150, "MDPink", "����", "Black");						
		isMenuList2 = 1;
	}

	if(isMenuList2){
		if(isInMenu(30, 800, 150) == 0){
			DrawOneMenu(30, 800, 150, "MLPink", "������ͼ", "Black");
		}else{
			DrawOneMenu(30, 800, 150, "MDPink", "������ͼ", "Black");
			DrawOneMenu(30, 650, 150, "MDPink", "CTRL+J", "Black");
		}

		if(isInMenu(60, 770, 150) == 0){
			DrawOneMenu(60, 770, 150, "MLPink", "�༭��ͼ", "Black");
		}else{
			DrawOneMenu(60, 770, 150, "MDPink", "�༭��ͼ", "Black");
			DrawOneMenu(60, 620, 150, "MDPink", "CTRL+K", "Black");			
		}

		if(isInMenu(90, 740, 150) == 0){
			DrawOneMenu(90, 740, 150, "MLPink", "�����ͼ", "Black");
		}else{
			DrawOneMenu(90, 740, 150, "MDPink", "�����ͼ", "Black");
			DrawOneMenu(90, 590, 150, "MDPink", "CTRL+S", "Black");
		}					
	
		if(isInMenu(120, 710, 150) == 0){
			DrawOneMenu(120, 710, 150, "MLPink", "����", "Black");
		}else{
			DrawOneMenu(120, 710, 150, "MDPink", "����", "Black");
			DrawOneMenu(120, 560, 150, "MDPink", "CTRL+Z", "Black");			
		}	
	}

	//���Ƶڶ����б�˵����������ߡ�
	if(isInMenu(0, 680, 150) == 0){
		DrawOneMenu(0, 680, 150, "MLPink", "����", "White");
	}else{
		DrawOneMenu(0, 680, 150, "MDPink", "����", "White");
		DrawOneMenu(30, 650, 150, "MDPink", "CTRL+H", "White");
	}

	if(isMClick && isInMenu(0, 680, 150)){
		MenuList3State = 1;
	}					

	return;
}

/****************
�Ƿ���ĳ�˵�ѡ����
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
��ͼ��һ����ֵ�������ڶ���
*******************/
double MovingY(double y1, double y2, int t)
{
	return 0;
}

/*****************
����һ���˵�ѡ��
******************/
void DrawOneMenu(double x, double y, double high, char *color, char *text, char *color2)
{
	//������
	StartFilledRegion(1);	
	SetPenSize(1);
	SetPenColor(color);
	MovePen(x, y);
	DrawLine(30, -30);
	DrawLine(0, -1 * high);
	DrawLine(-30, 30);
	DrawLine(0, high);	
	EndFilledRegion();

	//���߿�
	SetPenSize(3);
	SetPenColor("White");
	MovePen(x, y);
	DrawLine(30, -30);
	DrawLine(0, -1 * high);
	DrawLine(-30, 30);
	DrawLine(0, high);	

	if(*text == 'C'){
		//дӢ��
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
		//д����
		int n = strlen(text) / 2;  //��ȡ�ַ�������
		char s[3] = {'\0', '\0', '\0'};
		char *p = text;
		SetPenColor(color2);
		SetPointSize(20);
		SetFont("ǧͼС����");
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
��һ����ť
******************/
bool DrawOneButton(double x, double y, double width, double high, int pointsize, char *color, 
									char *color1, char *text, char *color2, bool isEditing, int ID)
{
	//������	
	if(isInButton(x, y, width, high)){
		StartFilledRegion(1);	
		SetPenSize(1);
		SetPenColor(color1);
		MovePen(x, y);
		DrawLine(width, 0);
		DrawLine(0, high);
		DrawLine(-1 * width, 0);
		DrawLine(0, -1 * high);	
		EndFilledRegion();		
	}else{
		StartFilledRegion(1);	
		SetPenSize(1);
		SetPenColor(color);
		MovePen(x, y);
		DrawLine(width, 0);
		DrawLine(0, high);
		DrawLine(-1 * width, 0);
		DrawLine(0, -1 * high);	
		EndFilledRegion();
	}

	if(isEditing){
		char puttext[100] = {'\0'};
		char *p = puttext;
		int n = strlen(text);
		strcpy(puttext, text);	
		if(isInButton(x, y, width, high) && isMClick){
			isFlashing[ID] = 1;
		}
		if((!isInButton(x, y, width, high)) && isMClick){
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
		SetFont("ǧͼС����");
		MovePen(x + TextEW, y + (high - TextCW) / 2 + 5);
		DrawTextString(puttext);
		if(isInButton(x, y, width, high) && isMClick){
			return 1;
		}
		return 0;
	}else{
		double w = TextStringWidth(text);
		SetPenColor(color2);
		SetPointSize(pointsize);
		SetFont("ǧͼС����");
		MovePen(x + (width - w) / 2, y + (high - TextCW) / 2 + 5);
		DrawTextString(text);
		if(isInButton(x, y, width, high) && isMClick){
			return 0;
		}else{
			return 1;
		}
	}
}

/******************
�Ƿ��ڰ�ť��
*******************/
bool isInButton(double x, double y, double width, double high)
{
	if(Mx >= x && My >= y && Mx <= x + width && My <= y + high) return 1;
	else return 0;
}


/*****************
�����Ӻ���
******************/
void DrawBox()
{
    double width = min(1800 / nowMapx, 1050 / nowMapy);
	double px, py;  //��������

	//��ʼ����������
	if(nowMapx % 2 == 0){
		px = 960 - (nowMapx / 2) * width;
	}else{
		px = 960 - (nowMapx / 2) * width - width / 2;
	}
	if(nowMapy % 2 == 0){
		py = 540 - (nowMapy / 2) * width;
	}else{
		py = 540 - (nowMapy / 2) * width - width / 2;
	}

	//���û��ʻ���ͼ
	for(int i = nowMapy; i >= 1; i--){
		#pragma omp for
		for(int j = 1; j <= nowMapx; j++){
			DrawOneBox(px, py, width, nowMap[i-1][j-1].state, 0);
			px += width;
		}
		//��������
		if(nowMapx % 2 == 0){
			px = 960 - nowMapx / 2 * width;
		}else{
			px = 960 - nowMapx / 2 * width - width / 2;
		}
		py += width;
	}
}

/***************
��һ������
****************/
bool DrawOneBox(double x, double y, double width, int state, bool isChoosing)
{
	//������Ӧ����ɫ
	char *color;
	switch (state)
	{
	case 0:
		if(isInBox(x, y, width) || isChoosing) color = "MGray2";
		else color = "MGray1";
		break;
	case 1:
		if(isInBox(x, y, width) || isChoosing) color = "MGreen1";
		else color = "MGreen2";
		break;
	case 2:
		if(isInBox(x, y, width) || isChoosing) color = "MYellow1";
		else color = "MYellow2";
		break;
	case 3:
		if(isInBox(x, y, width) || isChoosing) color = "MRed1";
		else color = "MRed2";
		break;
	default:
		break;
	}

	//���Ʒ���
	StartFilledRegion(1);	
	SetPenSize(1);
	SetPenColor(color);
	MovePen(x, y);
	DrawLine(width, 0);
	DrawLine(0, width);
	DrawLine(-1 * width, 0);
	DrawLine(0, -1 * width);	
	EndFilledRegion();
	//���Ʊ߿�	
	if(isChoosing){
		SetPenSize(1);
		SetPenColor("Gray");
		MovePen(x, y);
		DrawLine(width, 0);
		DrawLine(0, width);
		DrawLine(-1 * width, 0);
		DrawLine(0, -1 * width);
	}else{
		SetPenSize(1);
		SetPenColor("MLPink");
		MovePen(x, y);
		DrawLine(width, 0);
		DrawLine(0, width);
		DrawLine(-1 * width, 0);
		DrawLine(0, -1 * width);		
	}
	if(isInBox(x, y, width) && isMClick) return 1;
	else return 0;			
}

/***************
�ж��Ƿ���������
***************/
bool isInBox(double x, double y, double width)
{
	if(Mx >= x && Mx <= x + width && My >= y && My <= y + width) return 1;
	else return 0;
}

int DrawMenu2fun1()
{
	if(DrawOneButton(500, 70, 200, 40, 20, "MDPink", "MLPink", "ȷ��", "White", 0, 0) == 0){
		if(isFlashing[0]) isFlashing[0] = 0;
		if(isFlashing[1]) isFlashing[1] = 0;
		return 0;  //������ȷ����ť
	}
	if(DrawOneButton(1220, 70, 200, 40, 20, "MDPink", "MLPink", "ȡ��", "White", 0, 0) == 0){
		return 1;  //������ȡ����ť
	}
	DrawOneButton(600, 330, 710, 40, 20, "MLPink", "MLPink", "�����ȷ�Χ: 10~30    �߶ȷ�Χ: 10~20��", "White", 0, 0);
	
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
		f = 2;  //�����������1
	}
	if(DrawOneButton(1080, 400, 230, 60, 28, "MDPink", "MLPink", mapy, "White", 1, 1) == 1){
		f = 3;  //�����������2
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
