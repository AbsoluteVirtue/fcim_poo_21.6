#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>

// https://en.cppreference.com/w/cpp/language/operators

class var {
    int data[100]{0};
public:
    size_t size() const { return 100; }
    // присваивание
    // копированием:
    var &operator =(const var& other) {
        std::copy(other.data, other.data + size(), data);
        return *this;
    }
    // переносом:
    var &operator =(var&& movable) noexcept {
        std::swap(data, movable.data);
        return *this;   
    }
    // или универсальный copy-and-swap:
    var &operator=(var other) noexcept {
        std::swap(data, other.data);
        return *this;
    } 

    // сравнение

    friend bool operator ==(const var &a, const var &b) {
        return std::equal(a.data, a.data + a.size(), b.data);
    }
    friend bool operator !=(const var &a, const var &b) {
        return !(a == b);
    }
    friend bool operator <(const var &a, const var &b) {
        return std::lexicographical_compare(a.data, a.data + a.size(), b.data, b.data + b.size());
    }
    friend bool operator >(const var &a, const var &b) {
        return b < a;
    }
    friend bool operator <=(const var &a, const var &b) {
        return !(a > b);
    }
    friend bool operator >=(const var &a, const var &b) {
        return !(a < b);
    }

    // доступ к элементу массива
    // по ссылке для записи:
    int &operator [](size_t i) {
        return data[i];
    }
    // по значению для чтения:
    int operator [](size_t i) const {
        return data[i];
    }
    // или универсальный шаблон (C++23):
    decltype(auto) operator [](this auto& self, size_t i) {
        return self.data[i]; 
    }
    /*
        Код выше генерирует шаблон:

    template<class type_parameter_0_0>
    inline decltype(auto) operator[](type_parameter_0_0 & self, size_t i)
    {
        return self.data[i];
    }

        Вызов std::cout.operator<<(v.operator[](10)) инициализирует шаблон:

    template<> inline int & operator[]<var>(var & self, size_t i) {
        return self.data[i];
    }
    */

   // манипуляция потоков данных
   // ввод:
    friend std::istream &operator >>(std::istream &is, var &a) {
        for (size_t i = 0; i < a.size(); i++) {
            is >> a[i];
        }
        return is;
    }
    // вывод:
    friend std::ostream &operator <<(std::ostream &os, const var &a) {
        for (size_t i = 0; i < a.size(); i++) {
            os << a[i] << " ";
        }
        return os;
    }
};

int main()
{

}
