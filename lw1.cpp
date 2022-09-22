/*
Задание:
Для заданной структуры pod, которая содержит объект, по поведению схожий с динамическим массивом/списком элементов типа int, 
реализовать заданные функции:

make_empty -- инициализирует поля переменной типа pod подходящими значениями по умолчанию;
make_copy -- создает копию переменной типа pod в другой переменной;
make_from_array -- инициализирует поля переменной типа pod значениями из переданного массива;
make_of_size -- инициализирует переменную типа pod соответствующего размера;
clear -- освобождает память, занятую переменной типа pod, если в этом есть необходимость;
at -- возвращает элемент, принадлежащий переменной типа pod, находящийся по заданному индексу, принимает как положительные, так и отрицательные индексы, в случае превышения длины массива индексом возвращает элемент с соответствующего конца;
is_equal -- сравнивает две переменные типа pod поэлементно, возвращает true, если они равны, или false в противном случае.
*/

#include <assert.h>

struct pod
{
    int *value;
    unsigned int length;
};

void make_copy(pod &, const pod &);
void make_from_array(pod &, const int *, const unsigned int);
void make_of_size(pod &, const unsigned int);
void make_empty(pod &);
void clear(pod &);
int at(const pod &, const int);
bool is_equal(const pod &, const pod &);

int main(int argc, char const *argv[])
{
    int array[] = {1, 4, 7, 9};

    pod a;
    make_empty(a);
    make_from_array(a, array, 4);

    assert(9 == at(a, 3));
    assert(9 == at(a, -1));
    assert(9 == at(a, 13));
    assert(1 == at(a, -13));

    pod b;
    make_empty(b);
    make_copy(b, a);

    assert(1 == *(b.value));
    assert(9 == *(b.value + b.length - 1));

    assert(is_equal(a, b));

    clear(a);
    clear(b);
}
