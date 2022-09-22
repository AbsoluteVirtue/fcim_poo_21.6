/*
Задание:
Расширить структуру container, сделанную в предыдущей работе. 
Внутри структуры container нужно дополнительно реализовать заданные функции:

norm - возвращает сумму элементов массива.

Функции структуры container перегрузить следующие операторы:

operator== -- оператор сравнения, равенство, возвращает true, если массивы двух объектов равны, в остальных случаях возвращает false (два массива равны, если все их элементы одинаковы);
operator!= -- оператор сравнения, неравенство, логика обратна предыдущему оператору;
operator< -- оператор сравнения, строго меньше, возвращает true, если сумма элементов массива объекта слева меньше суммы элементов массива объекта справа;
operator<= -- оператор сравнения, меньше либо равно, обратная операция оператора "строго больше";
operator>= -- оператор сравнения, больше либо равно, обратная операция оператора "строго меньше";
operator> -- оператор сравнения, строго больше, возвращает true, если сумма элементов массива объекта слева больше суммы элементов массива объекта справа;
operator<< -- оператор вывода, выводит элементы массива через пробел в переданный поток вывода;
operator>> -- оператор ввода, инициализирует элементы массива значениями из переданного потока ввода, предполагает, что в массиве достаточно памяти для всех элементов ввода;
operator[] -- оператор доступа по индексу, возвращает копию элемента массива или ссылку на элемент массива по заданному индексу, работает и для отрицательных значений индекса;
operator= -- оператор присваивания, заменяет значения в объекте слева на значения из объекта справа.
*/

#include <assert.h>
#include <iostream>
#include <sstream>


struct container
{
    unsigned int size() const;
    int front() const;
    int back() const;
    int norm() const;
    friend bool operator==(const container &lhs, const container &rhs);
    friend bool operator!=(const container &lhs, const container &rhs);
    friend bool operator<(const container &lhs, const container &rhs);
    friend bool operator>(const container &lhs, const container &rhs);
    friend bool operator<=(const container &lhs, const container &rhs);
    friend bool operator>=(const container &lhs, const container &rhs);
    friend std::ostream &operator<<(std::ostream &os, const container &object);
    friend std::istream &operator>>(std::istream &is, container &object);
    void insert(const unsigned int idx, const int x);
    void append(const int x);
    void extend(const container &other);
    int pop(const unsigned int idx);
    void remove(const int x);
    unsigned int index(const int x) const;
    unsigned int count(const int x) const;
    int &operator[](const unsigned int idx);
    const int operator[](const unsigned int idx) const;
    container &operator=(const container &other);
    container(const container &other);
    container(const int *x, const unsigned int n);
    container(const unsigned int n);
    container();
    ~container();
private:
    int *value{nullptr};
    unsigned int length{0};
};

int main(int argc, char const *argv[])
{
    std::stringstream ss{"1 3 5 7 9"};

    container a(5);
    ss >> a;
    assert(5 == a.size());
    assert(1 == a[0]);
    assert(9 == a[4]);

    container b{a};
    assert(a == b);
    assert(3 == b[1]);
    assert(7 == b[3]);

    b[4] = 0;
    assert(0 == b[10]);
    assert(b < a);

    container c;
    c = b;
    assert(b == c);
    assert(1 == c[0]);
    assert(0 == c[-1]);

    std::cout << c;
}
