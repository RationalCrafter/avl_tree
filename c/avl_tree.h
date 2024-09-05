#ifndef AVL_TREE_H
#define AVL_TREE_H
//type of values stored in each tree node
typedef int value_t;

typedef struct AVLNode AVLNode;

typedef struct AVLNode{
    value_t value;
    AVLNode *parent;
    AVLNode *left;
    AVLNode *right;
    int height;
} AVLNode;

//default values
#define INITIAL_HEIGHT (0)
#define ABSENT_NODE_HEIGHT (-1)
/*node manipulation functions*/
AVLNode *create_avl_node(value_t value, AVLNode *parent, AVLNode *left_child, AVLNode *right_child);
AVLNode *destroy_avl_node(AVLNode *node);
int update_node_height(AVLNode *node);
int get_balance(AVLNode *node);
int get_height(AVLNode *node);
/*tree manipulation functions*/
//Rotations
AVLNode *left_rotate(AVLNode *z);
AVLNode *right_rotate(AVLNode *z);
//Insertion
void avl_insert(AVLNode **root,value_t key);
//Destroy Tree
AVLNode *destroy_avl_tree(AVLNode **root);
//Traversal
void printInorder(AVLNode *root);
//Search
AVLNode *avl_tree_search(AVLNode *x,value_t key);
AVLNode *avl_tree_minimum(AVLNode *x);
AVLNode *avl_tree_maximum(AVLNode *x);
//Deletion
void avl_delete(AVLNode **root,value_t key);
#endif
