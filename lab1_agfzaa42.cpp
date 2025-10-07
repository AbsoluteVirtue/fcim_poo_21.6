#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct item {
    void *data;
    struct item *next;
} item;

typedef struct queue {
    item *front;
    item *back;
    size_t size;
} queue;

void push(queue *q, void *p) {
    item *tmp = malloc(sizeof(item));
    tmp->data = p;
    tmp->next = NULL;
    if (q->back) q->back->next = tmp;
    else q->front = tmp;
    q->back = tmp;
    q->size++;
}

void pop(queue *q) {
    item *tmp = q->front;
    if (tmp) {
        q->front = tmp->next;
        q->size--;
        if (tmp == q->back) q->back = NULL;
    }
    free(tmp);
}

typedef struct node {
    int x;
    struct node *left;
    struct node *right;
} node;

typedef node *tree;

void print(tree parent, int padding) {
    if (!parent) return;

    char p[100] = {0};
    for (int i = 0; i < padding; ++i) strcat(p, "\t");
    print(parent->right, padding + 1);
    printf("%s%d\n", p, parent->x);
    print(parent->left, padding + 1);
}

void insert(tree *n, int v) {
    if (!*n) {
        *n = malloc(sizeof(node));
        (*n)->x = v;
        (*n)->right = NULL;
        (*n)->left = NULL;
        return;
    }
    if (v > (*n)->x) {
        insert(&(*n)->right, v);
    } else {
        insert(&(*n)->left, v);
    }
}

void clear(tree *n) {
    if (NULL == *n) return;
    clear(&(*n)->left);
    clear(&(*n)->right);
    free(*n);
    *n = NULL;
}

#define count 10

int main() {

    tree root = NULL;
    int a[count] = {6, 3, 8, 7, 2, 5, 1, 0, 9, 4};
    for (size_t i = 0; i < count; i++)
    {
        insert(&root, a[i]);
    }

    print(root, 0);

    clear(&root);
    clear(&root);
    root = NULL;
}
