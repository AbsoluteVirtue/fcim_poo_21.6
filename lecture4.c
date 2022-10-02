#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>

#define n 4

int index(int a[n], const int find)
{
    for (size_t i = 0; i < n; i++)
    {
        if (find == a[i])
            return i;
    }
    return n;
}

int main(int argc, char const *argv[])
{
    errno = NO_ERROR;
    FILE *f_pointer;
    f_pointer = fopen("no_file.here", "r");
    if (NULL == f_pointer)
        printf("Ошибка при открытии файла: %s\n", strerror(errno));

    char text[50] = {};
    if(1 != scanf("%50s", text))
        perror("Ошибка при чтении ввода\n");

    int a[n] = {1, 2, 3, 4};

    int x = index(a, 3);
    if (n == x)
        perror("Выход за пределы массива\n");
    else
        printf("%d", x);
}
