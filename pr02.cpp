#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

class linked_list
{
    struct node
    {
        int data{0};
        struct node *next{nullptr};
        struct node *prev{nullptr};
    };

    node *head{nullptr};
    node *tail{nullptr};
    size_t _size{0};

public:
    size_t size()
    {
        return _size;
    }

    void set_head(int x)
    {
        if (head)
        {
            head->data = x;
        }
        else
        {
            head = new node{x};
        }
    }

    const node *get_head() const
    {
        return head;
    }

    void clear()
    {

        node *current = head;
        while (current != NULL)
        {
            node *temp = current;
            current = current->next;
            delete (temp);
        }

        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    void push_front(int value)
    {
        node *new_node = new(node){value, head, nullptr};

        if (head != nullptr)
        {
            head->prev = new_node;
        }

        head = new_node;

        if (tail == nullptr)
        {
            tail = new_node;
        }

        _size++;
    }
};

int main(void)
{
    linked_list a;

    a.push_front(3);
    a.push_front(2);
    a.push_front(1);

    a.clear();

    return 0;
}

#ifdef C
typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node;

typedef struct {
    node *head;
    node *tail;
    size_t size;
} linked_list;

void push_front(linked_list *list, int value) {
    reset_error();
    if (list == NULL) {
        list_error = true;
        return;
    }

    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        list_error = true;
        return;
    }

    new_node->data = value;
    new_node->next = list->head;
    new_node->prev = NULL;

    if (list->head != NULL) {
        list->head->prev = new_node;
    }

    list->head = new_node;

    if (list->tail == NULL) {
        list->tail = new_node;
    }

    list->size++;
}

void clear(linked_list *list) {
    reset_error();
    if (list == NULL) {
        list_error = true;
        return;
    }

    node *current = list->head;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
#endif
