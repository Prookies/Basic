#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

const int StrLen = 24;
typedef char TElemType;
typedef char String[StrLen];

enum Status
{
    ERROR = 0,
    OK,
};

struct BiTNode
{
    TElemType data;
    BiTNode *lchild, *rchild;
};

typedef BiTNode *BiTree;

class BinaryTree
{
public:
    BinaryTree() : treeIndex(1), Nil(' '), MaxSize(100) {}

    Status StrAssign(const char *chars)
    {
        int i;
        if (strlen(chars) > MaxSize)
        {
            return ERROR;
        }
        else
        {
            str[0] = strlen(chars);
            for (i = 1; i <= str[0]; i++)
            {
                str[i] = *(chars + i - 1);
            }
            return OK;
        }
    }

    Status visit(TElemType e)
    {
        printf("%c", e);
        return OK;
    }

    Status InitBiTree()
    {
        root = NULL;
        return OK;
    }

    void Destroy()
    {
        DestroyBiTree(&root);
    }

    // 试试改为一维指针是什么效果
    void DestroyBiTree(BiTree *T)
    {
        if (*T)
        {
            if ((*T)->lchild)
                DestroyBiTree(&(*T)->lchild); // 为什么用二维指针
            if ((*T)->rchild)
                DestroyBiTree(&(*T)->rchild);
            free(*T);
            *T = NULL;
        }
    }

    void Create()
    {
        CreateBiTree(&root);
    }

    void CreateBiTree(BiTree *T)
    {
        TElemType ch;

        ch = str[treeIndex++];

        if ('#' == ch)
            *T = NULL;
        else
        {
            *T = (BiTree)malloc(sizeof(BiTNode));
            if (!*T)
                exit(OVERFLOW);
            (*T)->data = ch;
            CreateBiTree(&(*T)->lchild);
            CreateBiTree(&(*T)->rchild);
        }
    }

    Status Empty()
    {
        if (root)
            return ERROR;
        else
            return OK;
    }

    int Depth()
    {
        return BiTreeDeepth(root);
    }

    int BiTreeDeepth(BiTree T)
    {
        int i = 0, j = 0;
        if (!T)
            return 0;
        if (T->lchild)
            i = BiTreeDeepth(T->lchild);

        if (T->rchild)
            j = BiTreeDeepth(T->rchild);

        return i > j ? i + 1 : j + 1;
    }

    TElemType Root()
    {
        if (Empty())
            return Nil;
        else
            return root->data;
    }

    TElemType Value(BiTree T)
    {
        return T->data;
    }

    void Assign(BiTree T, TElemType value)
    {
        T->data = value;
    }

    void PreOrder()
    {
        PreOrderTraverse(root);
    }

    void PreOrderTraverse(BiTree T)
    {
        if (NULL == T)
            return;
        printf("%c", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }

    void InOrder()
    {
        InOrderTraverse(root);
    }

    void InOrderTraverse(BiTree T)
    {
        if (NULL == T)
            return;
        InOrderTraverse(T->lchild);
        printf("%c", T->data);
        InOrderTraverse(T->rchild);
    }

    void PostOrder()
    {
        PostOrderTraverse(root);
    }

    void PostOrderTraverse(BiTree T)
    {
        if (T == NULL)
            return;
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        printf("%c", T->data);
    }

private:
    int treeIndex;
    String str;
    TElemType Nil;
    BiTree root;
    const int MaxSize;
};

int main()
{
    int i;
    TElemType e1;
    BinaryTree tree;

    tree.InitBiTree();

    tree.StrAssign("ABDH#K###E##CFI###G#J##");

    tree.Create();

    printf("构造空二叉树后，树控否？%d(1：是 0:否） 树的深度=%d\n", tree.Empty(), tree.Depth());

    e1 = tree.Root();

    printf("二叉树的根为：%c\n", e1);

    printf("\n前序遍历二叉树：");

    tree.PreOrder();

    printf("\n中序遍历二叉树：");

    tree.InOrder();

    printf("\n后序遍历二叉树：");

    tree.PostOrder();

    tree.Destroy();

    printf("\n清除二叉树后，树空否？%d(1:是 0:否) 树的深度=%d\n", tree.Empty(), tree.Depth());
    i = tree.Root();
    if (!i)
        printf("树空，无根\n");

    return 0;
}