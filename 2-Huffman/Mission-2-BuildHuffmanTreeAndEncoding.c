// Your code begin.
// 示例仅供参考，你也可以自行修改设计
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRLEN 8192 // 自定义的一个硬编码最大字符串长度，可调整

typedef struct ListNode // 结点结构，哈夫曼树与频度链表共用
{
    char c;                  // 结点的字符
    int frequency;           // 字符的频度
    char *code;              // 字符的编码(对哈夫曼树结点有效)
    struct ListNode *parent; // 结点的双亲结点(对哈夫曼树结点有效)
    struct ListNode *left;   // 结点的左子树(对哈夫曼树结点有效)
    struct ListNode *right;  // 结点的右子树(对哈夫曼树结点有效)
    struct ListNode *next;   // 结点的后继结点(对频度链表结点有效)
} ListNode, HuffmanTree;

ListNode *findNode(ListNode *head, char c) // 查找频度链表中是否存在需要统计的字符
{
    while (head != NULL)
    {
        if (head->c == c)
        {
            return head;
        }
        else
        {
            head = head->next;
        }
    }
    return NULL;
}

void insertOrIncrement(ListNode **head, char c) // 查找频度链表，如果存在，则频度+1，如果不存在，则新建节点（头插法）
{
    ListNode *node = findNode(*head, c);
    if (node != NULL)
    {
        node->frequency++;
    }
    else
    {
        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        newNode->c = c;
        newNode->frequency = 1;
        newNode->next = NULL;

        if (*head == NULL)
        {
            *head = newNode;
        }
        else
        {
            ListNode *tail = *head;
            while (tail->next)
            {
                tail = tail->next;
            }
            tail->next = newNode;
        }
    }
}

void countFrequencies(const char *text, ListNode **head) // 进行词频统计，遍历输入的字符串
{
    while (*text)
    {
        insertOrIncrement(head, *text);
        text++;
    }
}

void sortList(ListNode **head) // 链表排序，按频率降序
{
    if (!head || !*head)
        return;

    int swapped;
    ListNode *ptr1;
    ListNode *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr)
        {
            if (ptr1->frequency < ptr1->next->frequency)
            {
                int tempFreq = ptr1->frequency;
                char tempChar = ptr1->c;

                ptr1->frequency = ptr1->next->frequency;
                ptr1->c = ptr1->next->c;

                ptr1->next->frequency = tempFreq;
                ptr1->next->c = tempChar;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void printList(ListNode *head) // 打印链表
{
    while (head)
    {
        if (head->c != '\n')
        {
            printf("'%c' %d\n", head->c, head->frequency);
        }
        else
        {
            printf("'\\n' %d\n", head->frequency);
        }

        head = head->next;
    }
}

void freeList(ListNode *head) // 释放链表
{
    while (head)
    {
        ListNode *temp = head;
        head = head->next;
        free(temp);
    }
}

void readInput(char *cString) // 读取输入，包含空格、换行等
{
    int index = 0;
    char c = ' ';

    while ((c = getchar()) != EOF)
    {
        if (index < MAX_STRLEN - 1)
        {
            cString[index++] = c;
        }
    }

    cString[index] = '\0';
}

int main()
{
    char inputText[MAX_STRLEN];
    ListNode *head = NULL;

    readInput(inputText);

    countFrequencies(inputText, &head);
    sortList(&head);
    printList(head);

    freeList(head);
    return 0;
}
// Your code end.