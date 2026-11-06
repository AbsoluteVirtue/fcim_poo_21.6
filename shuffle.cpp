#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <random>

static const char* names[] = {

};

int main(void) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(names, names + 97, g);

    std::size_t no = 0;
    for (auto &&s : names) std::cout << ++no << ' ' << s << '\n';
}
