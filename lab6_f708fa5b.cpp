/* 
Лабораторная работа 6 - Шаблоны типов

Используя код из предыдущей лабораторной работы необходимо создать шаблонный тип данных.

Метод begin возвращает итератор на первый элемент коллекции. Метод end возвращает итератор на несуществующий элемент коллекции, адрес которого совпадает с байтом, идущим непосредственно за последним элементом коллекции.

Метод rbegin возвращает итератор на последний элемент коллекции. Метод rend возвращает итератор на несуществующий элемент коллекции, адрес которого совпадает с байтом, идущим непосредственно перед первым элементом коллекции.

Метод find принимает аргумент заданного в шаблоне типа, соответствующий типу данных хранящихся в контейнере элементов, и возвращает итератор на элемент контейнера, значение которого равно значению аргумента.

Метод insert имеет два параметра: итератор, указывающий на существующий в коллекции элемент, и ссылку на значение заданного для коллекции типа. Метод возвращает итератор на новый элемент коллекции. Метод сохраняет элементы, которые уже существуют в коллекции на момент вызова, сдвигая их на один вправо относительно значения первого аргумента. Если новый размер превышает выделенный до сих пор под коллекцию объем памяти, метод вызывает выделение нового блока памяти. При этом все ссылки и итераторы, существующие в программе, которые указывают на элементы, идущие за значением первого аргумента, становятся недействительными Асимптотичность метода линейная относительно длины оставшейся за индексом части коллекции – O(n).

Метод erase принимает один аргумент – итератор, обозначающий желаемую позицию элемента на удаление. Метод возвращает итератор на элемент, следующий за удаленным. Метод сохраняет элементы, которые уже существуют в коллекции на момент вызова, сдвигая их на один влево относительно pos. При этом все ссылки и итераторы, существующие в программе, которые указывают на элементы, идущие за pos, становятся недействительными Асимптотичность метода линейная относительно длины оставшейся за индексом части коллекции – O(n).
*/

#include <cassert>
#include <iostream>
#include <string>
// остальные необходимые библиотеки здесь

template <typename T>
class iterator {
public:
    // методы из предыдущей лабораторной работы здесь
private:
    // необходимые поля с данными здесь
};

template <typename T>
class abstract_data_t {
public:
    // методы из предыдущей лабораторной работы здесь

    // рекомендуемые прототипы функций:
    virtual iterator<T> begin() = 0;
    virtual iterator<T> end() = 0;
    virtual iterator<T> rbegin() = 0;
    virtual iterator<T> rend() = 0;
    virtual iterator<T> find(const T&) = 0;
    virtual iterator<T> insert(iterator<T>, const T&) = 0;
    virtual iterator<T> erase(iterator<T>) = 0;
    virtual void assign(std::initializer_list<T> &) = 0;
    static size_t erase(abstract_data_t<T>&, const T&);
};

template <typename T> 
inline abstract_data_t<T>::~abstract_data_t() {}

template <typename T, typename Iter = iterator<T>>
class YOUR_VARIANT : public abstract_data_t<T> {
public:
    // методы из предыдущей лабораторной работы, переопределение всех нужных методов здесь

    // рекомендуемые прототипы функций:
    Iter begin() override;
    Iter end() override;
    Iter rbegin() override;
    Iter rend() override;
    Iter find(const T&) override;
    Iter insert(Iter, const T&) override;
    Iter erase(Iter) override;
    void assign(std::initializer_list<T> &) override;
    static size_t erase(abstract_data_t<T>&, const T&);
private:
    // необходимые поля здесь
};

// код для проверки правильности выполнения задания:
int main(int argc, char const *argv[]) {
    YOUR_VARIANT<int> a({2, 3, 5, 7});
    a.push(11);
    assert(11 == a[a.length() - 1]);
    a.insert(a.begin(), 1);
    assert(1 == a[0]);
    a.extend(YOUR_VARIANT<int>({13, 17, 19}));
    a.erase(a.rbegin());
    assert(a.find(19) == a.end());
    assert(8 == a.length());
    std::cout << a;
    YOUR_VARIANT<char> b = "abra";
    assert(0 == b.back());
    b.erase(b.rbegin());
    b.push('c');
    assert('c' == *b.rbegin());
    b.insert(b.end(), 'a');
    assert('a' == b.rbegin());
    b.extend(YOUR_VARIANT<char>("dabra"));
    assert(b.rbegin() == b.find(0));
    b[0] = 'A';
    assert('A' == b.front());
    std::cout << b;
    YOUR_VARIANT<std::string> c({"Hello", "world"});
    c[0].append(",");
    c.insert(c.find("world"), " ");
    c[c.length()].append("!");
    std::cout << c;
}
