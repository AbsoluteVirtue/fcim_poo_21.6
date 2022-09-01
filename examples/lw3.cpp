#include <iostream>

class Vector
{
    unsigned int _size;
    int * _list;
public:
    ~Vector()
    {
        delete [] _list;
        _list = nullptr;
    }

    Vector()
    {
        _size = 0;
        _list = nullptr;
    }

    Vector(const unsigned int size, const int val = 0)
    {
        if (size == 0) return;

        _list = new int [size];
        for (unsigned int i = 0; i < size; i++)
        {
            _list[i] = val;
        }

        _size = size;
    }

    Vector(const Vector & other)
    {
        _size = 0;
        _list = nullptr;
        *this = other;
    }

    Vector(Vector && other) noexcept
    {
        _size = 0;
        _list = nullptr;
        *this = std::move(other);
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

    friend std::istream & 
    operator>>(std::istream & is, Vector & obj)
    {
        for (unsigned int i = 0; i < obj._size; i++)
        {
            is >> obj._list[i];
        }
        
        return is;
    }

    Vector & operator=(const Vector & other)
    {
        if (this != &other)
        {
            delete [] _list;

            _size = other._size;
            _list = new int [_size];
            for (unsigned int i = 0; i < _size; i++)
            {
                _list[i] = other._list[i];
            }
        }
        return *this;
    }

    Vector & operator=(Vector && other) noexcept
    {
        if (this != &other)
        {
            delete [] _list;

            _size = other._size;
            _list = other._list;

            other._list = nullptr;
            other._size = 0;
        }
        return *this;
    }

    int & operator[](unsigned int idx)
    {
        if (idx >= _size) idx = _size - 1;
        return _list[idx];
    }

    Vector & operator+=(const int val)
    {
        int * tmp = new int [_size + 1];
        for (unsigned int i = 0; i < _size; i++)
        {
            tmp[i] = _list[i];
        }
        delete [] _list;
        _list = tmp;
        tmp[_size] = val;
        _size += 1;

        return *this;
    }

    friend Vector operator+(Vector lhs, const int val)
    {
        lhs += val;
        return lhs;
    }

    friend Vector operator+(Vector lhs, const Vector & rhs)
    {
        Vector tmp;
        tmp._size = lhs._size + rhs._size;
        tmp._list = new int [tmp._size];
        for (unsigned int i = 0; i < lhs._size; i++)
        {
            tmp._list[i] = lhs._list[i];
        }

        for (unsigned int i = 0, j = lhs._size; i < rhs._size; i++, j++)
        {
            tmp._list[j] = rhs._list[i];
        }
        
        // std::copy(lhs._list, lhs._list + lhs._size, tmp);
        // std::copy(rhs._list, rhs._list + rhs._size, tmp + lhs._size);

        return std::move(tmp);
    }

    int operator--(int)
    {
        _size -= 1;
        int val = _list[_size];
        int * tmp = new int [_size];

        for (unsigned int i = 0; i < _size; i++)
        {
            tmp[i] = _list[i];
        }
        delete [] _list;
        _list = tmp;

        return val;
    }
};

int main(int argc, char const *argv[])
{
    int x, y, z; // 5 10 100 1 2 3 4 5

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

    // 1 2 3 4 5 10 1 2 3 4 5 1 2 3 4 100 1

    return 0;
}
