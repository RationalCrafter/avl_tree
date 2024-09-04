#include "avl_tree.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    //testing node
    AVLNode *root=NULL;
    //printf("\nAVL tree test:");
    //puts("\nCreating a node ...");
    //root = create_avl_node(20, NULL, NULL);
    //if (root) {
    //    printf("\nnode successfully allocated"
    //           " \n\tvalue = %d\theight = %d",
    //            root->value,root->height);
    //}
    //else {
    //    puts("\n Something went wrong in create_avl_node!");
    //}
    //puts("\n Updating Height: ");
    //printf("\n node height: %d",update_node_height(root));
    //puts("\nDestroying node ...");
    //puts(" finished");
    //root=destroy_avl_node(root);
    //if (!root) {
    //    puts("\n Node successfully destroyed!");
    //}
    //else {
    //    puts("\n Something went wrong with destroy_avl_node!"
    //            "\n Memory may not have been freed!");
    //}
    ////testing tree
    puts("\nCreating an AVL Tree...");
    puts("\nGonna test inserting sequence 1,2,3,4,5,6,7,8,9,10");
    int test_array[]={1,2,3,4,5,6,7,8,9,10};
    for (int i=0; i<sizeof(test_array)/sizeof(test_array[0]); i++){
        printf("\nInserting %d",test_array[i]);
        root=avl_insert(&root, test_array[i]);
    }
    
    printf("\nRoot height = %d",get_height(root));
    printf("\nIn order traversal: \n");
    printInorder(root);
    puts("\nDestroying AVL Tree ...");
    destroy_avl_tree(&root);
    puts(" finished");
    puts("\n");
    return 0;
}
