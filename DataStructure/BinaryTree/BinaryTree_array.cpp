#include "string.h"
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
    printf("%d ", c);
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
    printf("按层序输入节点的值（整形），0表示空节点，输入999结束，节点数≤%d：\n", MAX_TREE_SIZE);
    while (i < 10)
    {
        T[i] = i + 1;
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil)
        {
            printf("出现无双亲的非根节点%d\n", T[i]);
            exit(ERROR);
        }
        i++;
    }
    while (i < MAX_TREE_SIZE)
    {
        T[i] = Nil;
        i++;
    }
    return OK;
}

#define ClearBiTree InitBiTree

Status BiTreeEmpty(SqBiTree T)
{
    if (T[0] == Nil)
        return TRUE;
    else
        return FALSE;
}

int BiTreeDepth(SqBiTree T)
{
    int i, j = -1;
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--)
    {
        if (T[i] != Nil)
            break;
    }
    i++;

    do
    {
        j++;
    } while (i >= powl(2, j));
    return j;
}

Status Root(SqBiTree T, TElemType *e)
{
    if (BiTreeEmpty(T))
        return ERROR;
    else
    {
        *e = T[0];
        return OK;
    }
}

TElemType Value(SqBiTree T, Position e)
{
    return T[(int)powl(2, e.level - 1) + e.order - 2];
}

Status Assign(SqBiTree T, Position e, TElemType value)
{
    int i = (int)powl(2, e.level - 1) + e.order - 2;
    if (value != Nil && T[(i + 1) / 2 - 1] == Nil)
        return ERROR;
    else if (value == Nil && (T[i * 2 + 1] != Nil || T[i * 2 + 2] != Nil))
        return ERROR;
    T[i] = value;
    return OK;
}

TElemType Parent(SqBiTree T, TElemType e)
{
    int i;
    if (T[0] == Nil)
        return Nil;
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e)
            return T[(i + 1) / 2 - 1];
    }
    return Nil;
}

TElemType LeftChild(SqBiTree T, TElemType e)
{
    int i;
    if (T[0] == Nil)
        return Nil;
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e)
            return T[i * 2 + 1];
    }
    return Nil;
}

TElemType RightChild(SqBiTree T, TElemType e)
{
    int i;
    if (T[0] == Nil)
        return Nil;
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e)
            return T[i * 2 + 2];
    }
    return Nil;
}

TElemType LeftSibling(SqBiTree T, TElemType e)
{
    int i;
    if (T[0] == Nil)
        return Nil;
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e && i % 2 == 0)
            return T[i - 1];
    }
    return Nil;
}

TElemType RightSibling(SqBiTree T, TElemType e)
{
    int i;
    if (T[0] == Nil)
        return Nil;
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        if (T[i] == e && i % 2)
            return T[i + 1];
    }
    return Nil;
}

// 遍历存在数组越界的情况
void PreTraverse(SqBiTree T, int e)
{
#if 0
    visit(T[e]);
    if (T[2 * e + 1] != Nil)
        PreTraverse(T, 2 * e + 1);
    if (T[2 * e + 2] != Nil)
        PreTraverse(T, 2 * e + 2);
#else
    if (T[e] == Nil)
        return;

    visit(T[e]);
    PreTraverse(T, 2 * e + 1);
    PreTraverse(T, 2 * e + 2);

#endif
}

Status PreOrderTraverse(SqBiTree T)
{
    if (!BiTreeEmpty(T))
        PreTraverse(T, 0);
    printf("\n");
    return OK;
}

void InTraverse(SqBiTree T, int e)
{
    if (T[2 * e + 1] != Nil)
        InTraverse(T, 2 * e + 1);
    visit(T[e]);
    if (T[2 * e + 2] != Nil)
        InTraverse(T, 2 * e + 2);
}

Status InOrderTraverse(SqBiTree T)
{
    if (!BiTreeEmpty(T))
        InTraverse(T, 0);
    printf("\n");
    return OK;
}

void PostTraverse(SqBiTree T, int e)
{
    if (T[2 * e + 1] != Nil)
        PostTraverse(T, 2 * e + 1);
    if (T[2 * e + 2] != Nil)
        PostTraverse(T, 2 * e + 2);
    visit(T[e]);
}

Status PostOrderTraverse(SqBiTree T)
{
    if (!BiTreeEmpty(T))
        PostTraverse(T, 0);
    printf("\n");
    return OK;
}

void LevelOrderTraverse(SqBiTree T)
{
    int i = MAX_TREE_SIZE - 1, j;
    while (T[i] == Nil)
        i--;
    for (j = 0; j <= i; j++)
    {
        if (T[j] != Nil)
            visit(T[j]);
    }
    printf("\n");
}

void Print(SqBiTree T)
{
#if 0
    int j, k;
    Position p;
    TElemType e;
    for (j = 1; j <= BiTreeDepth(T); j++)
    {
        printf("第%d层：", j);
        for (k = 1; k <= powl(2, j - 1); k++)
        {
            p.level = j;
            p.order = k;
            e = Value(T, p);
            if (e != Nil)
                printf("%d:%d ", k, e);
        }
        printf("\n");
    }
#else
    int i = 0, j = 0;
    while (T[i] != Nil)
    {
        int num = (int)powl(2, j);
        printf("第%d层：", j);
        int count = 0;
        while (count < num)
        {
            printf("%d:%d ", count++, T[i++]);
        }
        printf("\n");
        j++;
    }
#endif
}

int main()
{
    Status i;
    Position p;
    TElemType e;
    SqBiTree T;
    InitBiTree(T);
    CreateBiTree(T);
    printf("建立二叉树后， 树空否？%d(1:是 0:否 树的深度=%d\n",
           BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("二叉树的根为：%d\n", e);
    else
        printf("树空，无根\n");
    printf("打印二叉树\n");
    Print(T);
    printf("层序遍历二叉树：\n");
    LevelOrderTraverse(T);
    printf("前序遍历二叉树：\n");
    PreOrderTraverse(T);
    printf("中序遍历二叉树：\n");
    InOrderTraverse(T);
    printf("后序遍历二叉树：\n");
    PostOrderTraverse(T);
    printf("修改节点的层号3本层序号2。");
    p.level = 3;
    p.order = 2;
    e = Value(T, p);
    printf("待修改节点的原值为%d请输入新值：50", e);
    e = 50;
    Assign(T, p, e);
    printf("前序遍历二叉树：\n");
    PreOrderTraverse(T);
    printf("节点%d的双亲为%d，左右孩子分别为", e, Parent(T, e));
    printf("%d, %d, 左右兄弟分别为", LeftChild(T, e), RightChild(T, e));
    printf("%d, %d\n", LeftSibling(T, e), RightSibling(T, e));
    ClearBiTree(T);
    printf("清除二叉树，树空否？%d(1:是 0:否) 树的深度=%d\n",
           BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("二叉树的根为：%d\n", e);
    else
        printf("树空，无根\n");

    return 0;
}
