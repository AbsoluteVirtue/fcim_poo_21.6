#include <iostream>

class Base
{
protected:
    int a;

public:
    Base(const int val = 0) : a(val) {}

    void helll() {}

    friend std::ostream &operator<<(std::ostream &os, const Base &obj)
    {
        return os << "Base a=" << obj.a << "\n";
    }
};

class Sub : public Base
{
    int b;

public:
    Sub(const int val, const int opt = 0) : Base(val), b(opt) {}

    void helll() = delete;

    friend std::ostream &operator<<(std::ostream &os, const Sub &obj)
    {
        return os << "Sub a=" << obj.Base::a << ", b=" << obj.b << "\n";
    }
};

class Interface
{
public:
    virtual void print() = 0;
};

class Comp : public Interface
{
    Base b;

public:
    Comp(const int val) : b(Base(val)) {}

    void print() override
    {
        std::cout << b;
    }
};

int main(int argc, char const *argv[])
{
    Base obj_base = Base(41);

    std::cout << obj_base;

    Sub obj_sub = Sub(42);

    std::cout << obj_sub;

    Comp obj_comp = Comp(43);

    obj_comp.print();

    return 0;
}
