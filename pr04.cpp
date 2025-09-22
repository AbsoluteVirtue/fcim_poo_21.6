#include <algorithm>
#include <initializer_list>

class var
{
private:
    size_t _size{0};
    int *_data{nullptr};

public:
    size_t size() const
    {
        return _size;
    }

    const int *data() const
    {
        return _data;
    }

    var() = default;

    var(int *p, size_t n)
    {
        _size = n;
        _data = p;
    }

    var(size_t n) : _size{n}
    {
        _data = new int[n];
    }

    ~var()
    {
        delete[] _data;
    }

    var(const std::initializer_list<int> &l) : var(l.size())
    {
        std::copy(l.begin(), l.end(), _data);
    }

    void swap(var &r) noexcept
    {
        std::swap(_size, r._size);
        std::swap(_data, r._data);
    }

    var(const var &a) : var(a.size())
    {
        for (size_t i = 0; i < size(); i++)
        {
            _data[i] = a.data()[i];
        }
    }

    var(var &&m) noexcept : _size(m.size()), _data(m.data())
    {
        m._size = 0;
        m._data = nullptr;
    }

#ifdef CANON
    var &operator=(const var &o) // оператор присваивания копированием 
    {
        if (&o != this) // проверка на самоприсваивание
        {
            delete[] _data; // т.к. это не конструктор, this уже может иметь ресурсы, которые надо освободить
            // далее повторяется код конструктора копирования:
            _size = o.size();
            _data = new int[_size];
            std::copy(o.data(), o.data() + o.size(), _data);
        }
        return *this;
    }

    var &operator=(var &&m) noexcept // оператор присваивания переносом 
    {
        if (&m != this) // проверка на самоприсваивание
        {
            delete[] _data; // т.к. это не конструктор, this уже может иметь ресурсы, которые надо освободить
            // далее повторяется код конструктора переноса:
            _size = m._size;
            _data = m._data;
            m._size = 0;
            m._data = nullptr;
        }
        return *this;
    }
#elif defined(COPY_SWAP)
    var &operator=(const var &m) // copy-and-swap: вместо дублирования кода из конструктора его можно вызвать сделав локальную переменную
    {                            // затем локальная копия меняется ресурсами с this, это позволяет не проверять самоприсваивание
        var copy(m);
        copy.swap(*this);
        return *this;
    }

    var &operator=(var &&m) noexcept
    {
        var copy(std::move(m));  // единственное отличие от копирования - вызов std::move для переноса аргумента вместо копирования
        copy.swap(*this);
        return *this;
    }
#else
    var &operator=(var copy)    // передача аргумента по значению вынуждает язык подбирать правильный конструктор автоматически
    {                           // это то же код, что и в случае copy-and-swap, роль временной переменной выполняет аргумент
        copy.swap(*this);
        return *this;
    }
#endif
};

int main()
{
    var a;                      // конструктор по умолчанию
    var b = 1;                  // конструктор size_t
    var c = b;                  // конструктор копирования
    var d = std::move(c);       // конструктор переноса
    var e = {1, 2, 3, 4, 5};    // конструктор std::initializer_list
    var f;
    f = e;                      // оператор присваивания копированием
    var g;
    g = var(2);                 // оператор присваивания переносом
} // деструкторы в обратном порядке
