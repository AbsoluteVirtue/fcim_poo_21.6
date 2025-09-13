/*
    1. #include <cstdio> или #include <stdio.h>
    2. using namespace std;
    3. class или struct
    4. указатели или ссылки
    5. new или malloc (delete, delete[] или free)
    6. std::cout или printf
    7. std::array<int, n> или int[n]
*/

int main() {
    #define 1_
    
    #ifdef 1_1
    // #include <cstdio> или #include <stdio.h>
    {
        #include <stdio.h> // сохраняется в языке С++ для обратной совместимости с кодом на языке С
        // все имена, упомянутые в таком файле, импортируются в программу на глобальном уровне
        // как и большинство подобных файлов, все такие файлы имеют файл-дубликат по типу cstdio
        #include <cstdio> // все имена, упомянутые в таком файле, импортируются в программу из пространства имен std
        // если код программы не обязан соответствовать стандарту языка ISO C, использовать версию .h не рекомендуется 
    }
    // https://en.cppreference.com/w/cpp/header
    #endif
    
    #ifdef 1_2
    {
        using namespace std; // директива вводит все имена из соответствующего пространства имен в глобальную область программы
        // это может привести к конфликтам имен, также создавая ненужные зависимости между разными заголовочными файлами
        // по этим причинам не рекомендуется использовать эту директиву на глобальном уровне файла или в заголовочных файлах

        namespace x {
            enum { A = 10 };
        }

        namespace y {
            enum { A = 20 };
        }

        printf("%d %d", x::A, y::A);
    }
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rs-using-directive
    #endif

    #ifdef 1_3
    // class или struct
    {
        // в языке С ключевое слово struct вводит тип данных, который состоит из уже существующих типов данных (аналог алгебраического типа-суммы)
        // структура используется для организации памяти составного объекта

        // в языке С++ ключевое слово struct имеет дополнительные свойства
        // a. оно может обозначать перечислимый тип (enumeration)
        // b. его можно использовать для смены контекста применения имен в заданной области видимости:
        void f(int);

        struct f {
            int a;
        };

        f(5);
        struct f x{5};
        // https://en.cppreference.com/w/cpp/language/elaborated_type_specifier.html

        // в языке С++ принципиальных различий между словами class и struct нет, за исключением:
        // a. объявления шаблонных аргументов (template <class C>)
        // b. доступа к полям с данными:
        struct x {
            int a;
        private:
            int b;
        };

        class y {
            int a;
        public:
            int b;
        }
        // по умолчанию ключевое слово struct оставляет внутренние поля открытыми, а слово class - скрытыми
        // это поведение можно изменить с помошью специальных меток public и private
        // https://en.cppreference.com/w/cpp/language/access
    }
    // https://en.cppreference.com/w/cpp/keyword/struct
    // https://foldoc.org/Algebraic+data+type
    #endif

    #ifdef 1_4
    // указатели или ссылки
    {
        // ссылки являются специальными указателями, и добавляют некоторые ограничения к правилам работы с указателями
        int *p;             // можно
        int &r;             // нельзя
        int &r = NULL;      // нельзя
        int i;
        int *p = &i;        // можно
        int &r = i;         // можно
        int &r = 2;         // нельзя
        const int &r = 2;   // можно
        int &a[3];          // нельзя
        int &*p;            // нельзя
        int &&r;            // нельзя

        // ссылки напрямую связаны с категориями значений в C++, самыми простыми категориями являются lvalue и rvalue
        void f(int&);       // ссылка на lvalue
        void g(int&&);      // ссылка на rvalue
        void h(const int&); // универсальная ссылка

        int i = 0;

        f(i);   // можно
        f(42);  // нельзя

        g(i);   // нельзя
        g(42);  // можно

        h(i);   // можно
        h(42);  // можно
    }
    // https://en.cppreference.com/w/cpp/language/reference_initialization
    // https://en.cppreference.com/w/cpp/language/value_category
    #endif

    #ifdef 1_5
    // new или malloc (delete, delete[] или free)
    {
        // выражение new описывается ключевым словом new и вызывает подходящую из доступных функцию для выделения памяти
        // если память выделяется под массив, это делается с помощью функции    operator new[]
        // если память выделяется не под массив, это делается с помощью функции operator new
        // эти функции можно заменить в своем классе
        // выражение new также вызывает подходящий конструктор класса
        auto s = new int; // скалярная величина
        // или
        auto s = new int {42}; // со значением по умолчанию
        int *s = malloc(sizeof(int)); // аналог в С
        
        auto a = new int [2] {0, 1}; // массив скалярных величин
        // или 
        auto a = new int [2] {0, 1}; // со значениями по умолчанию
        int *a = calloc(2, sizeof(int)); // аналог в С

        // аналогично, выражение delete вызывает подходящий деструктор класса (если объект - массив, деструкторы вызываются для каждого объекта массива)
        // после этого вызывается функция освобождения памяти (если не произошло исключений на предыдущем этапе)
        // этими функциями являются operator delete[] для массивов и operator delete для остальных случаев
        delete s;
        delete [] a;

        free(a); // аналог в С для обоих случаев
    }
    // https://en.cppreference.com/w/cpp/language/new
    // https://en.cppreference.com/w/cpp/language/delete
    #endif

    #ifdef 1_6
    // std::cout или printf
    {
        // класс basic_ostream используется для работы с массивами символов (строками) по умолчанию
        // для объекта cout используется определение:
        typedef basic_ostream<char> ostream;
        // тогда в пространстве имен std объявляются следующие переменные:
        namespace std {
            // ...
            extern istream cin;  /// Linked to standard input
            extern ostream cout; /// Linked to standard output
            extern ostream cerr; /// Linked to standard error (unbuffered)
            extern ostream clog; /// Linked to standard error (buffered)
        }

        // данный класс реализует функцию вывода operator<<
        std::cout.operator<<(42);
        printf(“%d”, 42); // аналог в С

        // для повторного вывода используются вызовы функции по цепочке:
        std::cout.operator<<("The answer to life, the universe, and everything: ")
                .operator<<(42)
                .operator<<(std::endl);
        // или в общепринятой форме:
        std::cout   << "The answer to life, the universe, and everything: " 
                    << 42 
                    << std::endl;
        printf("The answer to life, the universe, and everything: %d\n", 42); // аналог в С
    }
    // https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a00911_source.html
    #endif

    #ifdef 1_7
    // std::array<int, n> или int[n]
    {
        // std::array - это шаблонный класс (обобщенный тип), который инкапсулирует статический массив (тип[])
        std::array a = {1, 2, 3, 4};
        a[0] = 0;
        // или
        std::array<int, 4> a = {1, 2, 3, 4};
        int a[4] = {1, 2, 3, 4}; // аналог в С

        // он устроен аналогично стуктуре данных, одним из полей которой является массив из языка С
        #define N 10
        struct array {
            int p[N];
        };
        // или
        template <class T, size_t N> class array {
            T p[N];
        };

        // аналогом шаблонов (template) из С++ можно считать макросы в языке С
        #define pair(T, N) struct pair_##T##_##N { 
            T first;
            N second;
        }
    }
    // https://en.cppreference.com/w/cpp/container/array
    #endif

}