#include <iostream>
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <sstream>

class arraylist
{
    int *data{nullptr};
    size_t len{0};
    size_t capacity{0};

public:
    class iterator
    {
        int *ptr;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = int *;
        using reference = int &;

        iterator() : ptr(nullptr) {}
        iterator(int *p) : ptr(p) {}
        iterator(const iterator &other) : ptr(other.ptr) {}
        ~iterator() = default;

        iterator &operator++()
        {
            ++ptr;
            return *this;
        } // префикс
        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator &operator--()
        {
            --ptr;
            return *this;
        } // префикс
        iterator operator--(int)
        {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }

        int &operator*() { return *ptr; }
        int *operator->() { return ptr; }

        friend bool operator==(const iterator &a, const iterator &b) { return a.ptr == b.ptr; }
        friend bool operator!=(const iterator &a, const iterator &b) { return a.ptr != b.ptr; }

        int *base() const { return ptr; }
    };

    // ===== Обратный итератор =====
    class reverse_iterator
    {
        int *ptr;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = int *;
        using reference = int &;

        reverse_iterator() : ptr(nullptr) {}
        reverse_iterator(int *p) : ptr(p) {}
        reverse_iterator(const reverse_iterator &other) : ptr(other.ptr) {}
        ~reverse_iterator() = default;

        reverse_iterator &operator++()
        {
            --ptr;
            return *this;
        } // движение влево
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);
            --ptr;
            return tmp;
        }
        reverse_iterator &operator--()
        {
            ++ptr;
            return *this;
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        int &operator*() { return *ptr; }
        int *operator->() { return ptr; }

        friend bool operator==(const reverse_iterator &a, const reverse_iterator &b) { return a.ptr == b.ptr; }
        friend bool operator!=(const reverse_iterator &a, const reverse_iterator &b) { return a.ptr != b.ptr; }

        int *base() const { return ptr; }
    };

    arraylist() = default;

    explicit arraylist(size_t n) : len(n), capacity(n) { data = new int[len]{}; }

    arraylist(const std::initializer_list<int> &b) : len(b.size()), capacity(b.size())
    {
        data = new int[len];
        size_t i = 0;
        for (int v : b)
            data[i++] = v;
    }

    arraylist(iterator a, iterator b)
    {
        len = capacity = std::distance(a, b);
        data = new int[len]{};
        size_t i = 0;
        for (auto it = a; it != b; ++it)
            data[i++] = *it;
    }

    arraylist(reverse_iterator a, reverse_iterator b)
    {
        len = capacity = std::distance(a, b);
        data = new int[len]{};
        size_t i = 0;
        for (auto it = a; it != b; ++it)
            data[i++] = *it;
    }

    arraylist(const arraylist &other) : len(other.len), capacity(other.len)
    {
        data = new int[len];
        for (size_t i = 0; i < len; ++i)
            data[i] = other.data[i];
    }

    arraylist(arraylist &&other) noexcept : data(other.data), len(other.len), capacity(other.capacity)
    {
        other.data = nullptr;
        other.len = other.capacity = 0;
    }

    ~arraylist() { delete[] data; }

    arraylist &operator=(const arraylist &other)
    {
        if (this != &other)
        {
            delete[] data;
            len = other.len;
            capacity = other.len;
            data = new int[len];
            for (size_t i = 0; i < len; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    arraylist &operator=(arraylist &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            len = other.len;
            capacity = other.capacity;
            other.data = nullptr;
            other.len = other.capacity = 0;
        }
        return *this;
    }

    void push_back(int value)
    {
        if (len >= capacity)
        {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            int *temp = new int[new_capacity];
            for (size_t i = 0; i < len; ++i)
                temp[i] = data[i];
            delete[] data;
            data = temp;
            capacity = new_capacity;
        }
        data[len++] = value;
    }

    void insert(size_t index, int value)
    {
        if (index > len)
            return;
        if (len >= capacity)
        {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            int *temp = new int[new_capacity];
            for (size_t i = 0; i < len; ++i)
                temp[i] = data[i];
            delete[] data;
            data = temp;
            capacity = new_capacity;
        }
        for (size_t i = len; i > index; --i)
            data[i] = data[i - 1];
        data[index] = value;
        ++len;
    }

    void pop_back()
    {
        if (len > 0)
            --len;
    }

    void erase(size_t index)
    {
        if (index >= len)
            return;
        for (size_t i = index; i < len - 1; ++i)
            data[i] = data[i + 1];
        --len;
    }

    int &operator[](size_t index) { return data[index]; }
    const int &operator[](size_t index) const { return data[index]; }

    size_t size() const { return len; }
    bool empty() const { return len == 0; }

    bool contains(int value) const
    {
        for (size_t i = 0; i < len; ++i)
            if (data[i] == value)
                return true;
        return false;
    }
    size_t count(int value) const
    {
        size_t cnt = 0;
        for (size_t i = 0; i < len; ++i)
            if (data[i] == value)
                ++cnt;
        return cnt;
    }

    void clear()
    {
        delete[] data;
        data = nullptr;
        len = capacity = 0;
    }

    void assign(size_t dist, const int &value)
    {
        size_t count = 0;
        if (dist < size())
            count = dist;
        else
            count = size();
        for (size_t i = 0; i < count; i++)
        {
            data[i] = value;
        }
    }

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + len); }
    reverse_iterator rbegin() { return len ? reverse_iterator(data + len - 1) : reverse_iterator(nullptr); }
    reverse_iterator rend() { return len ? reverse_iterator(data - 1) : reverse_iterator(nullptr); }

    friend bool operator==(const arraylist &a, const arraylist &b)
    {
        if (a.len != b.len)
            return false;
        for (size_t i = 0; i < a.len; ++i)
            if (a.data[i] != b.data[i])
                return false;
        return true;
    }
    friend bool operator!=(const arraylist &a, const arraylist &b) { return !(a == b); }

    friend bool operator<(const arraylist &lhs, const arraylist &rhs)
    {
        size_t n = std::min(lhs.len, rhs.len);
        for (size_t i = 0; i < n; ++i)
        {
            if (lhs.data[i] < rhs.data[i])
                return true;
            if (lhs.data[i] > rhs.data[i])
                return false;
        }
        return lhs.len < rhs.len;
    }
    friend bool operator>(const arraylist &lhs, const arraylist &rhs) { return rhs < lhs; }
    friend bool operator<=(const arraylist &lhs, const arraylist &rhs) { return !(lhs > rhs); }
    friend bool operator>=(const arraylist &lhs, const arraylist &rhs) { return !(lhs < rhs); }

    friend std::ostream &operator<<(std::ostream &os, const arraylist &obj)
    {
        os << "[";
        for (size_t i = 0; i < obj.len; ++i)
        {
            os << obj.data[i];
            if (i + 1 < obj.len)
                os << ", ";
        }
        os << "]";
        return os;
    }
    friend std::istream &operator>>(std::istream &is, arraylist &obj)
    {
        for (size_t i = 0; i < obj.len; ++i)
            is >> obj.data[i];
        return is;
    }
};

using container = arraylist;

int main()
{
    container a({19, 47, 74, 91});
    for (auto it = a.begin(); it != a.end(); ++it)
        std::cout << *it << " ";

    container b(a.begin(), a.end());
    assert(a == b);
    for (auto &&it : b)
        std::cout << it << " ";

    container c;
    c.assign(std::distance(b.begin(), b.end()), 0);
    std::copy(b.begin(), b.end(), c.begin());
    assert(std::equal(c.begin(), c.end(), b.begin()));
    for (auto it = c.rbegin(); it != c.rend(); ++it)
        std::cout << *it << " ";

    container d(c.rbegin(), c.rend());
    for (auto &&it : d)
        std::cout << it << " ";
}
