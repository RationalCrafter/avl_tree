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
AVLNode *create_avl_node(value_t value,AVLNode *parent,AVLNode *left_child,AVLNode *right_child)
{
    AVLNode *new_node = (AVLNode *)malloc(sizeof(AVLNode));
    if (!new_node) {//failed to allocate memory for new_node
        return NULL;
    }
    new_node->value = value;
    new_node->height=INITIAL_HEIGHT;
    new_node->parent=parent;
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
        node->parent=node->left=node->right=NULL;
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
#if DEBUG==1
        int prevHeight = node->height;
#endif
        int left, right;
        left=right=INITIAL_HEIGHT;
        if (node->left)
            left = get_height(node->left);
        if (node->right)
            right = get_height(node->right);
        node->height = 1+MAX(left, right);
#if DEBUG==1
        printf("\nupdated node height = %d",node->height);
        printf("\nHeight changed from %d to %d inside update_node_height!",prevHeight,node->height);
#endif
        return node->height;
    }
}

int get_balance(AVLNode *node)
{
    if (node) {
        int left,right;
        left=right=INITIAL_HEIGHT;
        if (node->left)
            left=get_height(node->left);
        if (node->right)
            right=get_height(node->right);
        return left-right;
    }
    else {
        return 0;//an absent node can't be unbalanced!
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
            AVLNode *oldParent = z->parent; // the old parent of the current root of this subtree
            AVLNode *T = y->left; // T is the left child of y

            y->left = z; // z becomes the left child of y
            z->right = T; // T becomes the right child of z
            
            // Update parents
            z->parent = y;
            if (T) T->parent = z;
            y->parent = oldParent;
            
            if (oldParent) {
                if (oldParent->left == z) oldParent->left = y;
                else oldParent->right = y;
            }
            
            // Update heights
            update_node_height(z); // Update height of z
            update_node_height(y); // Update height of y (new root)
            return y; // Return new root
        }
    }
    return z; // If z or y were NULL to begin with, return z
}
/* Right Rotation: let z be the root of a subtree that's heavy on the left subtree of the left child
  *     z
  *    /
  *   y         ->     y
  *  /                / \
  * x                x   z
  * */


AVLNode *right_rotate(AVLNode *z) {
    if (z) {
        AVLNode *y = z->left; // y is the left child of z
        if (y) {
            AVLNode *oldParent = z->parent; // the old parent of the current root of this subtree
            AVLNode *T = y->right; // T is the right child of y

            y->right = z; // z becomes the right child of y
            z->left = T; // T becomes the left child of z
            
            // Update parents
            z->parent = y;
            if (T) T->parent = z;
            y->parent = oldParent;
            
            if (oldParent) {
                if (oldParent->left == z) oldParent->left = y;
                else oldParent->right = y;
            }
            
            // Update heights
            update_node_height(z); // Update height of z
            update_node_height(y); // Update height of y (new root)
            return y; // Return new root
        }
    }
    return z; // If z or y were NULL to begin with, return z
}
//--------------------------------------------------------------------------------
//Insertion
//--------------------------------------------------------------------------------
AVLNode *avl_insert(AVLNode **root,value_t key)
{
    //perform standard BST insertion
    if (!root || !*root) {
        *root = create_avl_node(key,NULL, NULL, NULL);
        return *root;
    }
    //--------------------------------------------------------------------------------
    //The tree wasn't empty, find a place to put the new node
    //--------------------------------------------------------------------------------
    AVLNode *y = NULL;
    AVLNode *x = *root;
    while (x) {
        y=x;
        if(key<x->value){
            x=x->left;
        }else{
            x=x->right;
        }
    }
    //--------------------------------------------------------------------------------
    //insert the new node and remember the spot
    AVLNode *insertedNode = NULL;
    //if key is smaller than the y (root of this subtree) make it a left child
    if (key < y->value) y->left = insertedNode = create_avl_node(key, y, NULL, NULL);
    else if (key==y->value) {
        //do nothing, can't have equal keys!
        return *root;
    }
    //if key is greater than or equal to the root of this subtree make it a right child
    else y->right = insertedNode = create_avl_node(key, y, NULL, NULL);

    // Update heights and rebalance
    while (insertedNode) {
        update_node_height(insertedNode);

        int balance = get_balance(insertedNode);

        // Left Heavy
        if (balance > 1) {
            if (get_balance(insertedNode->left) < 0) {
                insertedNode->left = left_rotate(insertedNode->left);
            }
            insertedNode = right_rotate(insertedNode);
        }
        // Right Heavy
        else if (balance < -1) {
            if (get_balance(insertedNode->right) > 0) {
                insertedNode->right = right_rotate(insertedNode->right);
            }
            insertedNode = left_rotate(insertedNode);
        }

        insertedNode = insertedNode->parent;
    }

    // Ensure root is updated
    while (*root && (*root)->parent) {
        *root = (*root)->parent;
    }

    return *root;
}
//--------------------------------------------------------------------------------
//Destroy AVL Tree
//--------------------------------------------------------------------------------


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
