// https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
// https://publications.gbdirect.co.uk//c_book/chapter9/stdarg.html
// https://www.stroustrup.com/C++11FAQ.html#variadic-templates

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <string>

template <typename T>
void print(T t)
{
	std::cout << t << " ";
}

template <typename T, typename... Args>
void print(T t, Args... args)
{
	std::cout << t << " ";
	print(args...);
}

template <typename T>
void func(T t)
{
    std::cout << __PRETTY_FUNCTION__ << ": " << t <<std::endl;
}

template <typename T, typename... Args>
void func(T t, Args... args) // recursive variadic function
{
    std::cout << __PRETTY_FUNCTION__ << ": " << t <<std::endl;

    func(args...);
}

template <class T>
void func2(std::initializer_list<T> list)
{
    for (auto elem : list)
    {
        std::cout << elem << std::endl;
    }
}

// function objects are used to pass code into templates for inlining
bool func_less_abs(double x, double y)
{
    return std::abs(x) < std::abs(y);
}

struct less_abs
{
    bool operator()(double x, double y) const
    {
        return std::abs(x) < std::abs(y);
    }
};

// as well as -- to associate a datum that is computed at run-time with code
// as opposed to creating a global variable
double a;

bool func_less_distance(double x, double y)
{
    return std::abs(x - a) < std::abs(y - a);
}

template <typename T>
inline
T abs(const T& x)
{
    return x < T(0) ? -x : x;
}

template <typename T>
struct less_distance
{
    T x;

    less_distance(const T &a0) : x(a0) {}

    friend bool operator<(const T &lhs, const T &rhs) const
    {
        return abs(lhs - this->x) < abs(rhs - this->x);
    }
};

// generate new function objects using existing ones for automatic type inference  
template <typename T>
inline
less_distance<T> make_less_distance(const T& x)
{
    return less_distance<T>(x);
}

// function binding for funtion composition f(x) g(x) => f(g(x)) using adaptor
template <class F, class G>
struct unary_compose
{
    typedef typename G::argument_type argument_type;
    typedef typename F::result_type result_type;
    F f;
    G g;
    unary_compose(const F& f0, const G& g0) : f(f0), g(g0) {}
    result_type operator() (const argument_type& x) const 
    {
        return f(g(x));
    }
};

template <class F, class G>
inline
unary_compose<F, G> compose(const F& f, const G& g)
{
    return unary_compose<F, G>(f, g);
}


int main()
{
    std::string str1("Hello"), str2("world");

    func(1, 2.5, 'a', str1);

    func2({10, 20, 30, 40});
    func2({str1, str2});

    print(1, 2, 3, 4);

    double array[100];

    std::sort(array, array + N, func_less_abs);

    std::sort(array, array + N, less_abs());

    double b;
    std::sort(array, array + N, less_distance<double>(b));

    std::sort(array, array + N, make_less_distance(b));
}
