#include <iostream>

class Vector
{
    unsigned int _size;
    // _list; реализация списка целых чисел
public:
    ~Vector() // dtor
    {
        std::cout << "dtor ";
        // реализация здесь
    }

    Vector() // default ctor
    {
        std::cout << "default ctor ";
        // реализация здесь
    }

    Vector(const unsigned int size, const int val = 0) // parametric ctor
    {
        std::cout << "param ctor ";
        // реализация здесь
    }

    Vector(const Vector &other) // copy ctor
    {
        std::cout << "copy ctor ";
        // реализация здесь
    }

    Vector(Vector &&other) noexcept // move ctor
    {
        std::cout << "move ctor ";
        // реализация здесь
    }

    friend std::ostream &
    operator<<(std::ostream &os, const Vector &obj)
    {
        for (unsigned int i = 0; i < obj._size; i++)
        {
            os << obj._list[i] << " ";
        }

        return os;
    }
};

int main(int argc, char const *argv[])
{
    int x, y, z;

    std::cin >> x >> y >> z;

    Vector a;

    std::cout << a << " ";

    Vector b(x);

    std::cout << b << " ";

    Vector c(std::move(b));

    std::cout << c << " " << b << " ";

    Vector d(Vector(y, z));

    std::cout << d << " ";

    Vector e = d;

    std::cout << d;

    return 0;
}
