#include <iostream>
#include <string>

template <unsigned N, unsigned M>
int c_string_compare(const char (&a)[N], const char (&b)[M])
{
    return strcmp(a, b);
}

template <size_t M, size_t N, typename T>
void print(T (&matrix)[M][N])
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

template <typename _Key, typename _Value>
struct Pair
{
    _Key key;
    _Value val;

    friend std::ostream &operator<<(std::ostream &os, const Pair<_Key, _Value> &obj)
    {
        return os << obj.key << " " << obj.val;
    }
};

template <typename _K, typename _V>
class Map
{
    size_t _size = 0;
    Pair<_K, _V> *_list = NULL;

public:
    Map(std::initializer_list<Pair<_K, _V>> il)
    {
        _size = il.size();
        _list = (Pair<_K, _V> *)calloc(_size, sizeof(Pair<_K, _V>));
        std::copy(il.begin(), il.end(), _list);
    }

    ~Map()
    {
        free(_list);
    }

    const size_t size() const
    {
        return _size;
    }

    Pair<_K, _V> *begin()
    {
        return _list;
    }

    Pair<_K, _V> *end()
    {
        return (_list + _size);
    }

    void push_back(Pair<_K, _V> x)
    {
        Pair<_K, _V> *tmp = (Pair<_K, _V> *)calloc(_size + 1, sizeof(Pair<_K, _V>));
        for (size_t i = 0; i < _size; ++i)
        {
            tmp[i] = _list[i];
        }
        tmp[_size] = x;
        _size += 1;
        free(_list);
        _list = tmp;
    }
};

int main()
{
    std::cout << c_string_compare("hello", "world") << std::endl;

    Map<std::string, int> v = {
        {"goodbye", 8},
        {"alpha", 9},
        {"zulu", 0},
        {"charlie", 11},
    };

    v.push_back({"hotel", 100});

    for (auto it : v)
    {
        std::cout << it << "\t";
    }

    return 0;
}
