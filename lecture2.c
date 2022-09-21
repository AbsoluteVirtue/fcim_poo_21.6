#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// method example
typedef struct 
{
    int (* sq)(int a);
} T;

int test_func(int a) 
{ 
    return a * a;
}

// inheritance example
typedef struct Boolean
{
    struct Boolean* self;
    void (*ifTrue) (void (*expression)());
} Boolean;

void true_func(void (*expression)())
{
    return expression();
}

int main(int argc, char *argv[], char *envp[])
{
    // method example
    T a = {.sq = test_func};

    int x = a.sq(10);
    printf("%d", x);

    // int y = 1 ?: 0;

    // inheritance example
    Boolean True = {.self = &True, .ifTrue = true_func};

    True.ifTrue(x);
}
