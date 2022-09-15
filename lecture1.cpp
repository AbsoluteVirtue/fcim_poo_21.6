#include <array>
#include <stdio.h>


struct c_struct
{
// public:
    int v[10];
};

unsigned int count(c_struct a)
{
    return sizeof(a.v) / sizeof(int);
}

unsigned int count(int a[10])
{
    return sizeof(a) / sizeof(int);
}

unsigned int count(std::array<int, 10> &a)
{
    return sizeof(a) / sizeof(int);
}

class cpp_struct 
{
// private:
    int *v{nullptr};
    unsigned int length{0};
public: // для class нужно задавать явно
    unsigned int count()
    {
        return length;
    }

    cpp_struct(unsigned int n) : v(new int [n]), length(n) {}

    ~cpp_struct()
    {
        delete [] v;
    }
};

int main(int argc, char const *argv[])
{
    int a[10];
    printf("%d ", count(a));

    std::array<int, 10> b;
    printf("%d ", count(b));

    c_struct c;
    printf("%d ", count(c));

    cpp_struct d(10);
    printf("%d ", d.count());
}
