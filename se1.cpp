#include <iostream>
#include <utility>

struct test
{
    int a;
    int b;
};

class test_c
{
    int *a{nullptr};

public:
    test_c() = delete;

    test_c(const int val)
    {
        this->a = new int;
        *(this->a) = val;
    }

    test_c(const test_c &other)
    {
        this->a = new int;
        *(this->a) = *(other.a);
    }

    test_c(const test_c &&other)
    {
        int *tmp = std::move(other.a);
    }

    test_c(const char *str)
    {
        this->a = new int;
        *(this->a) = std::atoi(str);
    }

    int get_a() const
    {
        return *(this->a);
    }

    ~test_c()
    {
        delete this->a;
        this->a = nullptr;
    }
};

void set_a(test obj, int val)
{
    obj.a = val;
}

int main(int argc, char const *argv[])
{
    std::cout << "skip";
    test_c t1(100);
    test_c t2(t1);

    test_c t3 = t2;

    test_c t4(test_c(1000));

    test_c t5("hello");

    std::cout << &t4;
    return 0;
}
