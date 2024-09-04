#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H
#include <stddef.h>
#include <stdbool.h>
#include "../avl_tree.h"
typedef AVLNode* val_type;
typedef struct {
    val_type *data;
    int max_size;
    int top;
} ArrayStack;

ArrayStack *create_stack(int max_size);
ArrayStack *destroy_stack(ArrayStack **ppStack);
bool push(ArrayStack *pStack,val_type val);
val_type pop(ArrayStack *pStack);
bool isEmptyStack(ArrayStack *pStack);
bool isFullStack(ArrayStack *pStack);
#endif
