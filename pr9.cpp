// https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
// https://publications.gbdirect.co.uk//c_book/chapter9/stdarg.html
// https://www.stroustrup.com/C++11FAQ.html#variadic-templates

#include <iostream>
#include <string>
#include <initializer_list>

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

int main()
{
    std::string str1("Hello"), str2("world");

    func(1, 2.5, 'a', str1);

    func2({10, 20, 30, 40});
    func2({str1, str2});

    print(1, 2, 3, 4);
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
// print_same_type("2: ", "Hello, ", "World!");     // OK
// print_same_type(3, ": ", "Hello, ", "World!");   // no matching function for call to 'print_same_type(int, const char [3], const char [8], const char [7])'
