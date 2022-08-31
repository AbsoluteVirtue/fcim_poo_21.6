#include <iostream>

class Vector
{
    unsigned int _size;
    // _list; реализация списка целых чисел
public:
    ~Vector() // dtor
    {
        // реализация здесь
    }

    Vector() // default ctor
    {
        // реализация здесь
    }

    Vector(const unsigned int size, const int val = 0) // parametric ctor
    {
        // реализация здесь
    }

    Vector(const Vector &other) // copy ctor
    {
        // реализация здесь
    }

    Vector(Vector &&other) noexcept // move ctor
    {
        // реализация здесь
    }

    Vector &operator=(const Vector &other)
    {
        // реализация здесь
    }

    Vector &operator=(Vector &&other) noexcept
    {
        // реализация здесь
    }

    int &operator[](unsigned int idx)
    {
        // реализация здесь
    }

    Vector &operator+=(const int val)
    {
        // реализация здесь
    }

    friend Vector operator+(Vector lhs, const int rhs)
    {
        // реализация здесь
    }

    friend Vector operator+(Vector lhs, const Vector &rhs)
    {
        // реализация здесь
    }

    Vector operator--(int)
    {
        // реализация здесь
    }

    friend std::istream &operator>>(std::istream &is, Vector &obj)
    {
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

int main()
{
    int x, y, z;

    std::cin >> x >> y >> z;

    Vector a(x);

    std::cin >> a;

    std::cout << a;

    Vector b = a;

    b += y;

    std::cout << b-- << " ";

    Vector c = a + b;

    c[y] = z;

    std::cout << c << c[x];

    Vector d = d;

    return 0;
}
