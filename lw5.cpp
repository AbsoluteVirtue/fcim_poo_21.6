/*
Задание:
Используя класс container из лабораторной работы 4 создать с помощью наследования новый контейнер согласно своему варианту. Для контейнера реализовать конструктор по умолчанию, конструктор копирования, конструктор, принимающий массив, деструктор.

Дополнительно реализовать методы: begin, end, empty, size, clear, insert, erase, swap -- согласно спецификации своего варианта.

Таблица стандартных методов: https://en.cppreference.com/w/cpp/container
*/

#include <assert.h>
#include <iostream>

// ваша реализация с наследованием здесь

// typedef /* тип вашего контейнера здесь */ container; например:
typedef vector<int> Container;

int main(int argc, char const *argv[])
{
    Container v({1, 2, 3, 4}), w;

    assert(w.empty());
    assert(!v.empty());

    w = v;
    assert(v.size() == w.size());

    for (auto i = v.end() - 1, j = w.begin(); i != v.begin() - 1; *j++ = *i--);

    auto it1 = std::next(v.begin());
    auto it2 = std::next(w.begin());
 
    int& ref1 = v.front();
    int& ref2 = w.front();
 
    v.swap(w);

    assert(std::next(w.begin()) == it1);
    assert(std::next(v.begin()) == it2);
    assert(w.front() == ref1);
    assert(v.front() == ref2);
}
