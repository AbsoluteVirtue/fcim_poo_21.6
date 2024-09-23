// https://cppinsights.io/

#include <cstdio>
#include <iostream>
#include <cstdarg>

#ifdef LOOP_GEN
int main() {
    const char arr[10]{2, 4, 6, 8};
    for(const char& c : arr) {
        printf("c=%c\n", c);
    }
/*
// данный цикл будет изменен для компиляции в такую форму:

    const char (&__range1)[10] = arr;
    const char * __begin1 = __range1;
    const char * __end1 = __range1 + 10L;
    for(; __begin1 != __end1; ++__begin1) {
        const char & c = *__begin1;
        printf("c=%c\n", 
            static_cast<int>(c));
    }
*/
}
#endif

#ifdef VAR_ARG
// Variadic function: функция с переменным количеством аргументов
template <typename T>
void print(T t) {
	std::cout << t << " ";
}
/*
// инстанциирование шаблона с аргументом int для вызова print(1, *, *) сгенерирует данную версию:
template<>
void print<int>(int t)
{
    std::operator<<(std::cout.operator<<(t), " ");
}
*/

template <typename T, typename... Args>
void print(T t, Args... args) {
	std::cout << t << " ";
	print(args...);
}
/*
// инстанциирование шаблона с аргументами int и int для вызова print(*, 2, 3) сгенерирует данную версию:
template<>
void print<int, int>(int t, int __args1)
{
  std::operator<<(std::cout.operator<<(t), " ");
  print(__args1);
}
// инстанциирование шаблона с аргументами int и int для вызова print(1, 2, 3) сгенерирует данную версию:
template<>
void print<int, int, int>(int t, int __args1, int __args2)
{
    std::operator<<(std::cout.operator<<(t), " ");
    print(__args1, __args2);
}
*/
int main() {
    print(1, 2, 3);
}
#endif

#ifdef MANGLE
struct var {
    int x{0};
    var() = default;
    var(int i) : x(i) {}
    var(double d) : x(static_cast<int>(d)) {}
};

int main() {
    var a{1};
    var b{.1};
    var c{};
/*
// Итоговая сборка будет выполняться на основании сгенерированного кода:
    lea     rdi, [rbp - 4]
    mov     esi, 1
    call    _ZN3varC2Ei
    lea     rdi, [rbp - 8]
    movsd   xmm0, qword ptr [rip + .LCPI0_0]
    call    _ZN3varC2Ed
    lea     rdi, [rbp - 12]
    xor     esi, esi
    mov     edx, 4
    call    memset@PLT
    lea     rdi, [rbp - 12]
    call    _ZN3varC2Ev
// Для конструкторов генерируются уникальные названия процедур, для конструктора по умолчанию код не генерируется
*/
}
#endif

class var {
private:
    int x{0};
public:
    var() = default;
    var(int i) : x{i} {}

    void swap(var &other) {
        int t = x;
        x = other.x;
        other.x = t;
    }
    friend void swap(var &a, var &b) {
        a.swap(b);
    }
    friend std::ostream &operator<<(std::ostream &os, var a) {
        os << a.x;
        return os;
    }
    var operator+(var other) {
        return this->x + other.x;
    }
    void * operator new(size_t n) {
        std::printf("2) new(size_t), size = %zu\n", n);
        void *p = std::malloc(n);
        if (!p) throw std::bad_alloc{};
        return p;
    }
};

using std::swap;

int main() {
    var a;
    var b{1};

    a.swap(b);    // this->swap
    swap(a, b);   // friend swap
    ::swap(a, b); // std::swap

    std::cout << a + b; // friend operator << this->operator +

    var *p = new var{2}; // this->operator new
    std::cout << *p;
}
