#include <assert.h>


struct container
{
    unsigned int size() const;
    int front() const;
    int back() const;
    void insert(const unsigned int idx, const int x);
    void append(const int x);
    void extend(const container &other);
    int pop(const unsigned int idx);
    void remove(const int x);
    unsigned int index(const int x) const;
    unsigned int count(const int x) const;
    static bool is_equal(const container &dest, const container &other);
    int at(const int idx) const;
    ~container();
    container();
    container(const container &other);
    container(const unsigned int n);
    container(const int *x, const unsigned int n);
private:
    int *value{nullptr};
    unsigned int length{0};
};

int main(int argc, char const *argv[])
{
    int array[] = {1, 4, 7, 9};

    container a(array, 4);

    container b(a);
    a.append(10);
    assert(1 == a.front());
    assert(10 == a.back());

    b.insert(0, 10);
    assert(10 == b.front());
    assert(1 == b.at(1));
    assert(9 == b.back());

    container c;
    c.extend(b);
    assert(container::is_equal(c, b));
    assert(0 == c.index(10));

    a.extend(c);
    assert(2 == a.count(10));
    assert(9 == a.pop(20));
    assert(7 == a.back());
    
    a.remove(4);
    assert(7 == a.at(1));
    assert(8 == a.size());
}
