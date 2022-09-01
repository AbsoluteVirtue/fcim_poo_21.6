#include <assert.h>


struct container
{
    int front();
    int back();
    int at(const int);
    int pop(const unsigned int);
    void append(const int);
    void extend(const int *, const unsigned int);
    void insert(const unsigned int, const int);
    void remove(const int);
    unsigned int index(const int);
    unsigned int count(const int);
    static bool is_equal(const container &, const container &);
    container(const container &);
    container(const int *, const unsigned int);
    container(const unsigned int);
    container();
    ~container();
private:
    int *value;
    unsigned int length;
};

int main(int argc, char const *argv[])
{
    int array[] = {1, 4, 7, 9};

    container a(array, 4);
    assert(9 == a.at(3));
    assert(9 == a.at(-1));
    assert(9 == a.at(13));
    assert(1 == a.at(-13));

    container b(a);
    assert(1 == b.front());
    assert(9 == b.back());

    assert(container::is_equal(a, b));

    // 
}
