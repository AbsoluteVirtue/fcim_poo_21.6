// код для проверки правильности выполнения задания:
#include <cassert>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <utility>
// остальные необходимые библиотеки здесь

using container = /* название варианта здесь */;

int main() {
    std::stringstream ss{"1 3 5 7 9"};
    container a(5);
    ss >> a;
    assert(5 == a.size());
    assert(1 == a[0]);
    assert(9 == a[4]);
    std::cout << a;
    container b{a};
    assert(a == b);
    assert(3 == b[1]);
    assert(7 == b[3]);
    b[4] = 0;
    assert(0 == b[4]);
    assert(!b.contains(9));
    assert(b < a);
    assert(a > b);
    std::cout << b;
    container c;
    assert(0 == c.size());
    c = b;
    assert(b == c);
    c[1] = c[2] = 7;
    assert(7 == c[1]);
    assert(7 == c[2]);
    assert(3 == c.count(7));
    std::cout << c;
    b = container({1, 3, 5, 7, 9});
    assert(5 == b.size());
    assert(1 == b[0]);
    assert(9 == b[4]);
    c = std::move(b);
    assert(9 == c[4]);
    assert(c.contains(7));
    assert(b.empty());
    assert(b < c);
}
