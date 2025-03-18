#include "tree.h"
Bitnode *buildTree()
{
    char data;
    scanf("%c", &data);
    if (data == '$')
        return NULL;
    if (data == '#')
        return NULL;
    else
    {
        Bitnode *t = (Bitnode *)malloc(sizeof(Bitnode));
        t->data = data;
        t->left = buildTree();
        t->right = buildTree();
        return t;
    }
}
int main()
{
    Bitnode *t = buildTree();
    int ans = depth(t);
    printf("%d", ans);
}