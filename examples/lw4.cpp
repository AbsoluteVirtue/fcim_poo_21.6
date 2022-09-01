#include <iostream>

class Iterable
{

protected:
    unsigned int _size{0};
    int *_list{nullptr};
};

class Vector : public Iterable
{

public:
    ~Vector()
    {
        delete[] _list;
        _list = nullptr;
    }

    Vector()
    {
        _size = 0;
        _list = nullptr;
    }

    Vector(const unsigned int size, const int val = 0)
    {
        if (size == 0)
            return;

        _list = new int[size];
        for (unsigned int i = 0; i < size; i++)
        {
            _list[i] = val;
        }

        _size = size;
    }

    Vector(const std::initializer_list<int> &il)
    {
        _size = 0;
        _list = nullptr;
        *this = il;
    }

    Vector(const Vector &other)
    {
        _size = 0;
        _list = nullptr;
        *this = other;
    }

    Vector(Vector &&other) noexcept
    {
        _size = 0;
        _list = nullptr;
        *this = other;
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

    friend std::istream &
    operator>>(std::istream &is, Vector &obj)
    {
        for (unsigned int i = 0; i < obj._size; i++)
        {
            is >> obj._list[i];
        }

        return is;
    }

    Vector &operator=(const std::initializer_list<int> &il)
    {
        delete[] _list;

        _size = il.size();
        _list = new int[_size];
        std::copy(il.begin(), il.end(), _list);

        return *this;
    }

    Vector &operator=(const Vector &other)
    {
        if (this == &other)
            return *this;

        delete[] _list;

        _size = other._size;
        _list = new int[_size];
        for (unsigned int i = 0; i < _size; i++)
        {
            _list[i] = other._list[i];
        }

        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (this == &other)
            return *this;

        delete[] _list;

        _size = other._size;
        _list = other._list;

        other._list = nullptr;
        other._size = 0;

        return *this;
    }

    int &operator[](unsigned int idx)
    {
        if (idx >= _size)
            idx = _size - 1;
        return _list[idx];
    }

    Vector &operator+=(const int val)
    {
        int *tmp = new int[_size + 1];
        for (unsigned int i = 0; i < _size; i++)
        {
            tmp[i] = _list[i];
        }
        delete[] _list;
        _list = tmp;
        tmp[_size] = val;
        ++_size;

        return *this;
    }

    friend Vector operator+(Vector lhs, const int val)
    {
        lhs += val;
        return lhs;
    }

    friend Vector operator+(Vector lhs, const Vector &rhs)
    {
        Vector tmp;
        tmp._size = lhs._size + rhs._size;
        tmp._list = new int[tmp._size];
        for (unsigned int i = 0; i < lhs._size; i++)
        {
            tmp._list[i] = lhs._list[i];
        }

        for (unsigned int i = 0, j = lhs._size; i < rhs._size; i++, j++)
        {
            tmp._list[j] = rhs._list[i];
        }

        return std::move(tmp);
    }

    int operator--(int)
    {
        --_size;
        int val = _list[_size];
        int *tmp = new int[_size];

        for (unsigned int i = 0; i < _size; i++)
        {
            tmp[i] = _list[i];
        }
        delete[] _list;
        _list = tmp;

        return val;
    }
};

class Queue : public Vector
{

public:
    Queue() {}
    Queue(const Vector &obj) : Vector(obj) {}
    Queue(const std::initializer_list<int> &il) : Vector(il) {}

    int &
    operator[](unsigned int idx) = delete;
    friend std::istream &
    operator>>(std::istream &is, Queue &obj) = delete;
    friend Queue
    operator+(Queue lhs, const int val) = delete;
    friend Queue
    operator+(Queue lhs, const Queue &rhs) = delete;
    friend Queue
    operator+(Queue lhs, const Vector &rhs) = delete;
    int
    operator--(int) = delete;

    void
    operator--()
    {
        if (0 == _size)
            return;

        int *tmp = new int[_size - 1];

        for (unsigned int i = 0, j = 1; j < _size; i++, j++)
        {
            tmp[i] = _list[j];
        }
        delete[] _list;
        --_size;
        _list = tmp;

        return;
    }

    const int &
    operator~() const
    {
        return *(_list + (_size - 1));
    }

    const int &
    operator*() const
    {
        return *_list;
    }
};

class Feed
{
    Queue numbers;
    unsigned int size{0};

public:
    void
    push(int val)
    {
        this->numbers += val;
        ++this->size;
    }

    void
    pop()
    {
        if (this->size > 0) 
        {
            --this->numbers;
            --this->size;
        }
    }

    const int &
    head() { return *this->numbers; }

    const int &
    tail() { return ~this->numbers; }

    bool
    empty() { return this->size == 0; }
};

class Producer
{
    Vector values;
    unsigned int size{0};

public:
    Producer()
    {
        int val = 0;
        std::cin >> val;

        if (val > 0)
        {
            this->size = val;
            for (unsigned int i = 0; i < this->size; i++)
            {
                std::cin >> val;
                this->values += val;
            }
        }
    }

    bool
    produce(Feed & feed)
    {
        if (!this->size) return false;

        feed.push(this->values--);
        --this->size;

        return true;
    }
};

class Consumer
{
    Vector values;

public:
    Consumer() {}

    bool
    consume(Feed & feed)
    {
        if (feed.empty()) return false;

        this->values += feed.head();
        feed.pop();

        return true;
    }

    void
    report_status()
    {
        std::cout << this->values;
    }
};

int main(int argc, char const *argv[])
{
    Producer pro;
    Consumer con;
    Feed feed;

    while (pro.produce(feed));

    while (con.consume(feed));

    con.report_status();

    return 0;
}
