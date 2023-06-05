#include "include/find.h"
 
#define WALL  1
#define ROUTE 0

	//每个点的上下左右四个方向扩展
static int Rank = 0;  //控制迷宫的复杂度，数值越大复杂度越低，最小值为0

//来源于main.c

extern int nowMapx, nowMapy, startX, startY, endX, endY;

int Count = 0;	//统计走法种数
Way *Head = NULL, *End = NULL;

int Check(int i, int j, int k, int **maze);
void Path_Search(int i, int j, int dep, int endx, int endy, int **maze); 
void CreateMaze(int **maze, int x, int y);
void Output(int **maze, int count, int dep);

/************************生成地图**************************/
/************
传入地图长宽
传回生成好的地图
*************/ 
void randommap(int **reMaze, int x, int y)
{
    srand((unsigned)time(NULL));
 
	int **Maze = (int**)malloc((y + 2) * sizeof(int *));
	for (int i = 0; i < (y + 2); i++) {
		Maze[i] = (int*)calloc(x + 2, sizeof(int));
	}
 
	//最外围层设为路径的原因，为了防止挖路时挖出边界，同时为了保护迷宫主体外的一圈墙体被挖穿
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
	
	//创造迷宫，（2，2）为起点
	CreateMaze(Maze, 2, 2); 
 
	//画迷宫的入口和出口
	Maze[2][1] = ROUTE;
 
	//由于算法随机性，出口有一定概率不在（L-3,L-2）处，此时需要寻找出口
	for (int i = y + 2 - 3; i >= 0; i--) {
		if (Maze[i][x + 2 - 3] == ROUTE) {
			Maze[i][x + 2 - 2] = ROUTE;
			break;
		}
	}
 
	//抠墙
	for (int i = 0; i < y + 2; i++) {
		for (int j = 0; j < x + 2; j++) {
			if(Maze[i][j] == WALL){
				if(rand() % (min(nowMapx, nowMapy)) == 0){
					Maze[i][j] = ROUTE;
				}
			}
		}
	}

    //传回地图
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
生成迷宫
*************/
void CreateMaze(int **maze, int x, int y) 
{
	maze[x][y] = ROUTE;
 
	//确保四个方向随机
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
 
	//向四个方向开挖
	for (int i = 0; i < 4; i++) {
		int dx = x;
		int dy = y;
 
		//控制挖的距离，由Rank来调整大小
		int range = 1 + (Rank == 0 ? 0 : rand() % Rank);
		while (range>0) {
			dx += direction[i][0];
			dy += direction[i][1];
 
			//排除掉回头路
			if (maze[dx][dy] == ROUTE) {
				break;
			}
 
			//判断是否挖穿路径
			int count = 0;
			for (int j = dx - 1; j < dx + 2; j++) {
				for (int k = dy - 1; k < dy + 2; k++) {
					//abs(j - dx) + abs(k - dy) == 1 确保只判断九宫格的四个特定位置
					if (abs(j - dx) + abs(k - dy) == 1 && maze[j][k] == ROUTE) {
						count++;
					}
				}
			}
 
			if (count > 1) {
				break;
			}
 
			//确保不会挖穿时，前进
			--range;
			maze[dx][dy] = ROUTE;
		}
 
		//没有挖穿危险，以此为节点递归
		if (range <= 0) {
			CreateMaze(maze, dx, dy);
		}
	}
}


/************************寻找路线**************************/

/****************
返回一个随机数
*****************/
int Random(int n)
{
	srand(time(NULL));
	int random_number = rand() % (n + 1);
	return random_number;
}

/****************
递归寻路函数
maze[0][?]以及maze[?][0]需要是1
*****************/
void Path_Search(int i, int j, int dep, int endx, int endy, int **maze)
{
	int k, newi, newj;
	int fx[4] = { -1,1,0,0 }, fy[4] = { 0,0,-1,1 };
	for (k = 0; k <= 3; k++) {				//搜索当前坐标的四个扩展方向
		if (Check(i, j, k, maze) == 1){
			newi = i + fy[k];
			newj = j + fx[k];
			maze[newi][newj] = dep;			//来到新位置后,设置当前值为搜索深度
			if (newi == endy && newj == endx){	//走到(endy,endx)即出口则结束搜索，输出路径并返回
				Count++;
				Output(maze, Count, dep);
			}
			else							//否则进行下一层递归
				Path_Search(newi, newj, dep + 1, endx, endy, maze);
			maze[newi][newj] = 0;			//走不通，回溯
		}
	}
}

/******************
检查当前坐标是否可行
******************/
int Check(int i, int j, int k, int **maze)
{
	int fx[4] = {-1, 1, 0, 0}, fy[4] = {0, 0, -1, 1};
	int flag = 1;
	i += fy[k];
	j += fx[k];
	if (i > nowMapy || i < 1 || j > nowMapx || j < 1){
		flag = 0;
	}	//是否在迷宫内&拒绝越界 		
	if (maze[i][j] != 0 && maze[i][j] != 3){
		flag = 0;
	}					//是否可行		
	return flag;
}

/********************
输出寻路结果
*********************/
void Findfun(int **maze, int mod, int KUNX, int KUNY)
{
	Count = 0;
	Head = NULL;
	End = NULL;  //初始化
	
	//保护原始数据
	int **copyMaze = (int **)malloc(sizeof(int *) * (nowMapy + 2));
	for(int i = 0; i <= nowMapy + 1; i++){
		copyMaze[i] = (int *)malloc(sizeof(int) * (nowMapx + 2));
	}
	for(int i = 0; i <= nowMapy + 1; i++){
		for(int j = 0; j <= nowMapx + 1; j++){
			copyMaze[i][j] = maze[i][j];
		}
	}	

	//寻路
	Path_Search(KUNY, KUNX, 4, endX, endY, maze);
	
	Way *p = Head;
	Way m;
	Way *min = &m;
	min->length = 1000;  //让最小值最大
	int ways = Random(Count);  //随机一条路
	while(p != NULL){
		if(p->length <= min->length){
			min = p;
		}
		p = p->next;
	}
	p = Head;
	switch (mod)
	{
	case 1:  //提示下一步
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
	case 2:  //最短路径
		for(int i = 0; i <= nowMapy + 1; i++){
			for(int j = 0; j <= nowMapx + 1; j++){
				maze[i][j] = min->map[i][j];
			}
		}
		break;
	case 3:  //随机一条路径
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
寻路成功后输出一个数组到链表
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