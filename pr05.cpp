#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>

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
    var(size_t n) : _size{n}
    {
        _data = new int[n];
    }
    ~var()
    {
        delete[] _data;
    }
    var(int *p, size_t n)
    {
        _size = n;
        _data = p;
    }
    var(const std::initializer_list<int> &l) : var(l.size())
    {
        std::copy(l.begin(), l.end(), _data);
    }
    var(const var &a)
    {
        _size = a.size();
        _data = new int[_size];
        for (size_t i = 0; i < size(); i++)
        {
            _data[i] = a.data()[i];
        }
    }
    var &operator=(const var &o)
    {
        var copy{o};
        std::swap(copy._data, _data);
        std::swap(copy._size, _size);
        return (*this);
    }
    var(var &&m)
    {
        _data = m._data;
        _size = m._size;

        m._data = nullptr;
        m._size = 0;
    }
    var &operator=(var &&m)
    {
        var copy{std::move(m)};
        std::swap(copy._data, _data);
        std::swap(copy._size, _size);
        return *this;
    }
    bool operator==(const var &r)
    {
        return std::equal(_data, _data + size(), r._data, r._data + r.size());
    }
    bool operator!=(const var &r)
    {
        return !(*this == r);
    }
    friend inline bool operator<(const var &l, const var &r)
    {
        return std::lexicographical_compare(l._data, l._data + l.size(), r._data, r._data + r.size());
    }
    friend inline bool operator>(const var &lhs, const var &rhs) { return rhs < lhs; }
    friend inline bool operator<=(const var &lhs, const var &rhs) { return !(lhs > rhs); }
    friend inline bool operator>=(const var &lhs, const var &rhs) { return !(lhs < rhs); }
    friend std::ostream& operator<<(std::ostream& os, const var& obj)
    {
        for(size_t i=0; i < obj.size(); ++i)
            os << obj[i];
        return os;
    }
    friend std::istream& operator>>(std::istream& is, var& o) {
        size_t x = 0;
        is >> x;
        if (x) {
            var copy(x);
            for (size_t i = 0; i < x; ++i) {
                is >> copy[i];
            }
            std::swap(copy._data, o._data);
            std::swap(copy._size, o._size);
        }
        return is;
    }
    int& operator[](std::size_t idx) { return _data[idx]; }
    const int& operator[](std::size_t idx) const { return _data[idx]; }
    // decltype(auto) operator[](this auto& self, std::size_t idx) 
    // { 
    //     return self._data[idx]; 
    // }
};

int main()
{

    var a;
    std::cin >> a;
    std::cout << a;
}
