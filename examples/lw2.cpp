#include <iostream>

class Vector
{
    unsigned int _size;
    int * _list;
public:
    ~Vector() // dtor
    {
        std::cout << "dtor ";
        delete [] _list;
        _list = nullptr;
    }

    Vector() // default ctor
    {
        std::cout << "default ctor ";
        _size = 0;
        _list = nullptr;
    }

    Vector(const unsigned int size, const int val = 0) // parametric ctor
    {
        std::cout << "param ctor ";
        if (size == 0) return;

        _list = new int [size];
        for (unsigned int i = 0; i < size; i++)
        {
            _list[i] = val;
        }

        _size = size;
    }

    Vector(const Vector & other) // copy ctor
    {
        std::cout << "copy ctor ";
        if (other._size == 0) return;

        _size = other._size;
        _list = new int [_size];
        for (unsigned int i = 0; i < _size; i++)
        {
            _list[i] = other._list[i];
        }
    }

    Vector(Vector && other) noexcept // move ctor
    {
        std::cout << "move ctor ";
        _size = other._size;
        _list = other._list;
        other._list = nullptr;
        other._size = 0;
    }

    friend std::ostream &
    operator<<(std::ostream & os, const Vector & obj)
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
