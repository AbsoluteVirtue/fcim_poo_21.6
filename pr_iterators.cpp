// https://internalpointers.com/post/writing-custom-iterators-modern-cpp

#include <iostream>
#include <random>

#include <iterator>
#include <cstddef>

class Vector
{
    size_t size_{0};
    int *list_{nullptr};

public:
    ~Vector()
    {
        delete[] list_;
    }

    Vector() = default;

    Vector(size_t size, int val = 0)
    {
        size_ = size;
        list_ = new int[size];
        for (size_t i = 0; i < size; i++)
        {
            list_[i] = val;
        }
    }

    Vector(const Vector &other)
    {
        *this = other;
    }

    Vector(Vector &&other) noexcept
    {
        *this = std::move(other);
    }

    Vector(const std::initializer_list<int> &il)
    {
        size_ = 0;
        list_ = nullptr;

        *this = il;
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            delete[] list_;

            size_ = other.size_;
            list_ = new int[size_];

            std::copy(other.list_, other.list_ + other.size_, list_);
        }

        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] list_;

            size_ = other.size_;
            list_ = other.list_;

            other.list_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    Vector &operator=(const std::initializer_list<int> &il)
    {
        delete[] list_;

        size_ = il.size();
        list_ = new int[size_];

        std::copy(il.begin(), il.end(), list_);

        return *this;
    }

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        pointer ptr{nullptr};

    public:
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
    };

    Iterator begin()
    {
        return Iterator(list_);
    }

    Iterator end()
    {
        return Iterator(list_ + size_);
    }
    const size_t &size() const
    {
        return size_;
    }

    const int &operator[](size_t idx) const
    {
        return list_[idx];
    }
};

int main(int argc, char const *argv[])
{
    Vector my_vec = {10, 20, 30, 40, 50, 60};

    for (Vector::Iterator it = my_vec.begin(), end = my_vec.end(); it != end; it++)
    {
        const auto i = *it;
        std::cout << i << " ";
    }

    std::cout << "\n";

    for (auto &&i : my_vec)
    {
        std::cout << i << " ";
    }
}
