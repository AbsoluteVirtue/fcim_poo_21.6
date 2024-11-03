/*
Лабораторная работа 1 - Абстрактные типы данных

Для своего варианта (варианты смотрите в приложении 1 методички) найти реализацию подходящего абстрактного типа данных в соответствующем файле (или файлах, как правило, интерфейс определен в файле с расширением .h, а реализация интерфейса - в файле с расширением .c) по ссылке:

    https://github.com/AbsoluteVirtue/c-algorithms-origin/tree/master/src

Для заданной реализации необходимо написать тесты: по одному-два на каждую функцию интерфейса - исходя из аргументов функции и возвращаемого значения функции.

Пример для АТД ArrayList см. ниже.
*/

#include <assert.h>
// остальные необходимые библиотеки здесь

#include "arraylist.h"
#include "arraylist.c"

void test_new(void);
void test_append(void);
void test_clear(void);
void test_free(void);
void test_index_of(void);
void test_insert(void);
void test_prepend(void);
void test_remove(void);
void test_remove_range(void);
void test_sort(void);

int main(void)
{
    test_new();
    test_append();
    test_clear();
    test_free();
    test_index_of();
    test_insert();
    test_prepend();
    test_remove();
    test_remove_range();
    test_sort();
}

void test_sort(void)
{
    #define count 10
    // входные данные
    const int data [count] = {9, 6, 1, 5, 4, 7, 0, 3, 8, 2};
    // ожидаемый результат
    const int sorted_data [count] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ArrayList *list = arraylist_new(count);

    for (size_t i = 0; i < count; i++)
    {
        assert(arraylist_append(list, &data[i]));
    }

    #include "compare-int.h"
    #include "compare-int.c"

    arraylist_sort(list, int_compare);

    for (size_t i = 0; i < count; i++)
    {
        // сравнение полученного результата с ожидаемым
        assert(sorted_data[i] == *((int *)list->data[i]));
    }
}

// остальные тесты здесь
