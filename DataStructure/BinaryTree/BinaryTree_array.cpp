#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

const int MaxSize = 100;
const int MaxTreeSize = 100;

typedef int Status;

struct Position
{
    int level, order;
};

template <typename T>
class BinaryTree
{
public:
    typedef T TElemType;

    BinaryTree(int size = MaxTreeSize) : mSize(size), pData(new TElemType[size]), Nil(0) {}

    ~BinaryTree()
    {
        if (pData)
        {
            delete[] pData;
        }
    }

    Status Create()
    {
        int i = 0;
        printf("按层序输入节点的值（整形），0表示空节点，输入999结束，节点数≤%d：\n", MaxTreeSize);
        while (i < 10)
        {
            pData[i] = i + 1;
            if (i != 0 && pData[(i + 1) / 2 - 1] == Nil && pData[i] != Nil)
            {
                printf("出现无双亲的非根节点%d\n", pData[i]);
                exit(ERROR);
            }
            i++;
        }
        while (i < mSize)
        {
            pData[i] = Nil;
            i++;
        }
        return OK;
    }

    Status visit(TElemType c)
    {
        printf("%d ", c);
        return OK;
    }

    Status Init()
    {
        for (int i = 0; i < mSize; i++)
            pData[i] = Nil;
        return OK;
    }

    Status Empty()
    {
        if (pData[0] == Nil)
            return TRUE;
        else
            return FALSE;
    }

    int Depth()
    {
        int i, j = -1;
        for (i = mSize - 1; i >= 0; i--)
        {
            if (pData[i] != Nil)
                break;
        }
        i++;

        do
        {
            j++;
        } while (i >= powl(2, j));
        return j;
    }

    void Clear()
    {
        Init();
    }

    Status Root(TElemType *e)
    {
        if (Empty())
            return ERROR;
        else
        {
            *e = pData[0];
            return OK;
        }
    }

    TElemType Value(Position e)
    {
        return pData[(int)powl(2, e.level - 1) + e.order - 2];
    }

    Status Assign(Position e, TElemType value)
    {
        int i = (int)powl(2, e.level - 1) + e.order - 2;
        if (value != Nil && pData[(i + 1) / 2 - 1] == Nil)
            return ERROR;
        else if (value == Nil && (pData[i * 2 + 1] != Nil || pData[i * 2 + 2] != Nil))
            return ERROR;
        pData[i] = value;
        return OK;
    }

    TElemType Parent(TElemType e)
    {
        int i;
        if (pData[0] == Nil)
            return Nil;
        for (i = 1; i <= mSize - 1; i++)
        {
            if (pData[i] == e)
                return pData[(i + 1) / 2 - 1];
        }
        return Nil;
    }

    TElemType LeftChild(TElemType e)
    {
        int i;
        if (pData[0] == Nil)
            return Nil;
        for (i = 0; i <= mSize - 1; i++)
        {
            if (pData[i] == e)
                return pData[i * 2 + 1];
        }
        return Nil;
    }

    TElemType RightChild(TElemType e)
    {
        int i;
        if (pData[0] == Nil)
            return Nil;
        for (i = 0; i <= mSize - 1; i++)
        {
            if (pData[i] == e)
                return pData[i * 2 + 2];
        }
        return Nil;
    }

    TElemType LeftSibling(TElemType e)
    {
        int i;
        if (pData[0] == Nil)
            return Nil;
        for (i = 1; i <= mSize - 1; i++)
        {
            if (pData[i] == e && i % 2 == 0)
                return pData[i - 1];
        }
        return Nil;
    }

    TElemType RightSibling(TElemType e)
    {
        int i;
        if (pData[0] == Nil)
            return Nil;
        for (i = 1; i <= mSize - 1; i++)
        {
            if (pData[i] == e && i % 2)
                return pData[i + 1];
        }
        return Nil;
    }

    // 遍历存在数组越界的情况
    void PreTraverse(int e)
    {
#if 0
    visit(T[e]);
    if (T[2 * e + 1] != Nil)
        PreTraverse(T, 2 * e + 1);
    if (T[2 * e + 2] != Nil)
        PreTraverse(T, 2 * e + 2);
#else
        if (pData[e] == Nil)
            return;

        visit(pData[e]);
        PreTraverse(2 * e + 1);
        PreTraverse(2 * e + 2);

#endif
    }

    Status PreOrderTraverse()
    {
        if (!Empty())
            PreTraverse(0);
        printf("\n");
        return OK;
    }

    void InTraverse(int e)
    {
        if (pData[2 * e + 1] != Nil)
            InTraverse(2 * e + 1);
        visit(pData[e]);
        if (pData[2 * e + 2] != Nil)
            InTraverse(2 * e + 2);
    }

    Status InOrderTraverse()
    {
        if (!Empty())
            InTraverse(0);
        printf("\n");
        return OK;
    }

    void PostTraverse(int e)
    {
        if (pData[2 * e + 1] != Nil)
            PostTraverse(2 * e + 1);
        if (pData[2 * e + 2] != Nil)
            PostTraverse(2 * e + 2);
        visit(pData[e]);
    }

    Status PostOrderTraverse()
    {
        if (!Empty())
            PostTraverse(0);
        printf("\n");
        return OK;
    }

    void LevelOrderTraverse()
    {
        int i = MaxTreeSize - 1, j;
        while (pData[i] == Nil)
            i--;
        for (j = 0; j <= i; j++)
        {
            if (pData[j] != Nil)
                visit(pData[j]);
        }
        printf("\n");
    }

    void Print()
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
        while (pData[i] != Nil)
        {
            int num = (int)powl(2, j);
            printf("第%d层：", j);
            int count = 0;
            while (count < num)
            {
                printf("%d:%d ", count++, pData[i++]);
            }
            printf("\n");
            j++;
        }
#endif
    }

private:
    int mSize;
    TElemType *pData;
    TElemType Nil;
};

int main()
{
    BinaryTree<int> tree;
    Status i;
    Position p;
    int e;
    tree.Init();
    tree.Create();
    printf("建立二叉树后， 树空否？%d(1:是 0:否 树的深度=%d\n",
           tree.Empty(), tree.Depth());
    i = tree.Root(&e);
    if (i)
        printf("二叉树的根为：%d\n", e);
    else
        printf("树空，无根\n");
    printf("打印二叉树\n");
    tree.Print();
    printf("层序遍历二叉树：\n");
    tree.LevelOrderTraverse();
    printf("前序遍历二叉树：\n");
    tree.PreOrderTraverse();
    printf("中序遍历二叉树：\n");
    tree.InOrderTraverse();
    printf("后序遍历二叉树：\n");
    tree.PostOrderTraverse();
    printf("修改节点的层号3本层序号2。");
    p.level = 3;
    p.order = 2;
    e = tree.Value(p);
    printf("待修改节点的原值为%d请输入新值：50", e);
    e = 50;
    tree.Assign(p, e);
    printf("前序遍历二叉树：\n");
    tree.PreOrderTraverse();
    printf("节点%d的双亲为%d，左右孩子分别为", e, tree.Parent(e));
    printf("%d, %d, 左右兄弟分别为", tree.LeftChild(e), tree.RightChild(e));
    printf("%d, %d\n", tree.LeftSibling(e), tree.RightSibling(e));
    tree.Clear();
    printf("清除二叉树，树空否？%d(1:是 0:否) 树的深度=%d\n",
           tree.Empty(), tree.Depth());
    i = tree.Root(&e);
    if (i)
        printf("二叉树的根为：%d\n", e);
    else
        printf("树空，无根\n");

    return 0;
}
