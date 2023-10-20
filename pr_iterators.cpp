#include <cstddef>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <utility>

using std::cout;

// https://internalpointers.com/post/writing-custom-iterators-modern-cpp

#ifdef test
#include <vector>

using std::vector;

int main(int argc, char const *argv[]) {

    vector a = {19, 47, 74, 91};
    for (auto it = a.begin(); it != a.end(); ++it) cout << *it << " ";

    vector b(a.begin(), a.end());
    for (auto &&it : b) cout << it << " ";

    vector c(b.begin(), b.end());
    for (auto it = c.rbegin(); it != c.rend(); ++it) cout << *it << " ";

    vector d(c.rbegin(), c.rend());
    for (auto &&it : d) cout << it << " ";
}
#endif

struct iter {
    using value_type = int;
    using pointer = value_type*;
    using reference = value_type&;

    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    
    pointer p{nullptr};

    iter(pointer q) : p(q) {}

    difference_type operator-(const iter &other) const {
        return (p - other.p);
    }
    bool operator==(const iter &other) const {
        return p == other.p;
    }
    bool operator!=(const iter &other) const {
        return !(*this == other);
    }
    reference operator*() {
        return *p;
    }
    iter& operator++() {
        ++p;
        return *this;
    }
    iter operator++(int) {
        auto tmp(*this);
        ++(*this);
        return tmp;
    }
    iter& operator--() {
        --p;
        return *this;
    }
    iter operator--(int) {
        auto tmp(*this);
        --(*this);
        return tmp;
    }
};

struct vec {
    using value_type = int;
    using pointer = value_type*;
    using reference = value_type&;

    pointer p{nullptr};
    pointer q{nullptr};

    vec() = default;
    vec(const std::initializer_list<value_type> &il) : p(new int[il.size()]), q(p + il.size()) {
        std::copy(il.begin(), il.end(), p);
    }
    vec(const iter &b, const iter &e) : p(new int[(e - b)]), q(p + (e - b)) {
        std::copy(b, e, p);
    }

    auto begin() { return iter(p); }
    auto end() { return iter(q); }
    auto rbegin() { return std::reverse_iterator<iter>(q); }
    auto rend() { return std::reverse_iterator<iter>(p); }
};

int main(int argc, char const *argv[]) {

    vec b({1, 2, 3, 4});
    for (auto &&it : b) cout << it << " ";

    vec c(b.begin(), b.end());
    for (auto it = c.rbegin(); it != c.rend(); ++it) cout << *it << " ";
}
