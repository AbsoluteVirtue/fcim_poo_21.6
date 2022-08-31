
#include <assert.h>
#include <iostream>

struct pod
{
    int *value;
    unsigned int length;
};

void copy(pod &dest, const pod &other)
{
    if (dest.value)
        delete[] dest.value;

    dest.length = other.length;
    dest.value = new int[dest.length];
    for (unsigned int i = 0; i < dest.length; ++i)
    {
        dest.value[i] = other.value[i];
    }
}

bool eq(const pod &dest, const pod &other)
{
    if (dest.length != other.length)
        return false;

    for (unsigned int i = 0; i < dest.length; ++i)
    {
        if (dest.value[i] != other.value[i])
            return false;
    }
    return true;
}

int at(const pod &dest, const int idx)
{
    // FIXME: find a way without comparing int and uint 
    unsigned int i = (idx < 0) ? ((-idx < dest.length) ? dest.length + idx : 0) : idx;
    return dest.value[(i > dest.length - 1) ? dest.length - 1 : i];
}

void make_from_array(pod &dest, const int *x, const unsigned int n)
{
    if (dest.value)
        delete[] dest.value;

    dest.length = n;
    dest.value = new int[dest.length];
    for (unsigned int i = 0; i < dest.length; ++i)
    {
        dest.value[i] = x[i];
    }
}

void make_empty(pod &dest)
{
    dest.length = 0;
    dest.value = nullptr;
}

void clear(pod &dest)
{ 
    delete[] dest.value;
    dest.length = 0;
    dest.value = nullptr;
}

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
    copy(b, a);
    assert( 1 == at(b, 0));

    assert(eq(a, b));

    clear(a);
    clear(b);
}
