#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "binary_tree.h"
#define BUFLEN 1024

void insert(struct node **root, int value) {
    // root points to NULL?
    if(!(*root)) {
        struct node *tmp;
        tmp = (struct node *) malloc(sizeof(struct node));
        tmp->left = tmp->right = NULL;
        tmp->key = value;
        *root = tmp;
        return;
    }

    if(value < (*root)->key) {
        insert(&((*root)->left), value);
    } else if(value > (*root)->key) {
        insert(&((*root)->right), value);
    }
    // если value == (*root)->key => вставки не будет
}

void delete_tree(struct node *root) {
    if(root != NULL) {
        if(root->left != NULL) {
            delete_tree(root->left);
        }

        if(root->right != NULL) {
            delete_tree(root->right);
        }

        free(root);
    }
}

struct node* search(struct node *root, int value) {
    if(!root) {
        return NULL;
    }

    if (value < root->key) {
        return search(root->left, value); //меньше - искать в левом поддереве
    }
    else if(value > root->key) {
        return search(root->right, value); //больше - искать в правом поддереве
    }
    else {
        return root;
    }
}

struct node* tree_maximum(struct node *root) {
    if(root != NULL) {
        while(root->right != NULL) {
            root = root->right;
        }
    }

    return root;
}

struct node* tree_minimum(struct node *root) {
    if(root != NULL) {
        while(root->left != NULL) {
            root = root->left;
        }
    }

    return root;
}

struct node* tree_successor(struct node *root) {
    if(root->right != NULL)
        return tree_minimum(root->right);
    else {

    }

    return root;
}

void traverse_inorder(struct node *root) {
    if(!root)
        return;

    printf("( ");
    traverse_inorder(root->left);
    printf(") %i (", root->key);
    traverse_inorder(root->right);
    printf(" )");
}

void traverse_inorder_stack(struct node *root) {
    if(!root)
        return;

    struct item *stack_top = NULL;
    while(root != NULL || stack_top != NULL) {
        if(root->left != NULL) {
            push(stack_top, root->key, root->right);
            root = root->left;
        }
        else {
            printf("%i\n", root->key);
            if(root->right != NULL) {
                // go rigth if the right node exists
                root = root->right;
            }
            else {
                if(stack_top != NULL) {
                    root->key = stack_top->key;
                    root->right = stack_top->right;
                    stack_top = pop(stack_top);
                }
                else
                    root = NULL;
            }
        }
    }
}

// удаляет корень из бинарного дерева, возвращает новый корень
// в случае выделения под узел динамической памяти
// о её освобождении должен заботиться вызывающий код
struct node* delete_root(struct node* root) {
    if(root->left == NULL)
        return root->right;

    if(root->right == NULL)
        return root->left;

    struct node *tek = root->right;
    if(tek->left == NULL) {
        tek->left = root->left;
        return tek;
    }

    struct node *prev;
    while(tek->left != NULL) {
        prev = tek;
        tek = tek->left;
    }

    prev->left = tek->right;
    tek->left = root->left;
    tek->right = root->right;

    return tek;
}

struct node* parse_node(char **str) {
    enum states {opening_bracket, digit_closing, digit_opening, closing_bracket};
    enum states state = opening_bracket;

    int val = 0;
    struct node *result = NULL;

    while(**str != '\0') {
        if(**str == ' ') {
            (*str)++;
            continue;
        }

        switch(state) {
        case opening_bracket:
            // ожидаем открывающей скобки
            if(**str == '(')
                state = digit_closing;
            else {
                fprintf(stderr, "Expecting '('.\n");
                exit(1);
            }

            (*str)++;
            break;
        case digit_closing:
            // ожидаем цифру или закрывающую скобку
            if(**str >= '0' && **str <= '9') {
                // в накопителе может быть только 0
                val = (int) **str - '0';
                state = digit_opening;
                (*str)++;
            }
            else if(**str == ')') {
                (*str)++;
                return NULL;
            }
            else {
                fprintf(stderr, "Expecting digit or ')'.\n");
                exit(1);
            }

            break;
        case digit_opening:
            // цифра
            if(**str >= '0' && **str <= '9') {
                val = val*10 + (**str - '0');
                (*str)++;
            }
            else if(**str == '(') {
                struct node *left = parse_node(str);
                struct node *right = parse_node(str);

                result = malloc(sizeof(struct node));
                if(result == NULL) {
                    fprintf(stderr, "Can't get memory!\n");
                    exit(1);
                }

                result->key = val;
                result->left = left;
                result->right = right;
                // далее ожидаем закрывающую скобку
                state = closing_bracket;
            }
            else {
                fprintf(stderr, "Expecting digit or '('.\n");
                exit(1);
            }

            break;
        case closing_bracket:
            if(**str == ')') {
                (*str)++;
                return result;
            }
            else {
                fprintf(stderr, "Expecting ')'.\n");
                exit(1);
            }
        }
    }

    fprintf(stderr, "Invalid format\n");
    exit(1);
}
