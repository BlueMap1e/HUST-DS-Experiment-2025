#include "linearList.h"

int main()
{
	int n,i,e;
	node *t;
	node *head=NULL; // 头指针为NULL，表示线性表为空，结点数�?0
	// 输入结点�?
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		// 为新节点动态分配空�?
		t = (node*)malloc(sizeof(node));
		scanf("%d",&t->data);  // 输入结点数据
		t->next=NULL;  // 结点指针域值为�?
		// 调用函数插入结点
		head = insertTail(head, t);
	}
	scanf("%d",&e);
	delNode(head,e);
	// 输出链表
	printList(head);
	// 删除结点，释放空�?
	delList(head);

	return 0;
}
// 函数delList：删除链表，释放空间
// 参数：h-链表头指�?
void delList(node *h)
{
	node *p=h;  // 指针p指向头结点，第一个要删除的结�?
	while(p)  // 这个结点是存在的
	{
		h = h->next;  // 头指针h指向下一个结点（下一个结点的地址存在当前结点的指针域中，即h->next�?
		free(p);  // 删除p指向的结�?
		p = h;  // p指向当前的头结点，即下一个要删除的结�?
	}
}
// 函数printList：输出链表，每个数据之间用一个空格隔开
// 参数：h-链表头指�?
void printList(node *h)
{
	printf("List:"); 
	while(h)
	{// h为真，即h指向的结点存在，则输出该结点的数�?
		printf(" %d",h->data);  // 输出结点数据
		h=h->next;  // 将该结点的指针域赋值给h，h就指向了下一个结�?
	}
	printf("\n"); // 输出换行�?
}

