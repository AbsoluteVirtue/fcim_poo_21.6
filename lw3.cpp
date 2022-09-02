#include <assert.h>
#include <iostream>
#include <sstream>


struct container
{
    unsigned int size() const;
    int front() const;
    int back() const;
    int norm() const;
    friend bool operator==(const container &lhs, const container &rhs);
    friend bool operator!=(const container &lhs, const container &rhs);
    friend bool operator<(const container &lhs, const container &rhs);
    friend bool operator>(const container &lhs, const container &rhs);
    friend bool operator<=(const container &lhs, const container &rhs);
    friend bool operator>=(const container &lhs, const container &rhs);
    friend std::ostream &operator<<(std::ostream &os, const container &object);
    friend std::istream &operator>>(std::istream &is, container &object);
    void insert(const unsigned int idx, const int x);
    void append(const int x);
    void extend(const container &other);
    int pop(const unsigned int idx);
    void remove(const int x);
    unsigned int index(const int x) const;
    unsigned int count(const int x) const;
    int &operator[](const unsigned int idx);
    const int operator[](const unsigned int idx) const;
    container &operator=(const container &other);
    container(const container &other);
    container(const int *x, const unsigned int n);
    container(const unsigned int n);
    container();
    ~container();
private:
    int *value{nullptr};
    unsigned int length{0};
};

int main(int argc, char const *argv[])
{
    std::stringstream ss{"1 3 5 7 9"};

    container a(5);
    ss >> a;
    assert(5 == a.size());
    assert(1 == a[0]);
    assert(9 == a[4]);

    container b{a};
    assert(a == b);
    assert(3 == b[1]);
    assert(7 == b[3]);

    b[4] = 0;
    assert(0 == b[4]);
    assert(b < a);

    container c;
    c = b;
    assert(b == c);
    assert(1 == c[0]);
    assert(0 == c[4]);

    std::cout << c;
}
