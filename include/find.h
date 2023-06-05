#ifndef find_h
#define find_h

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void randommap(int **reMaze, int x, int y);
void Findfun(int **maze, int mod, int KUNX, int KUNY);


typedef struct way{
    int map[22][32];
    struct way *next;
    int count;
    int length;
} Way;





#endif