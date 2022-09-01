#include <cstdlib>
#include <cstring>

#include <iostream>
#include <string>

template <unsigned N, unsigned M>
int c_string_compare(const char (&a)[N], const char (&b)[M])
{
    return strcmp(a, b);
}

template <typename T>
class queue
{
    size_t _size{0};
    T *arr{NULL};

public:
    queue(std::initializer_list<T> il)
    {
        _size = il.size();
        arr = (T *)calloc(_size, sizeof(T));
        std::copy(il.begin(), il.end(), arr);
    };
    ~queue()
    {
        free(arr);
    }
    const size_t size() const
    {
        return _size;
    }
    void push_back(T x)
    {
        T *tmp = (T *)calloc(_size + 1, sizeof(T));
        if (tmp == NULL)
        {
            return;
        }
        for (size_t i = 0; i < _size; ++i)
        {
            tmp[i] = arr[i];
        }
        tmp[_size] = x;
        free(arr);
        arr = tmp;
        _size += 1;
    }
    void pop_front()
    {
        if (!_size)
        {
            return;
        }
        _size -= 1;
        T *tmp = (T *)calloc(_size, sizeof(T));
        if (tmp == NULL)
        {
            return;
        }
        for (size_t i = 0; i < _size; ++i)
        {
            tmp[i] = arr[i + 1];
        }
        free(arr);
        arr = tmp;
    }
    const T *begin() const
    {
        return arr;
    }
    const T *end() const
    {
        return arr + _size;
    }
    bool operator<(const queue<T> &other);
};

template <typename T>
bool queue<T>::operator<(const queue<T> &other)
{
    if (this->_size != other._size)
        return false;

    for (size_t i = 0; i < this->_size; i++)
    {
        if (other.arr[i] != this->arr[i])
            return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    std::cout << c_string_compare("hello", "world") << std::endl;

    queue<int> Q = {1, 2, 3};
    queue<int> R = {1, 2, 3};

    std::cout << ((Q < R) ? "true" : "false");
}
