#include"stdio.h"
#include"stdlib.h"
// 定义结点结构
typedef struct node
{
    int data;  // 数据域
    struct node * next;  //指针域,指向下一个结点
}node;

// 函数insertTail：链表尾部插入
// 参数：h-链表头指针，t-指向要插入的结点
// 返回值：插入结点后链表的首结点地址
node *insertTail(node *h, node *t);

// 函数printList：输出链表，每个数据之间用一个空格隔开
// 参数：h-链表头指针
void printList(node *h);

// 函数delList：删除链表，释放空间
// 参数：h-链表头指针
void delList(node *h);

//函数delNode:删除指定数值
//参数：h-链表表头指针，e指定节点的数值
//如果该数值的节点存在，就删除节点，否则打印“error”
void delNode(node *h,int e);