#include <iostream>
#include <algorithm>
#include <iterator>

template <typename T> class vector
{
public:
    using value_type = T;
    using iterator = T*;
    using pointer = T*;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

private:
    size_type n{0};
    pointer data{nullptr};

public:
    // it++, it--, it1 - it2, it + n, it - n, *it 
    // class reverse_iterator {
    // public:
    //     typedef std::random_access_iterator_tag iterator_category;
    // };

    ~vector() { delete[] data; }

    template <typename RandomAccessIter>
    vector(RandomAccessIter first, RandomAccessIter last)
        : n{static_cast<size_type>(last - first)}, 
          data{new value_type[n]}
    {
        std::copy(first, last, data);
    }
    
    vector(const std::initializer_list<value_type> &il)
        : n{il.size()}, data{new value_type[n]}
    {
        std::copy(il.begin(), il.end(), data);
    }

    auto size() const { return n; }

    inline auto operator[](size_type i)
    {
        return data[i];
    }

    const auto operator[](size_type i) const
    {
        return data[i];
    }
    // [begin, end)
    auto begin()
    {
        return iterator(data);
    }
    auto end()
    {
        return iterator(data + n);
    }
    // (rend, rbegin]
    auto rbegin() {
        return &data[n];
        // return std::reverse_iterator<iterator>{end()};
    }

    auto rend() {
        // return std::reverse_iterator<iterator>{begin()};
        return &data[0];
    }
};

int main()
{
    vector<double> v{6, 5, 4, 3, 2, 1};

    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }

    vector<int> w{v.begin(), v.end()};

    std::sort(v.begin(), v.end());

    for (auto&& element : v)
    {
        std::cout << element << " ";
    }
    //             data(n - 1)       data - 1
    // for (auto it = w.rbegin(); it != w.rend(); ++it)
    // {
    //     std::cout << *it << " ";        
    // }
}
