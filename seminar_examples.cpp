#include <assert.h>
#include <algorithm>
#include <iostream>

typedef unsigned int uint;

#define _LAB4_

#ifdef _LAB1_
struct pod
{
    int *value;
    uint length;
};

inline void clear(pod &a)
{
    delete[] a.value;
    a.value = nullptr;
    a.length = 0;
}
inline void make_of_size(pod &a, const uint n)
{
    clear(a);
    a.value = new int[n];
    a.length = n;
}
inline void make_from_array(pod &a, const int *s, const uint n)
{
    make_of_size(a, n);
    std::copy(s, s + n, a.value);
}
void make_copy(pod &a, const pod &b)
{
    make_from_array(a, b.value, b.length);
}
bool is_equal(const pod &a, const pod &b)
{
    if (a.length != b.length)
        return false;
    for (size_t i = 0; i < a.length; i++)
    {
        if (a.value[i] != b.value[i])
            return false;
    }
    return true;
}
int at(const pod &a, const int i)
{
    return a.value[(i < 0) ? ((-i < a.length) ? a.length + i : 0) : ((i >= a.length) ? a.length - 1 : i)];
}
void print(const pod &a)
{
    for (uint i = 0; i < a.length; i++)
    {
        std::cout << a.value[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    pod a, b, c;
    int arr[] = {2, 3, 5, 7};

    make_from_array(a, arr, 4);
    make_copy(b, a);
    make_of_size(c, 4);

    print(a);
    print(b);
    print(c);
}
#endif

#ifdef _LAB2_
struct container
{
    ~container()
    {
        this->clear(*this);
    }
    container() = delete;
    container(const int *s, const uint n)
    {
        this->make_from_array(*this, s, n);
    }
    container(const uint n)
    {
        this->make_of_size(*this, n);
    }
    container(const container &b)
    {
        this->make_copy(*this, b);
    }
    static bool is_equal(container &a, container &b)
    {
        if (a.length != b.length)
            return false;
        for (size_t i = 0; i < a.length; i++)
        {
            if (a.value[i] != b.value[i])
                return false;
        }
        return true;
    }
    int at(const int idx)
    {
        return this->at(*this, idx);
    }
    void print()
    {
        this->print(*this);
    }

private:
    int *value{nullptr};
    uint length{0};

    inline static void clear(container &a)
    {
        delete[] a.value;
        a.value = nullptr;
        a.length = 0;
    }
    inline static void make_of_size(container &a, const uint n)
    {
        clear(a);
        a.value = new int[n];
        a.length = n;
    }
    inline static void make_from_array(container &a, const int *s, const uint n)
    {
        make_of_size(a, n);
        std::copy(s, s + n, a.value);
    }
    inline static void make_copy(container &a, const container &b)
    {
        make_from_array(a, b.value, b.length);
    }
    static int at(container &a, const int i)
    {
        return a.value[(i < 0) ? ((-i < a.length) ? a.length + i : 0) : ((i >= a.length) ? a.length - 1 : i)];
    }
    static void print(container &a)
    {
        for (uint i = 0; i < a.length; i++)
        {
            std::cout << a.value[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    int arr[] = {2, 3, 5, 7};
    container a(arr, 4);
    container b(a);
    container c(4);

    a.print();
    b.print();
    c.print();
}
#endif

#ifdef _LAB3_
struct container
{
    ~container()
    {
        this->clear(*this);
    }
    container() = delete;
    container(const int *s, const uint n)
    {
        this->make_from_array(*this, s, n);
    }
    container(const uint n) : value(new int[n]), length(n) {}
    container(const container &b)
    {
        *this = b;
    }
    uint size() const { return this->length; }
    container &operator=(const container &b)
    {
        this->clear(*this);
        this->make_copy(*this, b);
        return *this;
    }
    friend bool operator==(const container &a, const container &b)
    {
        return container::is_equal(a, b);
    }
    friend bool operator!=(const container &a, const container &b)
    {
        return !(a == b);
    }
    int &operator[](const int i)
    {
        return this->value[(i < 0) ? ((-i < this->length) ? this->length + i : 0) : ((i >= this->length) ? this->length - 1 : i)];
    }
    const int &operator[](const int i) const
    {
        return this->value[(i < 0) ? ((-i < this->length) ? this->length + i : 0) : ((i >= this->length) ? this->length - 1 : i)];
    }
    friend std::ostream &operator<<(std::ostream &os, const container &a)
    {
        for (uint i = 0; i < a.size(); i++)
        {
            os << a[i] << " ";
        }
        os << std::endl;
        return os;
    }

private:
    int *value{nullptr};
    uint length{0};

    inline static void clear(container &a)
    {
        delete[] a.value;
        a.value = nullptr;
        a.length = 0;
    }
    inline static void make_of_size(container &a, const uint n)
    {
        clear(a);
        a.value = new int[n];
        a.length = n;
    }
    inline static void make_from_array(container &a, const int *s, const uint n)
    {
        make_of_size(a, n);
        std::copy(s, s + n, a.value);
    }
    inline static void make_copy(container &a, const container &b)
    {
        make_from_array(a, b.value, b.length);
    }
    static bool is_equal(const container &a, const container &b)
    {
        if (a.length != b.length)
            return false;
        for (size_t i = 0; i < a.length; i++)
        {
            if (a.value[i] != b.value[i])
                return false;
        }
        return true;
    }
};

int main(int argc, char const *argv[])
{
    int arr[] = {2, 3, 5, 7};
    container a(arr, 4);
    container b = a;
    container c = container(4);

    std::cout << a << "\n"
              << b << "\n"
              << c;
}
#endif

#ifdef _LAB4_
template <typename T>
struct container
{
    ~container()
    {
        this->clear(*this);
    }
    container() = delete;
    template <uint n>
    container(const T (&s)[n])
    {
        this->make_from_array(*this, s, n);
    }
    container(const uint n) : value(new T[n]), length(n) {}
    container(const container &b)
    {
        *this = b;
    }
    uint size() const { return this->length; }
    container &operator=(const container &b)
    {
        this->clear(*this);
        this->make_copy(*this, b);
        return *this;
    }
    friend bool operator==(const container &a, const container &b)
    {
        return container::is_equal(a, b);
    }
    friend bool operator!=(const container &a, const container &b)
    {
        return !(a == b);
    }
    T &operator[](const int i)
    {
        return this->value[(i < 0) ? ((-i < this->length) ? this->length + i : 0) : ((i >= this->length) ? this->length - 1 : i)];
    }
    const T &operator[](const int i) const
    {
        return this->value[(i < 0) ? ((-i < this->length) ? this->length + i : 0) : ((i >= this->length) ? this->length - 1 : i)];
    }
    friend std::ostream &operator<<(std::ostream &os, const container &a)
    {
        for (uint i = 0; i < a.size(); i++)
        {
            os << a[i] << " ";
        }
        os << std::endl;
        return os;
    }
    T *begin() { return value; }
    T *end() { return value + length; }

private:
    T *value{nullptr};
    uint length{0};

    inline static void clear(container &a)
    {
        delete[] a.value;
        a.value = nullptr;
        a.length = 0;
    }
    inline static void make_of_size(container &a, const uint n)
    {
        clear(a);
        a.value = new T[n];
        a.length = n;
    }
    inline static void make_from_array(container &a, const T *s, const uint n)
    {
        make_of_size(a, n);
        std::copy(s, s + n, a.value);
    }
    inline static void make_copy(container &a, const container &b)
    {
        make_from_array(a, b.value, b.length);
    }
    static bool is_equal(const container &a, const container &b)
    {
        if (a.length != b.length)
            return false;
        for (size_t i = 0; i < a.length; i++)
        {
            if (a.value[i] != b.value[i])
                return false;
        }
        return true;
    }
};

template <template <typename> typename Container, typename T>
void print(Container<T> &a)
{
    for (auto it : a)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    container<int> a({2, 3, 5, 7});
    container<char> b({112, 113, 115, 117});
    container<std::string> c({"hello", "world"});

    print(a);
    print(b);
    print(c);
}
#endif
