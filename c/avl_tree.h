#ifndef AVL_TREE_H
#define AVL_TREE_H
//type of values stored in each tree node
typedef int value_t;

typedef struct AVLNode AVLNode;

typedef struct AVLNode{
    value_t value;
    AVLNode *left;
    AVLNode *right;
    int height;
} AVLNode;

//default values
#define INITIAL_HEIGHT 0
#define ABSENT_NODE_HEIGHT 0
#define PERFECT_BALANCE 0
/*node manipulation functions*/
AVLNode *create_avl_node(value_t value, AVLNode *left_child, AVLNode *right_child);
AVLNode *destroy_avl_node(AVLNode *node);
int update_node_height(AVLNode *node);
int get_balance(AVLNode *node);
int get_height(AVLNode *node);
/*tree manipulation functions*/
#endif
