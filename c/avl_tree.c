#include <stddef.h>
#include <stdlib.h>

#include "avl_tree.h"
//helper macros
#define MAX(a,b) ((a)>=(b)?(a):(b))
//node manipulation functions
AVLNode *create_avl_node(value_t value,AVLNode *left_child,AVLNode *right_child)
{
    AVLNode *new_node = (AVLNode *)malloc(sizeof(AVLNode));
    if (!new_node) {//failed to allocate memory for new_node
        return NULL;
    }
    new_node->value = value;
    new_node->height=INITIAL_HEIGHT;
    new_node->left=left_child;
    new_node->right=right_child;
    return new_node;
}

AVLNode *destroy_avl_node(AVLNode *node)
{
    /*destroy_avl_node is intended to be used in a postorder traversal to free
     * the whole tree, and it assumes the children will be freed elsewhere.*/
    if (node) {
        node->left=node->right=NULL;
        free(node);
    }
    return NULL;
}

int update_node_height(AVLNode *node)
{
    /*Updates the height of a node, and returns the appropriate height value*/
    if (!node) {//empty node
        return ABSENT_NODE_HEIGHT;
    }
    else {
        if (node->left && node->right) {
            //both children exist, take the maximum of their heights
            return node->height=1+MAX(node->left->height, node->right->height);
        }
        else if (node->left && !node->right) {
            //the height must be determined only from the left child
            //since there is no right child
            return node->height=1+node->left->height;
        }
        else if (!node->left && node->right) {
            //the height is dictated by the right child
            //since there is no left child
            return node->height=1+node->right->height;
        }
        else {//this is a leaf node
            return node->height=INITIAL_HEIGHT;
        }
    }
}
