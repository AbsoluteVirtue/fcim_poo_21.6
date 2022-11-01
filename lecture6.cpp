#include <iostream>
#include <functional>

/*
// Как это выглядело бы в С

struct pair
{
    int car;
    struct pair (*cdr)();
};

struct pair ones()
{
    struct pair r = {1, ones};
    return r;
}

ones().car;
ones().cdr().car;

*/

struct pair
{
    int car;
    std::function<pair()> cdr;

    template <class F>
    pair(int x, F lambda) : car(x), cdr(lambda) {}
};

pair natural(int x)
{
    auto f = [=]() -> pair
    {
        return natural(x + 1);
    };
    return pair(x, f);
}

int main(int argc, char const *argv[])
{
    auto res = natural(1);
    for (int i = 1; i <= 10; res = res.cdr(), i = res.car)
    {
        std::cout << i << " ";
    }
}
