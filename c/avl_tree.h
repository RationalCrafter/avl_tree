#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct AVLNode AVLNode;

typedef struct AVLNode{
    int value;
    AVLNode *left;
    AVLNode *right;
    int height;
} AVLNode;


#endif
