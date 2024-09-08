#include "avl_tree.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#define NREPS 100
#define TEST_VALUE (1)
#define TEST_MAX (500)
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
    printf("\nDestroying AVL Tree ...");
    destroy_avl_tree(&root);
    printf("\nPreparing to measure time taken by tree operations...");
    //single node destruction
    printf("\nSingle node structure creation: ");
    AVLNode *emptyTrees[NREPS];
    clock_t start=clock(),diff;
    for (int i=0; i<NREPS; i++) {
        emptyTrees[i]=create_avl_node(TEST_VALUE, NULL, NULL, NULL);
    }
    diff=clock()-start;
    float avg_time = ((float)diff*1000/CLOCKS_PER_SEC)/NREPS;
    printf(" %f ms",avg_time);
    //single node destruction
    printf("\nSingle node structure destruction: ");
    start=clock();
    for (int i=0; i<NREPS; i++) {
        emptyTrees[i]=destroy_avl_node(emptyTrees[i]);
    }
    diff=clock()-start;
    avg_time = ((float)diff*1000/CLOCKS_PER_SEC)/NREPS;
    printf(" %f ms",avg_time);
    //creation and destruction
    for (int k=0; k<TEST_MAX; k<10?(k++):(k+=25)) {
        printf("\nAverage time for the creation and destruction of a tree with %d sequencial keys",k);
        start=clock();
        for (int i=0; i<NREPS; i++) {
            for (int j=0; j<k; j++){
                avl_insert(&emptyTrees[i], j);
            }
            destroy_avl_tree(&emptyTrees[i]);
        }
        diff=clock()-start;
        avg_time = ((float)diff*1000/CLOCKS_PER_SEC)/NREPS;
        printf(" %f ms",avg_time);
    }
    //search time
    for (int k=0; k<TEST_MAX; k+=25) {
        printf("\nAverage search time on a tree with %d random keys",k);
        start=clock();
        int rnd_key = rand();
        //allocate and fill the tree
        for (int i = 1; i<k; i++) {
            avl_insert(&emptyTrees[0], rand());
        }
        avl_insert(&emptyTrees[0], rnd_key);//yes, the insertion order will affect the result slightly...
        start = clock();
        for (int i=0; i<NREPS; i++) {
            if ((float)rand()/RAND_MAX>0.5) {//known to be in the tree
                avl_tree_search(emptyTrees[0], rnd_key);
            }else {//unknown random key
                avl_tree_search(emptyTrees[0], rand());
            }
        }
        diff=clock()-start;
        avg_time = ((float)diff*1000/CLOCKS_PER_SEC)/NREPS;
        printf(" %f ms",avg_time);
        destroy_avl_tree(&emptyTrees[0]);
    }


    printf("\n");
    return 0;
}
