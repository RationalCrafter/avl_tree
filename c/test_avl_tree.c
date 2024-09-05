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
    
    printf("\nRoot height after all keys were inserted is %d",get_height(root));
    printf("\nIn order traversal: \n");
    printInorder(root);
    // Print the tree
    puts("\nDestroying AVL Tree ...");
    destroy_avl_tree(&root);
    puts("\n");
    return 0;
}
