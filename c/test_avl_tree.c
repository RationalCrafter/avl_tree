#include "avl_tree.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    AVLNode *root=NULL;
    printf("\nAVL tree test:");
    puts("\nCreating a node ...");
    root = create_avl_node(20, NULL, NULL);
    if (root) {
        printf("\nnode successfully allocated"
               " \n\tvalue = %d\theight = %d",
                root->value,root->height);
    }
    else {
        puts("\n Something went wrong in create_avl_node!");
    }
    puts("\n Updating Height: ");
    printf("\n node height: %d",update_node_height(root));
    puts("\nDestroying node ...");
    root=destroy_avl_node(root);
    if (!root) {
        puts("\n Node successfully destroyed!");
    }
    else {
        puts("\n Something went wrong with destroy_avl_node!"
                "\n Memory may not have been freed!");
    }
    puts("\n");
    return 0;
}
