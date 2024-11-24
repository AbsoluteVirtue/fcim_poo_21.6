#include <iostream>

void pointer_arg(int *p) {
    std::cout << *p << "\n";
}

void lvalue_ref_arg(int &r) {
    std::cout << &r << " " << r << "\n";
}

void rvalue_ref_arg(int &&rr) {
    std::cout << rr << "\n";
}

void const_lvalue_ref_arg(const int &cr) {
    std::cout << cr << "\n";
}

///

class vector
{
private:
    int *p{0};
    size_t n{0};
    size_t cap{0};
public:
    size_t size() {
        return n;
    }
    int at(size_t i) {
        return p[i];
    }
    ~vector() {
        delete [] p;
    }
    vector() = default;
    vector(size_t number) 
        :   p(new int [number]{0}), 
            n(number),
            cap(number)
    {
    }
    vector(const std::initializer_list<int> &il) {
        size_t number = il.size();
        p = new int [number];
        n = number;
        cap = number;
        /*
        Для того, чтобы скопировать элементы из списка в массив,
        можно использовать цикл так:

            auto start = il.begin();
            for (size_t i = 0; i < number; i++)
            {
                p[i] = *(start + i);
            }

        или так:
        */
        std::copy(il.begin(), il.end(), p);      
    }
    // Начало массива для циклов for-each
    int *begin() {
        return p;
    }
    // Конец массива для циклов for-each
    int *end() {
        return p + n;
    }
};

int main()
{
    int x = 1;

    pointer_arg(&x);
    // аналогично указателю, ссылка копирует адрес объекта как аргумент:
    lvalue_ref_arg(x);
    // ссылка типа && не принимает объекты в качестве значений:
    // rvalue_ref_arg(x); // ошибка
    // но объекты можно привести к нужному типу ссылки так:
    rvalue_ref_arg(static_cast<int&&>(x));
    // или так:
    rvalue_ref_arg(std::move(x));
    // анонимные значения можно передавать и как ссылки типа &&:
    rvalue_ref_arg(42);
    // и как константные ссылки типа &:
    const_lvalue_ref_arg(42);
    // все объекты можно передавать как константные ссылки:
    const_lvalue_ref_arg(x);

    ///

    auto a = vector({1, 2, 3, 4});

    for (auto && it : a)
    {
        std::cout << it << " ";
    }
    
    for (size_t i = 0; i < a.size(); i++)
    {
        std::cout << a.at(i);
    }
}
