#include <stdio.h>
#include <stdlib.h>

typedef struct Bitnode
{
    char data;
    struct Bitnode *left, *right;
} Bitnode;

Bitnode *CreatBitree_level();

int depth(Bitnode *t);