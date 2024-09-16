#include <algorithm>
#include <cstdarg>
#include <cstddef>

class vector {
private:
    int *p{nullptr};
    size_t n{0};
public:
    ~vector() {
        delete [] p;
    }

    vector() = delete;

    vector(const vector &other) : p(new int[other.n]), n(other.n) {
        std::copy(other.p, other.p + n, p);
    }

    vector(vector &&movable) : p(movable.p), n(movable.n) {
        movable.p = nullptr;
        movable.n = 0;
    }

    vector(int count, ...) : p(new int [count]), n(count) {
        // https://en.cppreference.com/w/cpp/utility/variadic
        va_list args;
        va_start(args, count);

        for (size_t i = 0; i < count; i++) {
            p[i] = va_arg(args, int);
        }
        
        va_end(args);
    }

    template <size_t count> vector(int (&a)[count]) : p(new int [count]), n(count) {
        for (size_t i = 0; i < count; i++) {
            p[i] = a[i];       
        }
    }
};

int main() {

    // типы данных и категории значений
    int x;
    x = 0; //               mov DWORD PTR [rbp-44], 0
    int y = 4; //           mov DWORD PTR [rbp-4], 4
    int *p;
    p = &x; //              lea rax, [rbp-44]
    //                      mov QWORD PTR [rbp-16], rax
    int *q = nullptr; //    mov QWORD PTR [rbp-24], 0
    int &r = x; //          lea rax, [rbp-44]
    //                      mov QWORD PTR [rbp-32], rax
    const int &t = 4; //    mov DWORD PTR [rbp-48], 4
    //                      lea rax, [rbp-48]
    //                      mov QWORD PTR [rbp-40], rax

    // конструкторы
    // vector a{};              // вызывается удаленный конструктор по умолчанию
    vector b(5, 1, 2, 3, 4, 5); // вызывается конструктор с произвольным кол-вом аргументов
    vector c(b);                // вызывается конструктор копирования
    vector d = std::move(c);    // вызывается конструктор перемещения
    int arr[] = {1, 2, 3, 4};
    vector e(arr);              // вызывается конструктор со статическим массивом в качестве аргумента
}
