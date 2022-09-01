#include <ciso646>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <iostream>

struct Rerr
{
    int _val;
    int _err;
};

struct Vector
{
    size_t _size;
    int *_list;
};

void initialize(Vector *v);
int allocate(Vector *v, size_t len);
int add(Vector *v, int x);
Rerr get(Vector *v, size_t index);
int set(Vector *v, size_t index, int x);
int calculate_norm(Vector *v);
int deallocate(Vector *v);

#define N 10

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    Vector A;

    initialize(&A);

    allocate(&A, N);

    for (size_t i = 0; i < N; ++i)
    {
        set(&A, i, rand() % 100);
        printf("%d\t", get(&A, i));
    }
    printf("\n");

    deallocate(&A);

    return 0;
}

int calculate_norm(Vector *v)
{
    int sum = 0;
    for (size_t i = 0; i < v->_size; i++)
    {
        sum += v->_list[i];
    }

    return sum;
}

int set(Vector *v, size_t index, int x)
{
    if (v->_size < 1 or index < 0 or index > v->_size - 1)
    {
        return 1;
    }

    v->_list[index] = x;

    return 0;
}

Rerr get(Vector *v, size_t index)
{
    if (v->_size < 1 or index < 0 or index > v->_size - 1)
    {
        return {0, 1};
    }

    return {v->_list[index], 0};
}

int allocate(Vector *v, size_t len)
{
    if (len < 1 or len == v->_size)
    {
        return 1;
    }

    int *tmp = (int *)calloc(len, sizeof(int));
    if (tmp == NULL)
    {
        return -1;
    }

    if (v->_list != NULL)
    {
        for (size_t i = 0; i < (v->_size > len) ? len : v->_size; i++)
        {
            tmp[i] = v->_list[i];
        }
        free(v->_list);
    }

    v->_list = tmp;
    v->_size = len;

    return 0;
}

void initialize(Vector *v)
{
    v->_size = 0;
    v->_list = NULL;
}

int add(Vector *v, int x)
{
    int *tmp = (int *)calloc(v->_size + 1, sizeof(int));
    if (tmp == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < v->_size; ++i)
    {
        tmp[i] = v->_list[i];
    }
    tmp[v->_size] = x;

    v->_size += 1;

    free(v->_list);

    v->_list = tmp;

    return 0;
}

int deallocate(Vector *v)
{
    if (v->_list == NULL)
    {
        return -1;
    }
    free(v->_list);
    v->_list = NULL;
}
