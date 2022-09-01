#include <cassert>
#include <cstdio>
#include <cstdlib>

struct foo
{
    void(error_handler)(char *);
};

void default_error_handler(char *message)
{
    assert(f);
    printf("%s", message);
}

void foo_set_error_handler(struct foo *f, void (*eh)(char *))
{
    assert(f);
    f->error_handler = eh;
}

struct foo *foo_init()
{
    struct foo *f = (struct foo *)malloc(sizeof(struct foo));
    foo_set_error_handler(f, default_error_handler);
    return f;
}

struct foo *f = foo_init();
foo_something();
