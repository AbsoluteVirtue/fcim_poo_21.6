// код для проверки правильности выполнения задания:
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
// остальные необходимые библиотеки здесь

using container = /* название варианта здесь */;

int main() {
    // инициализация контейнера списком значений:
    container a({1, 4, 7, 9});
    // или с помощью С-массива с явно переданным размером:
    // int array[] = {1, 4, 7, 9};
    // container a(array, 4);

    assert(4 == a.size());
    assert(1 == a.at(0));
    assert(9 == a.at(10));
    // инициализация контейнера другим контейнером:
    container b(a);

    assert(container::is_equal(a, b));
    b.clear();
    assert(b.empty());
    // инициализация пустого контейнера:
    container c;

    assert(c.empty());
    c.assign(3, 7);
    assert(3 == c.size());
    // инициализация контейнера целым числом
    container d(5);

    assert(5 == d.size());
    d.resize(10);
    b.swap(d);
    assert(10 == b.size());
    assert(d.empty());
    // инициализация контейнера анонимным объектом:
    container e = std::move(b);

    assert(10 == e.size());
    assert(b.empty());
}
