#include <cassert>
#include <iostream>
#include <iterator>

class vector {
    int *data{nullptr};
    size_t n{0};
    size_t c{0};
public:
    typedef int* pointer;
    typedef std::reverse_iterator<pointer> riter;

    class iterator {
        int *p{nullptr};
    public:
        iterator(int *x) : p(x) {}
        // operator++()
        // operator--()
        // operator+()
        // operator-()
        // operator==()
        // operator!=()
        // operator*()
    };

    vector(const std::initializer_list<int>& l)
     : data(new int [l.size()]), n(l.size()), c(l.size()) 
    {
        std::copy(l.begin(), l.end(), data);
    }
    // [a, b)
    vector(pointer a, pointer b) 
    {
        n = c = b - a;
        data = new int [n];
        std::copy(a, b, data);
    }

    vector(riter a, riter b) 
    {
        n = c = b - a;
        data = new int [n];
        std::copy(a, b, data);
    }

    size_t size() const {
        return n;
    }

    int &operator [](size_t i) noexcept {
        return data[i];
    }

    auto begin() {
        return pointer(data);
    }

    auto end() {
        return pointer(data + n);
    }

    auto rbegin() {
        return riter(end());
    }

    auto rend() {
        return riter(begin());
    }
};

int main()
{
    vector v{1, 2, 3, 4, 5};

    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }

    vector w{v.begin(), v.end()};

    assert(std::equal(v.begin(), v.end(), w.begin(), w.end()));

    for (auto it = w.begin(); it != w.end(); it++)
    {
        std::cout << *it << " ";
    }

    vector z{w.rbegin(), w.rend()};
    
    for (auto &&it : z)
    {
        std::cout << it << " ";
    }
}
