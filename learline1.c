#include "linearList.h"

node *insertTail(node *h, node *t)
{
    // 请在此添加代码，补全函数insertTail
    /********** Begin *********/
        if (t == NULL)
            return h;
        t->next == NULL;

        if (h == NULL)
            return t;

        node * cur = h;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = t;
        return h;
    /********** End **********/
}
void delNode(node* h,int e) 
{
	//清在此添加代码，补全函数delNode
	/********** Begin *********/
        node * prev = h;
        node * cur = h->next;
        int flag = 1;
        while (cur != NULL)
        {
            if (cur->data == e)
            {
                prev->next = cur->next;
                free(cur);
                cur = prev->next;
                flag = 0;
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
        if (flag)
        {
            printf("error\n");
        }
    /********** End **********/
}