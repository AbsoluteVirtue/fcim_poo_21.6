#include <cstddef>
#include <cstdio>

struct arraylist {
    int *data;
    size_t n{0};
    size_t capacity{0};
    // в C перегрузки функций нет, и такого эффекта надо добиваться вручную
    void (*dtor_a)(const arraylist*);
    void (*ctor_a)(const arraylist*);
    void (*ctor_b)(const arraylist*, const arraylist*);
    arraylist* (*assign)(const arraylist*, const arraylist*);
    void (*fa)(const arraylist*, int);
    void (*fb)(const arraylist*, double);
    void (*fc)(const arraylist*, int*, int*);
};

struct vector {
    int *data{nullptr};
    size_t n{0};
    size_t capacity{0};
    // в C++ для перегрузки функций создается таблица хэшированных имен функций (name mangling)
    // в таблице тело функции хранится под именем _ZN6vectorD2Ev
    ~vector();
    // в таблице тело функции хранится под именем _ZN6vectorC2Ev
    vector();
    // в таблице тело функции хранится под именем _ZN6vectorC2ERKS_
    vector(const vector&);
    // в таблице тела функции нет
    vector(vector&&) noexcept = default;
    // в таблице тело функции хранится под именем _ZN6vectoraSERKS_
    vector& operator=(const vector&);
    // в таблице тела функции нет
    vector& operator=(vector&&) noexcept = default;
    // в таблице тело функции хранится под именем _ZN6vector1fEi
    void f(int);
    // в таблице тело функции хранится под именем _ZN6vector1fEd
    void f(double);
    // в таблице тело функции хранится под именем _ZN6vector1fEPiS0_
    void f(int*, int*);
};

int main() {

}
