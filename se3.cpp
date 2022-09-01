#include <iostream>
#include <optional>
#include <vector>

class Deque
{
public:
    Deque() = default;
    Deque(const Deque &other) = default;
    Deque(const std::initializer_list<int> obj)
    {
        list = obj;
    }

    friend std::ostream &operator<<(std::ostream &os, const Deque &obj)
    {
        for (unsigned int i = 0; i < obj.list.size(); ++i)
        {
            os << &(obj.list[i]) << "->" << obj.list[i] << " ";
        }
        return os;
    }

    // a + b -> +(a, b) ; this + b -> +(this, b) -> this.+(b)
    Deque &
    operator+(const int val)
    {
        list.push_back(val);
        return *this;
    }

    // a + b -> +(a, b) ; a + obj -> +(a, obj)
    friend Deque &
    operator+(const int val, Deque &obj)
    {
        obj.list.resize(obj.list.size() + 1);
        for (std::size_t i = obj.list.size() - 1; i > 0; --i)
        {
            obj.list[i] = obj.list[i - 1];
        }
        obj.list[0] = val;
        return obj;
    }

    std::optional<int> operator[](const unsigned int idx)
    {
        if (!list.size())
            return {};
        if (idx >= list.size())
            return list[list.size() - 1];
        return list[idx];
    }

private:
    std::vector<int> list;
};

int main(int argc, char const *argv[])
{
    Deque a = {1, 2, 3, 4, 5};

    std::cout << a << "\n";

    a + 10;

    20 + a;

    std::cout << a << "\n";

    Deque b;

    auto r = a[10];
    if (r.has_value())
        std::cout << r.value();

    return 0;
}
