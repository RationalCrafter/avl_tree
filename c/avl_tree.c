#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"
#include "array_stack/array_stack.h"
//--------------------------------------------------------------------------------
//debugging toggle
//--------------------------------------------------------------------------------
#define DEBUG 1
//--------------------------------------------------------------------------------
//helper macros
//--------------------------------------------------------------------------------
#define MAX(a,b) ((a)>=(b)?(a):(b))
//--------------------------------------------------------------------------------
//node manipulation functions
//--------------------------------------------------------------------------------
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
#if DEBUG==1
        printf("\ncall destroy_avl_node: node->value = %d",node->value);
#endif
        node->left=node->right=NULL;
        free(node);
    }
#if DEBUG==1
    else {
        printf("\ncall destroy_avl_node: node is NULL");
    }
#endif
    return NULL;
}

int update_node_height(AVLNode *node)
{
    /*Updates the height of a node, and returns the appropriate height value*/
    if (!node) {//empty node
#if DEBUG==1
        printf("\nupdate height(NULL)");
#endif
        return ABSENT_NODE_HEIGHT;
    }
    else {
        int left = get_height(node->left);
        int right = get_height(node->right);
        node->height = 1+MAX(left, right);
#if DEBUG==1
        printf("\nupdated node height = %d",node->height);
#endif
        return node->height;
    }
}

int get_balance(AVLNode *node)
{
    if (node && node->left && node->right) {
        //return node->left->height-node->right->height;
        return get_height(node->left)-get_height(node->right);
    }
    else {
        return PERFECT_BALANCE;//an absent node can't be unbalanced!
    }
}


int get_height(AVLNode *node)
{
    if (!node) {
        return ABSENT_NODE_HEIGHT;
    }
    return node->height;
}
//--------------------------------------------------------------------------------
//Tree manipulation functions
//--------------------------------------------------------------------------------
//Rotations
//--------------------------------------------------------------------------------
/* Left Rotation: let z be the root of a subtree that's heavy on the right subtree of the right child
 * z
 *  \
 *   y          ->     y
 *    \               / \
 *     x             z   x
 */

AVLNode *left_rotate(AVLNode *z) {
    if (z) {
        AVLNode *y = z->right; // y is the right child of z
        if (y) {
            AVLNode *T = y->left; // T is the left child of y
            y->left = z; // z becomes the left child of y
            z->right = T; // T becomes the right child of z
            
            // Update heights
            update_node_height(z); // Update height of z
            update_node_height(y); // Update height of y (new root)
            return y; // Return new root
        }
    }
    return NULL; // If z or y were NULL to begin with, return NULL
}
/* Right Rotation: let z be the root of a subtree that's heavy on the left subtree of the left child
  *     z
  *    /
  *   y         ->     y
  *  /                / \
  * x                x   z
  * */


AVLNode *right_rotate(AVLNode *z) 
{
    if (z) {
        AVLNode *y = z->left; // y is the left child of z
        if (y) {
            AVLNode *T = y->right; // T is the right child of y
            y->right = z; // z becomes the right child of y
            z->left = T; // T becomes the left child of z
            
            // Update heights
            update_node_height(z); // Update height of z
            update_node_height(y); // Update height of y (new root)
            return y; // Return new root
        }
    }
    return NULL; // If z or y were NULL to begin with, return NULL
}//--------------------------------------------------------------------------------
//Insertion
//--------------------------------------------------------------------------------
AVLNode *avl_insert(AVLNode **root,value_t key)
{
    //perform standard BST insertion
    if (*root == NULL) {
        *root = create_avl_node(key, NULL, NULL);
        return *root;
    }
    AVLNode *y = NULL;
    AVLNode *x = *root;
    while (x) {
        y=x;
        if(key<x->value)
            x=x->left;
        else
            x=x->right;
    }
    if (!y)//tree was empty
        *root=create_avl_node(key, NULL, NULL);
   // else if (key<y->value)
   //     y->left = create_avl_node(key, NULL, NULL); 
    else
        y->right = create_avl_node(key, NULL, NULL);
    //update the height of the ancestor node
    update_node_height(y);
    //balance tree
    int balance = get_balance(y);
    //left left case
    //heavy on the left subtree of the left child    
    if (balance>1 && key<y->left->value) {
        AVLNode * newRoot = right_rotate(y);
        update_node_height(newRoot);
        return newRoot;
    }
    //right right
    //heavy on the right subtree of the right child
    if (balance<-1 && key>y->right->value) {
        AVLNode *newRoot = left_rotate(y);
        update_node_height(newRoot);
        return newRoot;
    }
    //left right
    //heavy on the right subtree of the left child
    if (balance>1 && key>y->left->value){
        y->left=left_rotate(y->left);
        AVLNode *newRoot = right_rotate(y);
        update_node_height(newRoot);
        return newRoot;
    }
    //right left
    //heavy on the left subtree of the right child
    if (balance<-1 && key<y->right->value) {
        y->right = right_rotate(y->right);
        AVLNode *newRoot = left_rotate(y);
        update_node_height(newRoot);
        return newRoot;
    }
    return *root;
}
//--------------------------------------------------------------------------------
//Destroy AVL Tree
//--------------------------------------------------------------------------------


//AVLNode *destroy_avl_tree(AVLNode **root)
//{
//#if DEBUG==1
//    printf("\ncall destroy_avl_tree");
//#endif
//    if (!root || !*root) {
//#if DEBUG==1
//        printf("\tdestroy_avl_tree: NULL");
//#endif
//        return NULL;
//    }
//    else {
//#if DEBUG==1
//        printf("\nroot isn't null");
//        printf("\nPerforming post order traversal");
//#endif
//        //perform a postorder traversal and delete nodes
//        //assume no more than 64 nodes pushed at any time for simplicity
//        //adjustments can be made as needed later
//        ArrayStack *nodeStack=create_stack(AUX_STACK_SIZE);
//        push(nodeStack, *root);
//        while (!isEmptyStack(nodeStack)) {
//#if DEBUG==1
//            printf("\nOnce more into the breach!");
//#endif
//            AVLNode *current = pop(nodeStack);
//#if DEBUG==1
//            printf("\nPush right child into a stack");
//#endif
//            push(nodeStack, current->right);
//#if DEBUG==1
//            printf("\nPush left child into a stack");
//#endif
//            push(nodeStack, current->left);
//
//#if DEBUG==1
//            printf("\n Current node = %u sent to destroy_avl_node",current);
//#endif
//            destroy_avl_node(current);
//        }
//#if DEBUG==1
//        printf("\nGonna destroy stack");
//#endif
//        destroy_stack(&nodeStack);
//
//        *root = NULL;
//        return *root;
//    }
//}

AVLNode *destroy_avl_tree(AVLNode **root)
{
    if (!root || !*root) {
        return NULL;
    }
    else {
        destroy_avl_tree(&((*root)->left));
        destroy_avl_tree(&((*root)->right));
        return *root=destroy_avl_node(*root);
    }
}

void printInorder(AVLNode *root)
{
    if (root) {
        printInorder(root->left);
        printf("% d",root->value);
        printInorder(root->right);
    }
}
