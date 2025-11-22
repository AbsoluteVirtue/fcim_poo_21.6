/*
    Лабораторная работа 5
    Обобщенное программирование, шаблоны функций и типов, статический полиморфизм
*/

// код для проверки правильности выполнения задания:
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
// остальные необходимые библиотеки здесь

using container = /* название варианта здесь */;

int main() {
    container<int> a({2, 3, 5, 7});
    a.push(11);
    assert(11 == a[a.size() - 1]);
    a.insert(a.begin(), 1);
    assert(1 == a[0]);
    a.extend(container<int>({13, 17, 19}));
    a.erase(a.rbegin());
    assert(a.find(19) == a.end());
    assert(8 == a.size());
    container<char> b = "abra";
    assert(0 == b.back());
    b.erase(b.rbegin());
    b.push('c');
    assert('c' == *b.rbegin());
    b.insert(b.end(), 'a');
    assert('a' == *b.rbegin());
    b.extend(container<char>("dabra"));
    assert(b.rbegin() == b.find(0));
    b[0] = 'A';
    assert('A' == b.front());
    container<std::string> c({"Hello", "world"});
    c[0].append(",");
    c.insert(c.find("world"), " ");
    c[c.size() - 1].append("!");
}
