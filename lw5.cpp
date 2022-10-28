/*
Задание:
Используя класс container из лабораторной работы 4 создать с помощью наследования новый контейнер согласно своему варианту. Для контейнера реализовать конструктор по умолчанию, конструктор копирования, конструктор, принимающий массив, деструктор.

Дополнительно реализовать методы: begin, end, empty, size, clear, insert, erase, swap -- согласно спецификации своего варианта.

Таблица стандартных методов: https://en.cppreference.com/w/cpp/container
*/

#include <assert.h>
#include <iostream>

// ваша реализация с наследованием здесь

// typedef /* тип вашего контейнера здесь */ container; 
// например:
typedef vector<int> Container;

int main(int argc, char const *argv[])
{
    Container v({1, 2, 3, 4}), w;
    assert(!v.empty()); // !array
    assert(w.empty()); // !array

    w = v;
    assert(v.size() == w.size()); // !forward_list

    for (auto i = v.end() - 1, j = w.begin(); i != v.begin() - 1; *j++ = *i--);

    std::cout << *std::next(v.begin()) << *std::next(w.begin()); // !stack, queue
 
    v.swap(w); // !array

    v.erase(v.begin());

    w.erase(w.begin(), w.end());
    assert(w.empty());

    v.clear();
    assert(!v.size());

    v.insert(v.begin(), 23);
    w.insert(w.begin(), 23);

    std::cout << *v.begin() << *w.begin();
}
