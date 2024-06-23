#include <stdlib.h>
#include "stack.h"

struct item* push(struct item *stack_top, int key, struct node *right) {
    struct item *my_item = malloc(sizeof(struct item));

    my_item->key = key;
    my_item->right = right;
    my_item->next = stack_top;

    return my_item;
}

struct item* pop(struct item *stack_top) {
    struct item *result = stack_top->next;
    free(stack_top);

    return result;
}
