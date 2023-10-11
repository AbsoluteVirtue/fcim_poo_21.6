/*
Лабораторная работа 3 - Итераторы

Взяв за основу предыдущую лабораторную с помощью класса необходимо реализовать для своего варианта класс-итератор, который скрывает внутренние поля с данными. Соответственно, для инициализации внутренних полей необходимо добавить в класс все нужные конструкторы и деструктор. Ниже показаны примеры прототипов, из которых складывается интерфейс итератора и абстрактного типа данных.

Итератор должен скрывать работу с указателями внутри контейнера. Таким образом, в случаях, когда метод класса abstract_data_t должен вернуть указатель, он возвращает копию итератора.

Для класса abstract_data_t:

Статический метод is_equal имеет два параметра – два объекта заданного класса, которые необходимо сравнить. Метод возвращает “истинность”, если аргументы равны, и “ложь” в противном случае. Объекты считаются равными, если равны их контейнеры. Контейнеры равны, если они содержат равное количество элементов, а также – если значение каждого элемента одного контейнера равно элементу другого контейнера на том же месте.

Метод assign принимает два итератора на последовательный отрезок памяти заданного типа и заменяет значения в текущем контейнере на значения из заданного отрезка.

Метод begin возвращает итератор на первый элемент контейнера.

Метод end возвращает итератор на первый элемент справа за пределами контейнера, если это контейнер из одного блока памяти. Для контейнеров с другой структурой возвращает такое значение, которое обозначает необходимость прервать итерацию, идущую слева-направо.

Метод rbegin возвращает итератор на последний элемент контейнера.

Метод rend возвращает итератор на первый элемент слева за пределами контейнера, если это контейнер из одного блока памяти. Для контейнеров с другой структурой возвращает такое значение, которое обозначает необходимость прервать итерацию, идущую справа-налево.
*/

#include <cassert>
#include <iostream>
// остальные необходимые библиотеки здесь

class iterator {
public:
    // рекомендуемые прототипы функций:
    ~iterator();
    iterator();
    iterator(const iterator &);
    iterator(int *);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    int& operator*();
    int* operator->();
    friend bool operator==(const iterator &, const iterator &);
    friend bool operator!=(const iterator &, const iterator &);
private:
    // необходимые поля с данными здесь
};

class riterator {
public:
    // рекомендуемые прототипы функций:
    ~riterator();
    riterator();
    riterator(const riterator &);
    riterator(int *);
    riterator &operator++();
    riterator operator++(int);
    riterator &operator--();
    riterator operator--(int);
    int& operator*();
    int* operator->();
    friend bool operator==(const riterator &, const riterator &);
    friend bool operator!=(const riterator &, const riterator &);
private:
    // необходимые поля с данными здесь
};

class abstract_data_t {
public:
    // методы из предыдущей лабораторной работы здесь

    // рекомендуемые прототипы функций:
    abstract_data_t(iterator, iterator);
    iterator begin();
    iterator end();
    riterator rbegin();
    riterator rend();
    static bool is_equal(const abstract_data_t&, const abstract_data_t&);
    void assign(iterator, iterator);
private:
    // необходимые поля с данными здесь
};

int main(int argc, char const *argv[])
{
    int array[] = {19, 47, 74, 91};

    abstract_data_t a(array, 4);
    for (auto it = a.begin(); it != a.end(); ++it) std::cout << *it << " ";

    abstract_data_t b(a.begin(), a.end());
    assert(abstract_data_t::is_equal(a, b));
    for (auto &&it : b) std::cout << it << " ";

    abstract_data_t c(b.begin(), b.end());
    for (auto it = c.rbegin(); it != c.rend(); ++it) std::cout << *it << " ";

    abstract_data_t d(c.rbegin(), c.rend());
    for (auto &&it : d) std::cout << it << " ";
}
