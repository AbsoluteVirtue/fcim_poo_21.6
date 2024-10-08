#include <cassert>
#include <iostream>
#include <iterator>

class vector
{
    int *data{nullptr};
    size_t n{0};
public:
    typedef int                             value_type;
    typedef value_type *                    pointer;
    typedef value_type &                    reference;
    typedef size_t                          size_type;
    typedef ptrdiff_t                       difference_type;
    typedef pointer                         iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
/*
    // https://en.cppreference.com/w/cpp/iterator
    Для других вариантов итератор может понадобиться делать самостоятельно, так как для списков и деревьев, например, не определены нужные операции, которые для обычных указателей предоставлены по умолчанию:

        class iterator
        {
            int *p{nullptr};
        public:
            // категорию необходимо указывать для стандартных алгоритмов, которые ее проверяют
            typedef std::forward_iterator_tag iterator_category;

            iterator(int *x) : p(x) {}

            int& operator*();
            iterator& operator++();
            iterator operator++(int);
            iterator& operator--();
            iterator operator--(int);
            iterator& operator+=(ptrdiff_t n);
            iterator& operator-=(ptrdiff_t n);
            friend iterator operator+(iterator it, ptrdiff_t n);
            friend iterator operator-(iterator it, ptrdiff_t n);
            bool operator==(const iterator&);
            bool operator!=(const iterator&);
        };
*/
    vector(const std::initializer_list<value_type> &l) : data(new value_type[l.size()]), n(l.size())
    {
        std::copy(l.begin(), l.end(), data);
    }
    // [a, b)
    template <typename Iter>
    vector(Iter a, Iter b)
    {
        n = b - a;
        data = new value_type[n];
        std::copy(a, b, data);
    }
    size_type size() const { return n; }
    reference operator[](size_type i) noexcept { return data[i]; }
    auto begin() { return iterator(data); }
    auto end() { return iterator(data + n); }
    auto rbegin() { return reverse_iterator(end()); }
    auto rend() { return reverse_iterator(begin()); }
};

int main() {
    vector v{1, 2, 3, 4, 5};
    for (vector::size_type i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    vector w{v.begin(), v.end()};
    assert(std::equal(v.begin(), v.end(), w.begin(), w.end()));
    for (auto it = w.begin(); it != w.end(); it++) {
        std::cout << *it << " ";
    }
    vector z{w.rbegin(), w.rend()};
    for (auto &&it : z) {
        std::cout << it << " ";
    }
}
