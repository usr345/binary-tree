#ifndef stack_h
#define stack_h
struct item {
    struct node *right;
    int key;
    struct item *next;
};

struct item* push(struct item *stack_top, int key, struct node *right);
struct item* pop(struct item *stack_top);
#endif
