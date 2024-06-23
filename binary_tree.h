#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    int key;
};

void insert(struct node **root, int value);
void delete_tree(struct node *root);
struct node* search(struct node *root, int value);
struct node* tree_maximum(struct node *root);
struct node* tree_minimum(struct node *root);
struct node* tree_successor(struct node *root);
void traverse_inorder(struct node *root);
void traverse_inorder_stack(struct node *root);
struct node* delete_root(struct node* root);
struct node* parse_node(char **str);

#endif //BINARY_TREE_H
