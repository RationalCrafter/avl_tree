#include "avl_tree.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
   //testing tree
    puts("\nCreating an AVL Tree...");
    AVLNode *root=NULL;
    puts("\nGonna test inserting sequence 1,2,3,4,5,6,7,8,9,10");
    int test_array[]={1,2,3,4,5,6,7,8,9,10};
    for (int i=0; i<sizeof(test_array)/sizeof(test_array[0]); i++){
        printf("\nInserting %d",test_array[i]);
        avl_insert(&root, test_array[i]);
        printf("\nRoot height in the calling function is %d",get_height(root));
    }
    printf("\n\nRoot height after all keys were inserted is %d",get_height(root));
    printf("\nIn order traversal: \n");
    printInorder(root);
    int search_test_array[]={4,7};
    for (int i = 0; i<sizeof(search_test_array)/sizeof(search_test_array[0]); i++) {
        printf("\nTesting Search: key = %d",search_test_array[i]);
        AVLNode *found=avl_tree_search(root, search_test_array[i]);
        if (found) {
            printf("\n Key found! parent node(-1 means it's at the tree's root): %d",
                    found->parent?found->parent->value:-1);
        }
        else {
            printf("\nKey not found!");
        }
    }
    printf("\nTesting avl_tree_minimum:");
    AVLNode *minimum = avl_tree_minimum(root);
    if (minimum) {
        printf("\nMinimum node is %d",minimum->value);
    }
    else {
        printf("\nResult was NULL,the tree must be empty!");
    }
    printf("\nTesting avl_tree_maximum:");
    AVLNode *maximum = avl_tree_maximum(root);
    if (maximum) {
        printf("\nMaximum node is %d",maximum->value);
    }
    else {
        printf("\nResult was NULL,the tree must be empty!");
    }
    printf("\nTesting key deletion:");
    int delete_test_array[]={5,9};
    for (int i = 0; i<sizeof(delete_test_array)/sizeof(delete_test_array[0]); i++) {
        printf("\nInorder before deletion of %d: ",delete_test_array[i]);
        printInorder(root);
        printf("\navl_delete(%d)",delete_test_array[i]);
        avl_delete(&root, delete_test_array[i]);
        printf("\nInorder after deletion of %d: ",delete_test_array[i]);
        printInorder(root);
    }
    puts("\nDestroying AVL Tree ...");
    destroy_avl_tree(&root);
    puts("\n");
    return 0;
}
