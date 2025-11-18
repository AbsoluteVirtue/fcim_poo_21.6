// код для проверки правильности выполнения задания:
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <utility>
// остальные необходимые библиотеки здесь

using container = /* название варианта здесь */;

int main() {
    abstract_data_t *v = new container({2, 3, 5, 7});
    assert(!v->empty());
    v->push(11);
    assert(11 == v->back());
    assert(11 == (*v)[v->size() - 1]);
    v->extend(container({13, 17, 19}));
    assert(8 == v->size());
    abstract_data_t *w = new container();
    assert(w->empty());
    *w = *v;
    assert(*w == *v);
    (*w)[0] = 0;
    assert(0 == w->front());
    w->pop();
    assert(17 == w->back());
    assert(7 == w->size());
}
