/*
Лабораторная работа 5 - Наследование

Взяв предыдущую лабораторную работу за основу необходимо создать иерархию наследования, где класс abstract_data_t выступает в роли интерфейса (то есть, является абстрактным базовым классом для другого класса с реализацией). В коде ниже уже присутствует чисто виртуальный метод (деструктор класса abstract_data_t), это нужно для того, чтобы класс компилятором определялся как чисто абстрактный.

Метод front возвращает значение первого элемента коллекции (не для всех вариантов).

Метод back возвращает значение последнего элемента коллекции (не для всех вариантов).

Метод push принимает один аргумент – целое число – и добавляет значение аргумента в качестве нового элемента в начало (или конец) заданной коллекции (не для всех вариантов).

Метод pop удаляет первый (или последний) элемент из заданной коллекции (не для всех вариантов).

Метод extend с одним параметром (ссылкой на другую коллекцию того же типа, что и заданная) добавляет значения аргумента в конец заданной коллекции в том же порядке, в каком они встречаются в коллекции-аргументе.
*/

#include <cassert>
#include <iostream>
// остальные необходимые библиотеки здесь

class abstract_data_t {
public:
    // методы из предыдущей лабораторной работы здесь

    // рекомендуемые прототипы функций:
    virtual ~abstract_data_t() = 0;
    virtual int &front() = 0;
    virtual int &back() = 0;
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual void extend(const abstract_data_t&) = 0;
};

inline abstract_data_t::~abstract_data_t() {}

class YOUR_VARIANT : public abstract_data_t {
public:
    // конструкторы, деструктор, переопределение всех нужных методов здесь

    // рекомендуемые прототипы функций:
    int &front() override;
    int &back() override;
    void push(int) override;
    void pop() override;
    void extend(const abstract_data_t&) override;
private:
    // необходимые поля здесь
};

// код для проверки правильности выполнения задания:
int main(int argc, char const *argv[]) {
    const int a[4] = {2, 3, 5, 7};
    abstract_data_t *v = new YOUR_VARIANT(a, 4);
    assert(!v->empty());
    v->push(11);
    assert(11 == v->back());
    assert(11 == (*v)[v->length() - 1]);
    const int b[3] = {13, 17, 19};
    v->extend(YOUR_VARIANT(b, 3));
    assert(8 == v->length());
    abstract_data_t *w = new YOUR_VARIANT();
    assert(w->empty());
    *w = *v;
    assert(*w == *v);
    (*w)[0] = 0;
    assert(0 == w->front());
    w->pop();
    assert(17 == w->back());
    assert(7 == w->length());
}
