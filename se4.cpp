#include <iostream>
#include <vector>

// polymoprhism:
// - ad-hoc (overloading - functions, operators)
// -- overloading
// -- coercion (implicit typecasting)
// - universal
// -- parametric (generics)
// -- inclusion (subtyping)

template <int rows, int cols, typename T>
void cmp(T (&matrix)[rows][cols])
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

template <typename key_t, typename value_t>
struct Pair
{
    key_t k{0};
    value_t v{0};

    friend std::ostream &
    operator<<(std::ostream &os, const Pair<key_t, value_t> obj)
    {
        return os << obj.k << ":" << obj.v;
    }
};

int main(int argc, char const *argv[])
{
    Pair<std::string, int> m[2][2] = {
        {{"a", 1}, {"b", 2}},
        {{"c", 3}, {"d", 4}},
    };

    cmp(m);

    return 0;
}
