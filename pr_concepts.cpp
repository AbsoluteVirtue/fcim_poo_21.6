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

int main() {
    std::vector<double> v;
    assert(0 == length(v));

    std::array<int, 10> a;
    assert(10 == length(a));

    auto r = norm(v);
}
