#include <iostream>
#include <optional>
#define NDEBUG      // выключает assert
#include <assert.h> // assert
#include <error.h>  // NO_ERROR
#include <stdlib.h> // perror
#include <string.h> // strerror

int cdiv(float a, float b, float *result);
float cdiv_wa(float a, float b);
float cppdiv_wt(float a, float b);
float cppdiv_we(float a, float b);
float cppdiv_wse(float a, float b);
float cppdiv_wce(float a, float b);
std::optional<float> cppdiv_wo(float a, float b);

class zero_division_exception : public std::exception
{
    const char *msg{"zero division error"};

public:
    zero_division_exception() {}
    const char *what() const noexcept override { return msg; }
};

int main(int argc, char const *argv[])
{
    // C-стиль

    // проверка глобального статуса errno после вызова

    errno = NO_ERROR;
    FILE *fp = fopen("this_file_does_not_exist.txt", "r");
    if (!fp)
        std::cerr << strerror(errno);
    // или
    perror("\nfopen(\"this_file_does_not_exist.txt\", \"r\")");

    // проверка возвращаемого значения функции
    float div_res;
    if (cdiv(10, 0, &div_res))
        std::cerr << "cdiv(10, 0, &div_res): zero division error";

    std::cout << "\nEnter number: ";
    if (!scanf("%f", &div_res))
        std::cerr << "\nscanf(\"%f\", &div_res): stdin error";

    // проверка через assert, опция NDEBUG должна отсутствовать (компилировать без -dNDEBUG)
    cdiv_wa(10, 0);

    // C++-style

    // проверка исключений
    try
    {
        div_res = cppdiv_wt(10, 0);
    }
    catch (const char *e)
    {
        std::cerr << '\n'
                  << "cppdiv_wt(10, 0): " << e;
    }

    try
    {
        div_res = cppdiv_we(10, 0);
    }
    catch (const std::exception &e)
    {
        // сообщение об ошибке будет обобщенным, без указания причины
        std::cerr << '\n'
                  << "cppdiv_we(10, 0): " << e.what();
    }

    try
    {
        div_res = cppdiv_wse(10, 0);
    }
    // обратите внимание, что ловится объект типа std::exception
    // наследование позволяет это делать
    catch (const std::exception &e)
    {
        std::cerr << '\n'
                  << "cppdiv_wse(10, 0): " << e.what();
    }

    try
    {
        div_res = cppdiv_wce(10, 0);
    }
    // правильней ловить конкретный тип исключения
    // чтобы случайно не пропустить непредвиденную ошибку
    catch (const zero_division_exception &e)
    {
        std::cerr << '\n'
                  << "cppdiv_wce(10, 0): " << e.what();
    }

    // std::optional (доступно с версии C++17, компилировать с -std=c++17)
    std::optional<float> div_res_o = cppdiv_wo(10, 0);
    if (!div_res_o.has_value())
        std::cerr << "\ncppdiv_wo(10, 0): zero division error";
    else
        std::cout << "\nresult: " << div_res_o.value();
    return 0;
}

int cdiv(float a, float b, float *result)
{
    if (!b)
        return -1;
    *result = a / b;
    return 0;
}

float cdiv_wa(float a, float b)
{
    assert(b); // программа завершится принудительно, если b == 0
    return a / b;
}

float cppdiv_wt(float a, float b)
{
    // if (!b) throw; // без активного исключения программа завершится в любом случае
    // можно кинуть объект и ловить его тип
    if (!b)
        throw "zero division error";
    return a / b;
}

float cppdiv_we(float a, float b)
{
    if (!b)
        throw std::exception();
    return a / b;
}

float cppdiv_wse(float a, float b)
{
    // можно кинуть одно из стандартных исключений
    // std::logic_error;
    // std::domain_error;
    // std::invalid_argument;
    // std::length_error;
    // std::out_of_range;
    // std::runtime_error;
    // std::range_error;
    // std::overflow_error;
    // std::underflow_error;
    if (!b)
        throw std::overflow_error("zero division error");
    return a / b;
}

float cppdiv_wce(float a, float b)
{
    // можно кинуть исключение, сделанное специально для программы
    if (!b)
        throw zero_division_exception();
    return a / b;
}

std::optional<float> cppdiv_wo(float a, float b)
{
    if (!b)
        return std::nullopt;
    return a / b;
}
