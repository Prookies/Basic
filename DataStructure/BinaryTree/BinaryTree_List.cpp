#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100
#define MAX_TREE_SIZE 100

typedef int Status;
typedef int TElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE];

struct Position
{
    int level, order;
};

TElemType Nil = 0;

Status visit(TElemType c)
{
    printf("%d", c);
    return OK;
}

Status InitBiTree(SqBiTree T)
{
    int i;
    for (i = 0; i < MAX_TREE_SIZE; i++)
        T[i] = Nil;
    return OK;
}

Status CreateBiTree(SqBiTree T)
{
    int i = 0;
    printf("")
}
