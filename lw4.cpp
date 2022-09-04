#include <assert.h>
#include <iostream>
#include <string>


template <typename T>
inline
void swap(T& a, T& b)
{
    T tmp(a);
    a = b;
    b = tmp;
}

template <typename T>
struct container
{
    // код с реализацией здесь, за основу берите предыдущую лабораторную
};

int main(int argc, char const *argv[])
{
    container<int> a({2, 3, 5, 7});
    
    a.append(11);
    assert(11 == a[a.size() - 1]);

    a.insert(0, 1);
    assert(1 == a[0]);

    a.extend(container<int>({13, 17, 19}));
    assert(6 == a.index(13));

    a.remove(19);
    assert(0 == a.count(19));
    assert(8 == a.size());

    container<int> b(a);
    assert(a == b);

    b[0] = 0;
    assert(0 == b.front());
    assert(17 == b.pop(20));
    assert(13 == b.back());

    container<char> c = "abra";
    assert(0 == c.back());
    assert(0 == c.pop(c.size()));

    c.append('c');
    assert('c' == c[c.size() - 1]);

    c.insert(c.size(), 'a');
    assert(0 == c.count(0));
    assert(6 == c.size());

    c.extend(container<char>("dabra"));
    assert(c.size() - 1 == c.index(0));
    assert(1 == c.count(0));
    assert(12 == c.size());

    c[0] = 'A';
    assert('A' == c.front());

    std::cout << c;
}
