#include <array>
#include <cassert>
#include <cmath>
#include <type_traits> // !
#include <vector>

template <typename Number>
auto template_function(Number a, Number b) {
    return a + b;
}

// SFINAE (substitution failure is not an error)
template <
    typename Number,
    typename = std::enable_if_t<std::is_floating_point_v<Number>>
> // ::type < ::value>
auto sfinae_function(Number a, Number b) {
    return a + b;
}

// ver. C++ 20: -std=c++2a

template <typename Number>
auto req_function(Number a, Number b) requires std::is_floating_point_v<Number> {
    return a + b;
}

template <typename T>
concept floating_point = std::floating_point<T>;

template <floating_point Number>
auto concept_function(Number a, Number b) {
    return a + b;
}

floating_point auto concept_auto_function(const floating_point auto a, const floating_point auto b) {
    return a + b;
}

// Containers

auto length(const auto &container) {
    if constexpr (
        requires { container.capacity(); }
    ) {
        return container.capacity();
    } else {
        return container.size();
    }
}

template <typename Vec>
using Scalar = std::decay<decltype(Vec()[0])>::type;

template <typename Vec>
concept FloatVec = std::floating_point<Scalar<Vec>> &&
   requires(Vec v) {
       { v.size() } -> std::integral;
   };

template <FloatVec V>
auto norm(const V& v) -> Scalar<V> {
   using Size = decltype(v.size());
   Scalar<V> result = 0;
   for (Size i = 0; i < v.size(); i++) {
       result += v[i] * v[i];
   }
   return std::sqrt(result);
}

// C++ 17
#include <type_traits> // enable_if, conjuction

template<class Head, class... Tail>
using are_same = std::conjunction<std::is_same<Head, Tail>...>;

template<class Head, class... Tail, class = std::enable_if_t<are_same<Head, Tail...>::value, void>>
void print_same_type(Head head, Tail... tail)
{
    std::cout << head;
    (std::cout << ... << tail) << "\n";
}

int main() {
    std::vector<double> v;
    assert(0 == length(v));

    std::array<int, 10> a;
    assert(10 == length(a));

    auto r = norm(v);

    print_same_type("2: ", "Hello, ", "World!");     // OK
    // print_same_type(3, ": ", "Hello, ", "World!");   // no matching function for call to 'print_same_type(int, const char [3], const char [8], const char [7])'
}
