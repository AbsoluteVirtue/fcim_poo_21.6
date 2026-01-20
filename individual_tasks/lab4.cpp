/*
    Лабораторная работа 4
    Стандартные алгоритмы С++
    Итераторы
*/

// код для проверки правильности выполнения задания:
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
// остальные необходимые библиотеки здесь

using container = /* название варианта здесь */;

int main() {
    container a({19, 47, 74, 91});
    for (auto it = a.begin(); it != a.end(); ++it) std::cout << *it << " ";

    container b(a.begin(), a.end());
    assert(a == b);
    for (auto &&it : b) std::cout << it << " ";

    container c;
    c.assign(std::distance(b.begin(), b.end()), 0);
    std::copy(b.begin(), b.end(), c.begin());
    assert(std::equal(c.begin(), c.end(), b.begin()));
    for (auto it = c.rbegin(); it != c.rend(); ++it) std::cout << *it << " ";

    container d(c.rbegin(), c.rend());
    for (auto &&it : d) std::cout << it << " ";
}
