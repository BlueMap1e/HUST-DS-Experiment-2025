// Your code begin.
// 示例仅供参考，你也可以自行修改设计
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRLEN 8192  // 自定义的一个硬编码最大字符串长度，可调整
#define MAX_CODELEN 256  // 假定编码长度不会超过256位
#define CHARSET_SIZE 256 // 假定使用ASCII

char *huffmanTable[CHARSET_SIZE] = {NULL};

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

void findTwoMinNodes(ListNode *head, ListNode **firstMin, ListNode **secondMin) // 寻找频度链表中目前存在的，没有父节点的，频度最小的两个节点
{
    *firstMin = *secondMin = NULL;

    for (ListNode *cur = head; cur != NULL; cur = cur->next)
    {
        if (cur->parent == NULL)
        {
            if (*firstMin == NULL || cur->frequency < (*firstMin)->frequency)
            {
                *secondMin = *firstMin;
                *firstMin = cur;
            }
            else if (*secondMin == NULL || cur->frequency < (*secondMin)->frequency)
            {
                *secondMin = cur;
            }
        }
    }
}

ListNode *createParentNode(ListNode *firstMin, ListNode *secondMin) // 根据找到的频度最小的两个节点，构建一个父节点，返回它
{
    ListNode *parent = (ListNode *)malloc(sizeof(ListNode));
    parent->c = '\0';
    parent->frequency = firstMin->frequency + secondMin->frequency;
    parent->left = firstMin;
    parent->right = secondMin;
    parent->parent = NULL;
    parent->next = NULL;

    firstMin->parent = parent;
    secondMin->parent = parent;

    return parent;
}

void insertNode(ListNode **head, ListNode *newNode) // 向频度链表中插入新生成的父节点，保持降序顺序
{
    if (*head == NULL || (*head)->frequency < newNode->frequency)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        ListNode *cur = *head;
        while (cur->next != NULL && cur->next->frequency > newNode->frequency)
        {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

ListNode *buildHuffmanTree(ListNode **head) // 构建哈夫曼树，每次选取频度最小的两个节点，合成父节点，插入频度链表，直到只剩下一个节点
{
    while ((*head)->next != NULL)
    {
        ListNode *firstMin, *secondMin;
        findTwoMinNodes(*head, &firstMin, &secondMin);

        if (secondMin == NULL)
        {
            break;
        }

        ListNode *parent = createParentNode(firstMin, secondMin);

        insertNode(head, parent);
    }
    return *head;
}

void generateHuffmanCodes(ListNode *node, char *code, int depth)    // 遍历哈夫曼树，生成哈夫曼编码
{
    if (node == NULL)
    {
        return;
    }
    if (node->left == NULL && node->right == NULL)
    {
        node->code = (char *)malloc(depth + 1);
        strncpy(node->code, code, depth);
        node->code[depth] = '\0';
        return;
    }

    code[depth] = '0';
    generateHuffmanCodes(node->left, code, depth + 1);

    code[depth] = '1';
    generateHuffmanCodes(node->right, code, depth + 1);
}

void printHuffmanTable(ListNode *head)  // 打印哈夫曼编码表（临时打印，用的遍历）（其实第三关应该先Build再Print的，懒得重构了（）
{
    while (head != NULL)
    {
        if (head->code != NULL && head->c != '\0')
        {
            if (head->c != '\n')
                printf("'%c' %d %s\n", head->c, head->frequency, head->code);
            else
                printf("'\\n' %d %s\n", head->frequency, head->code);
        }
        head = head->next;
    }
}

int calculateWPL(ListNode *node, int depth) // 计算WPL
{
    if (node == NULL)
        return 0;

    if (node->left == NULL && node->right == NULL)
    {
        return node->frequency * depth;
    }

    return calculateWPL(node->left, depth + 1) + calculateWPL(node->right, depth + 1);
}

void freeHuffmanTree(ListNode *node)    // 释放哈夫曼树的内存空间
{
    if (node == NULL)
        return;
    freeHuffmanTree(node->left);
    freeHuffmanTree(node->right);
    if (node->code)
        free(node->code);
    free(node);
}

void buildHuffmanTable(ListNode *head, char *huffmanTable[256]) // 生成哈夫曼编码表，避免每次编码都要搜索哈夫曼树
{
    while (head)
    {
        if (head->code != NULL && head->c != '\0')
        {
            huffmanTable[(unsigned char)head->c] = head->code;
        }
        head = head->next;
    }
}

char *encodeText(const char *text, char *huffmanTable[256], int *bitCount)  // 编码过程，直接逐字符替换
{
    static char encodedText[MAX_STRLEN * MAX_CODELEN];
    encodedText[0] = '\0';
    *bitCount = 0;

    while (*text)
    {
        char *code = huffmanTable[(unsigned char)*text];
        if (code)
        {
            strcat(encodedText, code);
            *bitCount += strlen(code);
        }
        text++;
    }

    return encodedText;
}

void decodeText(const char *encodedText, ListNode *root)    // 解码过程，在哈夫曼树中搜索，找到叶子结点即可输出
{
    ListNode *current = root;

    while (*encodedText)
    {
        if (*encodedText == '0')
        {
            current = current->left;
        }
        else if (*encodedText == '1')
        {
            current = current->right;
        }

        if (current->left == NULL && current->right == NULL)
        {
            putchar(current->c);
            current = root;
        }

        encodedText++;
    }
    printf("\n");
}

int main()
{
    char inputText[MAX_STRLEN];
    ListNode *head = NULL;

    readInput(inputText);

    countFrequencies(inputText, &head);
    sortList(&head);
    // printList(head);

    ListNode *root = buildHuffmanTree(&head);

    char code[MAX_CODELEN];
    generateHuffmanCodes(root, code, 0);

    // printHuffmanTable(head);

    // int WPL = calculateWPL(root, 0);
    // printf("%d", WPL);

    buildHuffmanTable(head, huffmanTable);

    int bitCount = 0;
    char *encodedText = encodeText(inputText, huffmanTable, &bitCount);
    printf("%s\n", encodedText);


    decodeText(encodedText, root);
    printf("%d", bitCount);

    freeHuffmanTree(root);
    return 0;
}
// Your code end.