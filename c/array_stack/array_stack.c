#include "array_stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

ArrayStack *create_stack(int max_size)
{
    ArrayStack *pStack = (ArrayStack *)malloc(sizeof(ArrayStack));
    if (!pStack) {
        return NULL;
    }
    pStack->data=(val_type*) malloc(max_size*sizeof(val_type));
    if (!pStack->data) {
        printf("\nCouldn't allocate enough space for the stack");
        free(pStack);
        return NULL;
    }
    pStack->max_size = max_size;
    pStack->top=-1;
    return pStack;
}

ArrayStack *destroy_stack(ArrayStack **ppStack)
{
    if (ppStack) {
        if (*ppStack){
            if ((*ppStack)->data) {
                free((*ppStack)->data);
                (*ppStack)->data=NULL;
            }
            free(*ppStack);
            *ppStack=NULL;
        }
        ppStack=NULL;
    }
    return NULL;
}

bool push(ArrayStack *pStack,val_type val)
{
    if (pStack) {
        if (!isFullStack(pStack)){
            pStack->data[++pStack->top]=val;
            return true;
        }else{
            printf("\nCan't push: full stack!");
        }
    }
    return false;
}

val_type pop(ArrayStack *pStack)
{
    if (pStack) {
        if (!isEmptyStack(pStack)) {
            return pStack->data[pStack->top--];
        }else {
            printf("\nCan't pop: empty stack!");
        }
    }else {
        printf("\nError: can't dereference a null pointer to a stack");
    }
    return (val_type){0}; // Return a default value
}

bool isEmptyStack(ArrayStack *pStack)
{
    if (pStack) {
        if (pStack->top==-1)
            return true;
    }
    return false;
}

bool isFullStack(ArrayStack *pStack)
{
    if (pStack) {
        if (pStack->top>=(pStack->max_size-1)) {
            return false;
        }
        else {
            return true;
        }
    }else {
        printf("\nError: can't dereference a null pointer to a stack");
        //for all practical intents u can't push into it as if it was a proper, but full, stack!
        //hence a true value is a decent default
        return true;
    }
}
