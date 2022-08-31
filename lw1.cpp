#include <algorithm>
#include <iostream>

struct Vector
{
    unsigned int _size{0};
    // переменная _list должна быть массивом/списком из элементов типа int;
};

int norm(Vector &data);
void init(Vector &data, unsigned int size);
void clear(Vector &data);
int pop(Vector &data);
void push(Vector &data, int val);

bool cmp(int left, int right)
{
    return left < right;
}

int main(void)
{
    Vector v;
    unsigned int size = 0;
    std::cin >> size;
    int push_val = 0;
    std::cin >> push_val;

    init(v, size);
    for (size_t i = 0; i < v._size; i++)
    {
        std::cin >> v._list[i];
    }

    push(v, push_val);

    for (size_t i = 0; i < v._size; i++)
    {
        std::cout << v._list[i] << " ";
    }

    // укажите начало и конец списка в соответствии с вашей реализацией
    std::sort(, , cmp);

    std::cout << pop(v) << " ";

    for (size_t i = 0; i < v._size; i++)
    {
        std::cout << v._list[i] << " ";
    }

    std::cout << norm(v) << " ";

    clear(v);

    std::cout << norm(v);
}

int norm(Vector &data)
{
}

void init(Vector &data, unsigned int size)
{
}

void clear(Vector &data)
{
}

int pop(Vector &data)
{
}

void push(Vector &data, int val)
{
}
