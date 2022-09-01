#include <ciso646>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <utility>

struct Vector
{
    Vector() = delete;
    Vector(std::size_t len);
    Vector(std::initializer_list<int> il);
    ~Vector();

    void push_back(const int &x);
    void push_back(int &&x);
    int &operator[](std::size_t index);
    const int operator[](std::size_t index) const;
    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;
    friend std::ostream &operator<<(std::ostream &os, const Vector &obj);

private:
    std::size_t _size{0};
    int *_list{nullptr};
};

int main(int argc, char const *argv[])
{
#define N 10
    srand(time(NULL));

    Vector A(N);

    for (size_t i = 0; i < N; i++)
    {
        A[i] = rand() % 100;
        std::cout << A[i] << "\t";
    }
    std::cout << std::endl;

    A.push_back(100);

    std::cout << A;

    return 0;
}

void Vector::push_back(const int &x)
{
    int *tmp = new int[_size + 1];

    std::copy(_list, _list + _size, tmp);
    tmp[_size] = x;

    _size += 1;

    delete[] _list;

    _list = tmp;
}

void Vector::push_back(int &&x)
{
    int tmp = std::move(x);
    this->push_back(tmp);
}

std::ostream &operator<<(std::ostream &os, const Vector &obj)
{
    for (std::size_t i = 0; i < obj._size; ++i)
    {
        os << obj._list[i] << "\t";
    }

    return os;
}

Vector &Vector::operator=(const Vector &other)
{
    if (this != &other)
    {
        if (_size != other._size)
        {
            delete[] _list;
            _size = 0;
            _list = nullptr;

            _list = new int[other._size];
            _size = other._size;
        }
        std::copy(other._list, other._list + other._size, _list);
    }

    return *this;
}

Vector &Vector::operator=(Vector &&other) noexcept
{
    if (this != &other)
    {
        delete[] _list;
        _list = std::exchange(other._list, nullptr);
        _size = std::exchange(other._size, 0);
    }

    return *this;
}

int &Vector::operator[](std::size_t index)
{
    return _list[index];
}

const int Vector::operator[](std::size_t index) const
{
    return _list[index];
}

Vector::~Vector()
{
    delete[] _list;
}

Vector::Vector(std::initializer_list<int> il)
{
    _size = il.size();
    _list = new int[_size];
    std::copy(il.begin(), il.end(), _list);
}

Vector::Vector(std::size_t len)
{
    if (len < 1)
    {
        throw;
    }

    _list = new int[len];

    _size = len;
}
