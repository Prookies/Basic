#include <string>
#include <iostream>
#include <math.h>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;

enum Status
{
    ERROR = 0,
    OK
};

const int MaxSize = 100;

template <typename T>
class ThreadBinaryTree
{
public:
    typedef T TElemType;

    enum PointerTag
    {
        Link,
        Thread
    };
    struct BiThrNode
    {
        TElemType data;
        BiThrNode *lchild, *rchild;
        PointerTag LTag;
        PointerTag RTag;
    };
    typedef BiThrNode *BiThrTree;

    TElemType Nil;

    ThreadBinaryTree() : Nil('#') {}

    Status visit(TElemType e)
    {
        cout << e << " ";
        return OK;
    }

    Status Create()
    {
        return CreateBiThrTree(&tree);
    }

    Status CreateBiThrTree(BiThrTree *p)
    {
        TElemType h;
        cin >> h;

        if (h == Nil)
        {
            *p = NULL;
        }
        else
        {
            *p = (BiThrTree)malloc(sizeof(BiThrNode));
            if (!*p)
            {
                exit(OVERFLOW);
            }
            (*p)->data = h;
            CreateBiThrTree(&(*p)->lchild);
            if ((*p)->lchild)
                (*p)->LTag = Link;
            CreateBiThrTree(&(*p)->rchild);
            if ((*p)->rchild)
                (*p)->RTag = Link;
        }

        return OK;
    }

    void InThreading(BiThrTree p)
    {
        if (p)
        {
            InThreading(p->lchild);
            if (!p->lchild)
            {
                p->LTag = Thread;
                p->lchild = pre;
            }
            if (!pre->rchild)
            {
                pre->RTag = Thread;
                pre->rchild = p;
            }
            pre = p;
            InThreading(p->rchild);
        }
    }

    Status InOrderThreading()
    {
        root = (BiThrTree)malloc(sizeof(BiThrNode));
        if (!root)
            exit(OVERFLOW);
        root->LTag = Link;
        root->RTag = Thread;
        root->rchild = root;
        if (!tree)
        {
            root->lchild = root;
        }
        else
        {
            root->lchild = tree;
            pre = root;
            InThreading(tree);
            pre->rchild = root;
            pre->RTag = Thread;
            root->rchild = pre;
        }
        return OK;
    }

    Status InOrderTraverse_Thr()
    {
        BiThrTree p;
        p = root->lchild;
        while (p != root)
        {
            while (p->LTag == Link)
                p = p->lchild;
            if (!visit(p->data))
                return ERROR;
            while (p->RTag == Thread && p->rchild != root)
            {
                p = p->rchild;
                visit(p->data);
            }
            p = p->rchild;
        }
        return OK;
    }

private:
    BiThrTree root;
    BiThrTree tree;
    BiThrTree pre;
};

int main()
{
    ThreadBinaryTree<char> tree;
    printf("请按前序输入二叉树（如：'ABDH##I##EJ###CF##G##\n");
    tree.Create();
    tree.InOrderThreading();
    printf("中序遍历（输出）二叉线索树：\n");
    tree.InOrderTraverse_Thr();
    printf("\n");

    return 0;
}
