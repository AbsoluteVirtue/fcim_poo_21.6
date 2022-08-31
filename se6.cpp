#include <iostream>
#include <random>
#include <vector>

#include <iterator>
#include <cstddef>

class Iterable
{
protected:
    unsigned int _size{0};
    int *_list{nullptr};

    Iterable(){};

public:
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = value_type *;
        using reference = value_type &;

        Iterator(pointer p) : ptr(p) {}

        friend bool operator==(const Iterator &a, const Iterator &b)
        {
            return a.ptr == b.ptr;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return !(a == b);
        }

        Iterator &operator++()
        {
            ++ptr;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reference operator*()
        {
            return *ptr;
        }

        pointer operator->()
        {
            return ptr;
        }

    private:
        pointer ptr{nullptr};
    };

    Iterator begin()
    {
        return Iterator(this->_list);
    }

    Iterator end()
    {
        return Iterator(this->_list + this->_size);
    }
};

class Vector : public Iterable
{
public:
    ~Vector()
    {
        delete[] this->_list;
    }

    Vector()
    {
        this->_list = nullptr;
        this->_size = 0;
    }

    Vector(unsigned int size, int val = 0)
    {
        this->_size = size;
        _list = new int[size];
        for (unsigned int i = 0; i < this->_size; i++)
        {
            this->_list[i] = val;
        }
    }

    Vector(const Vector &other)
    {
        this->_size = 0;
        this->_list = nullptr;

        *this = other;
    }

    Vector(Vector &&other)
    {
        this->_size = 0;
        this->_list = nullptr;

        *this = other;
    }

    Vector(const std::initializer_list<int> &il)
    {
        this->_size = 0;
        this->_list = nullptr;

        *this = il;
    }

    const unsigned int &size() const
    {
        return this->_size;
    }

    const int &operator[](unsigned int idx) const
    {
        return this->_list[idx];
    }

    Vector &operator=(const Vector &other)
    {
        if (this == &other)
            return *this;

        delete[] _list;

        _size = other._size;
        _list = new int[_size];
        std::copy(other._list, other._list + other._size, this->_list);

        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (this == &other)
            return *this;

        delete[] _list;

        _size = other._size;
        _list = other._list;

        other._list = nullptr;
        other._size = 0;

        return *this;
    }

    Vector &operator=(const std::initializer_list<int> &il)
    {
        delete[] _list;

        this->_size = il.size();
        _list = new int[this->_size];

        std::copy(il.begin(), il.end(), this->_list);

        return *this;
    }
};

int main(int argc, char const *argv[])
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};

    Vector my_vec = {10, 20, 30, 40, 50, 60};

    for (Vector::Iterator i = my_vec.begin(); i != my_vec.end(); i++)
    {
        std::cout << *i << " ";
    }

    std::cout << "\n";

    for (auto i : my_vec)
    {
        std::cout << i << " ";
    }

    return 0;
}
