#include <iostream>

class base
{
protected:
    int a;
    int b;

public:
    void set(int x, int y)
    {
        a = x;
        b = y;
    }

    virtual int func() = 0;
    void print()
    {
        std::cout << this->func();
    }
};

class alpha : public base
{
public:
    int func() override
    {
        return a + b;
    }
};

class bravo : public base
{
public:
    int func() override
    {
        return a * b;
    }
};

int main(int argc, char const *argv[])
{
    alpha A;
    bravo B;

    base *pa = &A;
    base *pb = &B;

    pa->set(3, 8);
    pb->set(3, 8);

    pa->print();
    std::cout << "\n";
    pb->print();

    return 0;
}
