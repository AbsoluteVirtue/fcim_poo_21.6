#include <iostream>
#include <initializer_list>
#include <cstddef>

class container {
protected:
    int x{0};
public:
    void f() {
        x ++;
    }
};

class vector : public container {
    int *p{nullptr};
public:
    void push_back() {
        container::f();
    }
};

template <typename Container = vector>
class queue {
    Container c;
public:
    void push() {
        c.push_back();
    }
};

class abstract_data_t
{
public:
    virtual int &operator[](size_t) = 0;
};

class deque : public abstract_data_t
{
    int *p{nullptr};
    size_t n{0};

public:
    deque(std::initializer_list<int> il) {
        n = il.size();
        p = new int [n];
        std::copy(il.begin(), il.end(), p);
    }

    size_t size() const
    {
        return n;
    }

    int &operator[](size_t i) override
    {
        return p[i];
    }

    auto operator[](size_t i) const
    {
        return p[i];
    }

    template <typename Container>
    friend auto &operator << (std::ostream& os, const Container& d) {
        for (size_t i = 0; i < d.size(); i++)
        {
            os << (d[i]) << " ";
        }
        return os;
    }
};

int main()
{
    deque *d = new deque{1, 2, 3, 4, 5};
    std::cout << *d;

    abstract_data_t *adt = new deque{1, 2, 3, 4};
    std::cout << *adt;
}
