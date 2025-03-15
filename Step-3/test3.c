#include "tree.h"
int depth(Bitnode *t)
{
    // 在这里输入代码
    /*******begin*****/
    if (t == NULL)
    {
        return 0;
    }

    int left_depth = depth(t->left);
    int right_depth = depth(t->right);

    return (left_depth > right_depth ? left_depth : right_depth) + 1;
    /******end********/
}
