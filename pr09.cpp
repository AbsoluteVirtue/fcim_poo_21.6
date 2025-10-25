// Iterators, part 2
#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <iterator>

class var
{
private:
    size_t _size{0};
    int*   _data{nullptr};

public:
    size_t size() const { return _size; }
    const int *data() const { return _data; }

    class iterator {
        int *p{nullptr};
    public:
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::contiguous_iterator_tag;

        iterator() = delete;
        iterator(int* o) : p(o) {}
        iterator(const iterator& o) : iterator(o.p) {}
        ~iterator() = default;

        value_type& operator*() { return *p; }
        value_type operator*() const { return *p; }
        friend bool operator==(const iterator& a, const iterator& b) {
            return *a == *b;
        }
        friend bool operator!=(const iterator& a, const iterator& b) { 
            return !(a == b);
        }
        friend difference_type operator-(const iterator& a, const iterator& b) {
            return a.p - b.p;
        }
        iterator& operator++() {
            ++p;
            return *this;
        }
        iterator operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }
    };

    using reverse_iterator = std::reverse_iterator<iterator>;

    var() = default;
    var(size_t n) : _size{n} { _data = new int[n]; }
    ~var() { delete[] _data; }
    var(int *p, size_t n)
    {
        _size = n;
        _data = p;
    }
    var(const std::initializer_list<int> &l) : var(l.size()) {
        std::copy(l.begin(), l.end(), _data);
    }
    var(const var &a) {
        _size = a.size();
        _data = new int[_size];
        for (size_t i = 0; i < size(); i++)
        {
            _data[i] = a.data()[i];
        }
    }
    var &operator=(const var &o) {
        var copy{o};
        std::swap(copy._data, _data);
        std::swap(copy._size, _size);
        return (*this);
    }
    var(var &&m) {
        _data = m._data;
        _size = m._size;

        m._data = nullptr;
        m._size = 0;
    }
    var &operator=(var &&m) {
        var copy{std::move(m)};
        std::swap(copy._data, _data);
        std::swap(copy._size, _size);
        return *this;
    }
    auto begin() { return iterator(_data); }
    auto cbegin() const { return iterator(_data); }
    auto rbegin() { return reverse_iterator(end()); }
    auto end() { return iterator(_data + size()); }
    auto cend() const { return iterator(_data + size()); }
    auto rend() {return reverse_iterator(begin()); }
    bool operator==(const var &r) {
        auto first1 = cbegin();
        auto last1 = cend();
        auto first2 = r.cbegin();
        auto last2 = r.cend();
        return std::equal(first1, last1, first2, last2);
    }
    bool operator!=(const var &r) {
        return !(*this == r);
    }
    friend inline bool operator<(const var &l, const var &r) {
        auto first1 = l.cbegin();
        auto last1 = l.cend();
        auto first2 = r.cbegin();
        auto last2 = r.cend();
        return std::lexicographical_compare(first1, last1, first2, last2);
    }
    friend inline bool operator>(const var &lhs, const var &rhs) { return rhs < lhs; }
    friend inline bool operator<=(const var &lhs, const var &rhs) { return !(lhs > rhs); }
    friend inline bool operator>=(const var &lhs, const var &rhs) { return !(lhs < rhs); }
    friend std::ostream& operator<<(std::ostream& os, const var& obj) {
        for(size_t i=0; i < obj.size(); ++i)
            os << obj[i];
        return os;
    }
    friend std::istream& operator>>(std::istream& is, var& o) {
        size_t x = 0;
        is >> x;
        if (x) {
            var copy(x);
            for (size_t i = 0; i < copy.size(); ++i) {
                is >> copy[i];
            }
            std::swap(copy._data, o._data);
            std::swap(copy._size, o._size);
        }
        return is;
    }
    int& operator[](std::size_t idx) { return _data[idx]; }
    const int& operator[](std::size_t idx) const { return _data[idx]; }
};

int main()
{
    var a{1, 2, 3, 4 ,5};
    var b{2, 3, 4 ,5};
    
    std::cout << ((a <  b) ? "true" : "false");
    std::cout << ((a == b) ? "true" : "false");
}
