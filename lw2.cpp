/*
Задание:
Написать новую структуру container на базе структуры pod. 
Внутри структуры container нужно реализовать заданные функции:

size -- возвращает текущее количество элементов внутреннего массива;
front -- возвращает значение первого элемента внутреннего массива;
back -- возвращает значение последнего элемента внутреннего массива;
insert -- добавляет новый элемент в заданное место во внутреннем массиве;
append -- добавляет новый элемент в конец внутреннего массива;
extend -- расширяет внутренний массив всеми элементами массива-аргумента;
pop -- удаляет элемент из внутреннего массива по заданному индексу, возвращает значение удаленного элемента;
remove -- удаляет первый заданный элемент из внутреннего массива;
index -- возвращает индекс первого элемента, значение которого совпадает со значением аргумента;
count -- возвращает количество элементов, значение которых совпадает со значением аргумента.

Функции структуры pod сделать методами структуры container и поправить их код согласно требованиям С++. 
Соответствующие функции переписать как конструкторы:

конструктор по умолчанию -- инициализирует поля переменной типа container подходящими значениями по умолчанию;
конструктор копирования -- создает копию переменной типа container в другой переменной такого же типа, инициализируя поля переменной типа container значениями из аналогичных полей аргумента;
конструктор приведения int* -> container -- инициализирует поля переменной типа container значениями из переданного массива;
конструктор приведения int -> container -- инициализирует поля переменной типа container как массив соответствующего размера;
деструктор -- освобождает память, занятую переменной типа container, если в этом есть необходимость.
*/

#include <assert.h>
#include <iostream>

struct container
{
    unsigned int size() const;
    int front() const;
    int back() const;
    void insert(const unsigned int idx, const int x);
    void append(const int x);
    void extend(const container &other);
    int pop(const unsigned int idx);
    void remove(const int x);
    unsigned int index(const int x) const;
    unsigned int count(const int x) const;
    static bool is_equal(const container &dest, const container &other);
    int at(const int idx) const;
    ~container();
    container();
    container(const container &other);
    container(const unsigned int n);
    container(const int *x, const unsigned int n);
private:
    int *value{nullptr};
    unsigned int length{0};
};

int main(int argc, char const *argv[])
{
    int array[] = {1, 4, 7, 9};

    container a(array, 4);

    container b(a);
    a.append(10);
    assert(1 == a.front());
    assert(10 == a.back());
    assert(10 == a.at(10));

    b.insert(0, 10);
    assert(10 == b.front());
    assert(1 == b.at(1));
    assert(9 == b.back());

    container c;
    c.extend(b);
    assert(container::is_equal(c, b));
    assert(0 == c.index(10));

    a.extend(c);
    assert(2 == a.count(10));
    assert(9 == a.pop(20));
    assert(1 == a.pop(0));
    assert(7 == a.back());

    a.remove(4);
    assert(7 == a.at(1));
    assert(7 == a.at(-1));
    assert(8 == a.size());

    for (unsigned int i = 0; i < a.size(); i++)
    {
        std::cout << a.at(i) << " ";
    }
}
