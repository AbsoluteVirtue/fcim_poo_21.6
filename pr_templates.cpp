#include <iostream>
#include <map>

template <typename Key, typename Value>
struct pair
{
    Key key_{};
    Value val_{};

    friend std::ostream &operator<<(std::ostream &os, const pair<Key, Value> &obj)
    {
        os << obj.key_ << ":" << obj.val_;
        return os;
    }
};

template <typename Key, typename Value>
class dict
{
    std::size_t size_{0};
    pair<Key, Value> *list_{nullptr};

public:
    ~dict()
    {
        delete[] list_;
    }
    dict() = delete;
    dict(const std::initializer_list<pair<Key, Value>> &il)
    {
        size_ = (il.size());
        list_ = new pair<Key, Value>[size_];
        std::copy(il.begin(), il.end(), list_);
    }

    friend std::ostream &operator<<(std::ostream &os, const dict<Key, Value> &obj)
    {
        for (std::size_t i = 0; i < obj.size_; ++i)
        {
            os << obj.list_[i] << " ";
        }
        return os;
    }
};

template <int rows, int cols, typename T>
void print_m(T (&matrix)[rows][cols])
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    std::multimap<std::string, std::string> m = {
        {"hello", "world"},
        {"hello", "space"},
        {"code", "1001"},
    };

    for (auto row : m)
    {
        std::cout << row.first << ":" << row.second << " ";
    }

    std::cout << "\n";

    dict<std::string, std::string> data = {
        {"code", "1001"},
        {"hello", "world"},
        {"hello", "space"},
    };

    std::cout << data;

    pair<std::string, int> matrix[2][2] = {
        {{"a", 1}, {"b", 2}},
        {{"c", 3}, {"d", 4}},
    };

    print_m(matrix);
}
