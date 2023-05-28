#include "include/find.h"
 
//ǽ��·���ı�ʶ
#define WALL  1
#define ROUTE 0
 
//�����Թ��ĸ��Ӷȣ���ֵԽ���Ӷ�Խ�ͣ���СֵΪ0
static int Rank = 0;
 
void CreateMaze(int **maze, int x, int y);

/************
�������ɺõĵ�ͼ
*************/ 
void randommap(int **reMaze, int x, int y)  //�����ͼ����
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
				if(rand() % 6 == 0){
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
void CreateMaze(int **maze, int x, int y) {
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