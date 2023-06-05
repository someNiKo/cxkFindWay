#include "include/find.h"
 
#define WALL  1
#define ROUTE 0

	//ÿ��������������ĸ�������չ
static int Rank = 0;  //�����Թ��ĸ��Ӷȣ���ֵԽ���Ӷ�Խ�ͣ���СֵΪ0

//��Դ��main.c

extern int nowMapx, nowMapy, startX, startY, endX, endY;

int Count = 0;	//ͳ���߷�����
Way *Head = NULL, *End = NULL;

int Check(int i, int j, int k, int **maze);
void Path_Search(int i, int j, int dep, int endx, int endy, int **maze); 
void CreateMaze(int **maze, int x, int y);
void Output(int **maze, int count, int dep);

/************************���ɵ�ͼ**************************/
/************
�����ͼ����
�������ɺõĵ�ͼ
*************/ 
void randommap(int **reMaze, int x, int y)
{
    srand((unsigned)time(NULL));
 
	int **Maze = (int**)malloc((y + 2) * sizeof(int *));
	for (int i = 0; i < (y + 2); i++) {
		Maze[i] = (int*)calloc(x + 2, sizeof(int));
	}
 
	//����Χ����Ϊ·����ԭ��Ϊ�˷�ֹ��·ʱ�ڳ��߽磬ͬʱΪ�˱����Թ��������һȦǽ�屻�ڴ�
	for (int i = 0; i < y + 2; i++){
		for(int j = 0; j < x + 2; j++){
			Maze[i][j] = WALL;
		}
	}
	for(int i = 0; i < y + 2; i++){
		Maze[i][0] = ROUTE;
		Maze[i][x + 1] = ROUTE;
	}
	for(int j = 0; j < x + 2; j++){
		Maze[0][j] = ROUTE;
		Maze[y + 1][j] = ROUTE; 
	}
	
	//�����Թ�����2��2��Ϊ���
	CreateMaze(Maze, 2, 2); 
 
	//���Թ�����ںͳ���
	Maze[2][1] = ROUTE;
 
	//�����㷨����ԣ�������һ�����ʲ��ڣ�L-3,L-2��������ʱ��ҪѰ�ҳ���
	for (int i = y + 2 - 3; i >= 0; i--) {
		if (Maze[i][x + 2 - 3] == ROUTE) {
			Maze[i][x + 2 - 2] = ROUTE;
			break;
		}
	}
 
	//��ǽ
	for (int i = 0; i < y + 2; i++) {
		for (int j = 0; j < x + 2; j++) {
			if(Maze[i][j] == WALL){
				if(rand() % (min(nowMapx, nowMapy)) == 0){
					Maze[i][j] = ROUTE;
				}
			}
		}
	}

    //���ص�ͼ
 	for(int i = 0; i < y; i++){
 		for(int j = 0; j < x; j++){
 			reMaze[i][j] = Maze[i + 1][j + 1];
		 }
	 }
	reMaze[1][0] = 2;
    for(int i = (y - 1); i > 0; i--){
        if(Maze[i][x - 1] == ROUTE){
            reMaze[i][x - 1] = 3;
            break;
        }
    }
    //free
    for (int i = 0; i < y + 2; i++) free(Maze[i]);
	free(Maze);
 
}


/*************
�����Թ�
*************/
void CreateMaze(int **maze, int x, int y) 
{
	maze[x][y] = ROUTE;
 
	//ȷ���ĸ��������
	int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	for (int i = 0; i < 4; i++) {
		int r = rand() % 4;
		int temp = direction[0][0];
		direction[0][0] = direction[r][0];
		direction[r][0] = temp;
 
		temp = direction[0][1];
		direction[0][1] = direction[r][1];
		direction[r][1] = temp;
	}
 
	//���ĸ�������
	for (int i = 0; i < 4; i++) {
		int dx = x;
		int dy = y;
 
		//�����ڵľ��룬��Rank��������С
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range>0) {
			dx += direction[i][0];
			dy += direction[i][1];
 
			//�ų�����ͷ·
			if (maze[dx][dy] == ROUTE) {
				break;
			}
 
			//�ж��Ƿ��ڴ�·��
			int count = 0;
			for (int j = dx - 1; j < dx + 2; j++) {
				for (int k = dy - 1; k < dy + 2; k++) {
					//abs(j - dx) + abs(k - dy) == 1 ȷ��ֻ�жϾŹ�����ĸ��ض�λ��
					if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
						count++;
					}
				}
			}
 
			if (count > 1) {
				break;
			}
 
			//ȷ�������ڴ�ʱ��ǰ��
			--range;
			maze[dx][dy] = ROUTE;
		}
 
		//û���ڴ�Σ�գ��Դ�Ϊ�ڵ�ݹ�
		if (range <= 0) {
			CreateMaze(maze, dx, dy);
		}
	}
}


/************************Ѱ��·��**************************/

/****************
����һ�������
*****************/
int Random(int n)
{
	srand(time(NULL));
	int random_number = rand() % (n + 1);
	return random_number;
}

/****************
�ݹ�Ѱ·����
maze[0][?]�Լ�maze[?][0]��Ҫ��1
*****************/
void Path_Search(int i, int j, int dep, int endx, int endy, int **maze)
{
	int k, newi, newj;
	int fx[4] = { -1,1,0,0 }, fy[4] = { 0,0,-1,1 };
	for (k = 0; k <= 3; k++) {				//������ǰ������ĸ���չ����
		if (Check(i, j, k, maze) == 1){
			newi = i + fy[k];
			newj = j + fx[k];
			maze[newi][newj] = dep;			//������λ�ú�,���õ�ǰֵΪ�������
			if (newi == endy && newj == endx){	//�ߵ�(endy,endx)��������������������·��������
				Count++;
				Output(maze, Count, dep);
			}
			else							//���������һ��ݹ�
				Path_Search(newi, newj, dep + 1, endx, endy, maze);
			maze[newi][newj] = 0;			//�߲�ͨ������
		}
	}
}

/******************
��鵱ǰ�����Ƿ����
******************/
int Check(int i, int j, int k, int **maze)
{
	int fx[4] = {-1, 1, 0, 0}, fy[4] = {0, 0, -1, 1};
	int flag = 1;
	i += fy[k];
	j += fx[k];
	if (i > nowMapy || i < 1 || j > nowMapx || j < 1){
		flag = 0;
	}	//�Ƿ����Թ���&�ܾ�Խ�� 		
	if (maze[i][j] != 0 && maze[i][j] != 3){
		flag = 0;
	}					//�Ƿ����		
	return flag;
}

/********************
���Ѱ·���
*********************/
void Findfun(int **maze, int mod, int KUNX, int KUNY)
{
	Count = 0;
	Head = NULL;
	End = NULL;  //��ʼ��
	
	//����ԭʼ����
	int **copyMaze = (int **)malloc(sizeof(int *) * (nowMapy + 2));
	for(int i = 0; i <= nowMapy + 1; i++){
		copyMaze[i] = (int *)malloc(sizeof(int) * (nowMapx + 2));
	}
	for(int i = 0; i <= nowMapy + 1; i++){
		for(int j = 0; j <= nowMapx + 1; j++){
			copyMaze[i][j] = maze[i][j];
		}
	}	

	//Ѱ·
	Path_Search(KUNY, KUNX, 4, endX, endY, maze);
	
	Way *p = Head;
	Way m;
	Way *min = &m;
	min->length = 1000;  //����Сֵ���
	int ways = Random(Count);  //���һ��·
	while(p != NULL){
		if(p->length <= min->length){
			min = p;
		}
		p = p->next;
	}
	p = Head;
	switch (mod)
	{
	case 1:  //��ʾ��һ��
		for(int i = 0; i <= nowMapy + 1; i++){
			for(int j = 0; j <= nowMapx + 1; j++){
				maze[i][j] = copyMaze[i][j];
			}
		}
		if(min->map[KUNY + 1][KUNX] == 4){
			maze[KUNY + 1][KUNX] = 4;
		}else if(min->map[KUNY - 1][KUNX] == 4){
			maze[KUNY - 1][KUNX] = 4;
		}else if(min->map[KUNY][KUNX + 1] == 4){
			maze[KUNY][KUNX + 1] = 4;
		}else if(min->map[KUNY][KUNX - 1] == 4){
			maze[KUNY][KUNX - 1] = 4;
		}else{
			maze[KUNY][KUNX] = 4;
		}
		break;
	case 2:  //���·��
		for(int i = 0; i <= nowMapy + 1; i++){
			for(int j = 0; j <= nowMapx + 1; j++){
				maze[i][j] = min->map[i][j];
			}
		}
		break;
	case 3:  //���һ��·��
		for(int i = 0; i < ways - 1; i++){
			p = p->next;
		}
		for(int i = 0; i <= nowMapy + 1; i++){
			for(int j = 0; j <= nowMapx + 1; j++){
				maze[i][j] = p->map[i][j];
			}
		}
		break;
	default:
		break;
	}

	//free
	p = Head;
	Way *q;
	while(p != NULL){
		q = p;
		p = p->next;
		free(q);
	}
    for (int i = 0; i <= nowMapy + 1; i++) free(copyMaze[i]);
	free(copyMaze);	
}

/***************
Ѱ·�ɹ������һ�����鵽����
****************/
void Output(int **maze, int count, int dep)
{
	if(Head == NULL){
		Way *p = (Way *)malloc(sizeof(Way));
		Head = p;
		End = p;
		p->count = count;
		p->next = NULL;
		p->length = dep;
		for(int i = 0; i <= nowMapy + 1; i++){
			for(int j = 0; j <= nowMapx + 1; j++){
				p->map[i][j] = maze[i][j];
			}
		}
	}else{
		Way *p = (Way *)malloc(sizeof(Way));
		p->count = count;
		p->next = NULL;
		p->length = dep;
		for(int i = 0; i <= nowMapy + 1; i++){
			for(int j = 0; j <= nowMapx + 1; j++){
				p->map[i][j] = maze[i][j];
			}
		}
		End->next = p;
		End = p;			
	}
}