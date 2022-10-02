#include <algorithm>
#include <exception>
#include <iostream>
#include <optional>
#include <utility>

#define n 4

int
index_t(int a[n], const int find)
{
    for (size_t i = 0; i < n; i++)
    {
        if (find == a[i])
            return i;
    }
    throw std::out_of_range("значение не найдено");
}

std::optional<int>
index_o(int a[n], const int find)
{
    for (size_t i = 0; i < n; i++)
    {
        if (find == a[i])
            return i;
    }
    return std::nullopt;
}

std::pair<std::optional<int>, std::string>
index_p(int a[n], const int find)
{
    for (size_t i = 0; i < n; i++)
    {
        if (find == a[i])
            return {i, ""};
    }
    return {std::nullopt, "значение не найдено"};
}

int main(int argc, char const *argv[])
{
    int a[n] = {1, 2, 3, 4};

    try
    {
        int t = index_t(a, 5);
        std::cout << t;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << "\n";
    }

    auto o = index_o(a, 5);
    if (o.has_value())
        std::cout << o.value();

    auto p = index_p(a, 5);
    if (p.first.has_value())
        std::cout << p.first.value();
    else 
        std::cerr << p.second;
}
