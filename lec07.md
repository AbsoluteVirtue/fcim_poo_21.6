# Шаблоны функций и типов
Шаблоны уже встречались в предыдущих частях, но до сих пор не обсуждалась их роль в программах. В первую очередь, шаблоны позволяют определять семейства классов или функций. Дополнительно, с их помощью можно определить альтернативные имена для уже существующих типов (аналогично typedef в языке С), семейства переменных и "концепции" -- особый вид ограничений, позволяющий проверять выполнение определенных условий при вызове функций и т.п.

Суть шаблона сводится к тому, что он позволяет создать "пустой" (обобщенный) класс (или функцию), который можно скомпилировать, не указывая его окончательную структуру. Вместо этого достаточно заменить типы данных или выражения в классе (или функции) на произвольные имена, которые при компиляции будут заменены на конкретные типы или вражения автоматически.

    template<class T, T::type n = 0> class X;
    
    struct S {
        using type = int;
    };
Пример выше показывает объявление шаблонного типа *X* и структуры *S*, которая использует альтернативное имя для типа int. Шаблон *X* в объявлении использует такое же альтернативное имя, то есть, для объявления шаблона можно использовать несуществующие имена, если компилятор может найти определения этих имен в дальнейшем.

    using U = X<S>;
Данная строка является правильной с точки зрения компиляции, так как можно определить конкретные типы всех участвующих в этом определении имен. Имя *U* -- это псевдоним для комбинации символов *X* и *S*, где имя *X* определено через *S*. Причем, *Х* полностью определяется *S*, потому что *Х* зависит от произвольного типа *T*, при этом тип *T* должен содержать имя *type*, которое может быть использовано как тип для константы *n*, при этом *n* должно быть инициализировано значением "0". Тип *S* удовлетворяет этим требованиям, поэтому он может использоваться в определении *X* для подмены символа *T*. Из этого есть интересное следствие. Любой тип или символ, который отвечает этим требованиям, может быть использован для определения *X*, как в примере ниже.

    template<class T, T::type n = 0> class X;

    struct SL {
        using type = long;
    };
    
    using U = X<SL>;
Структура *SL* содержит имя type, которое может быть типом для переменной, инициализированной нулем. 

Из примеров выше можно сделать некоторые выводы. Во-первых, шаблоны образуют формальную грамматику -- набор правил для замены символов или комбинаций символов, определяемых другими правилами, которые, в свою очередь, также определены какими-то правилами. Во-вторых, шаблоны позволяют писать определения, которые не зависят от конкретных типов, а зависят от абстракций. Аналогично типам, которые зависят от абстрактных типов в иерархиях наследования, шаблоны позволяют создавать семейства типов. Эти семейства типов можно использовать для написания полиморфного кода.
## Макросы и шаблоны
Может показаться, что шаблоны работают аналогично "макро"-определениям из языка С.

    #define pair(T, U) struct pair_##T##_##U { 
        T first;
        U second;
    }
Например, такой "макрос" при написании утверждения *pair(int, double)* будет с помощью простой текстовой подстановки заменен на следующий код,

    struct pair_int_double { 
        int first;
        double second;
    }
Аналогичный шаблон, который определяется так.

    template <typename T, typename U> class pair {
        T first;
        U second;
    };
При инстанциировании с помощью утверждения *pair<int, double>{};* создастся экземпляр шаблона,

    template <> class pair<int, double> {
        int first;
        double second;
    };
Разница между двумя этими примерами неочевидна. Главное отличие в том, что макрос не всегда определяет новую функцию или тип, а всего лишь задает порядок замены текста в коде программы перед компиляцией. Это механическая подстановка, которая не проверяется компилятором. Второе отличие в том, что макрос не определяет семейство типов или функций. В качестве более сложного примера можно рассмотреть функцию из прошлой лекции. 

    template <typename T, size_t n> T prod(const T(&a)[n], const T(&b)[n]);
Теперь на него можно взглянуть под другим углом: символ *prod* объявляет семейство функций, носящих это имя, а объединяются все функции данного семейства посредством символа *T* и константы *n*. В программе можно определить одну из функций данного семейства, создав ее экземпляр(ы). Все экземпляры шаблона являются конкретными функциями, которые отличаются друг от друга конкретными типами или выражениями, которые подставляются в экземпляр при его объявлении, как показано на примере ниже.

    auto result = prod({1, 2, 3}, {4, 5, 6});
Этот экземпляр использует массивы целочисленных значений в качестве аргументов. Следовательно, параметры экземпляра с помощью подстановки будут определены как массивы типа *int[3]* (символ *T* заменяется на тип отдельного элемента аргумента, символ *n* заменяется на размер аргумента).

Отсюда следует несколько важных свойств данного шаблона. Из него можно порождать бесконечно много экземпляров подстановкой разных типов. Но интересней другое: на аргументы естественным образом накладывается несколько ограничений. Первое ограничение -- размер массивов, который должен совпадать, т.е. нельзя создать экземпляр функции, передав ей два массива разных размеров. Второе ограничение -- тип данных элементов массива, который также должен совпадать для обоих аргументов. Это, в свою очередь, значит, что определение шаблона может не содержать эти проверки, так как любой экземпляр, не отвечающий данным требованиям, не может быть инстанциирован компилятором. 

Последнее важное следствие из этого, которое нужно упомянуть, состоит в том, что в ходе работы программы все экземпляры уже заведомо созданы, а значит их создание не влияет на производительность программы, но влияет на производительность во время компиляции. Каждый экземпляр функции или класса из конкретного семества должен быть проверен компилятором на правильность, поэтому их все необходимо сгенерировать, что значительно увеличивает количество компилируемого кода.  
## Динамический и статический полиморфизм
Можно отметить, что на стадии компиляции шаблоны технически не отличаются от перегрузки. Независимо от того, используется перегрузка или шаблон, тип данных всех аргументов функции известен компилятору заранее. В случае перегрузки это нужно, чтобы компилятор проверил правильную версию функции из набора перегрузок. В случае шаблона это нужно чтобы компилятор проверил сгенерированную на основании шаблона специализацию-кандидата. Все, что делается во время компиляции (до непосредственного запуска скомпилированной программы), называется "статическим" процессом. Другой вид процесса -- динамический, который происходит уже после компиляции -- в ходе работы программы, так как нужная информация для проверки заранее компилятору не была доступна.

Таким образом можно подвести промежуточные итоги про особенности полиморфизма. Динамический полиморфизм:
* основан на создании иерархий типов данных (либо через наследование, либо через меченые объединения, либо другим аналогичным способом);
* создает абстракции как интерфейсы, которые являются вершиной иерархии;
* влияет на производительность программы (run-time);
* не позволяет компилятору проверять правильность алгоритмов или свойств типов данных.

Статический полиморфизм:
* основан на создании семейств типов данных через определение шаблонов;
* создает абстракции как интерфейсы, которые являются правильно определенными шаблонами;
* влияет на производительность компилятора (compile-time);
* возможно доказать правильность алгоритмов для некоторых семейств типов данных.

При этом и динамический, и статический полиморфизм может быть универсальным или специальным, но два списка выше описывают универсальный полиморфизм, так как он позволяет создавать программы из компонентов более общего характера -- код каждого компонента является единым для всех вариаций используемых типов -- из-за чего он представляет больший интерес в контексте ООП. Из универсальности -- единой структуры конкретных реализаций, создаваемых для абстракций-шаблонов или абстрактных классов -- вырастает особенный подход к написанию программ.
# Обобщенное программирование
Важным следствием из возможности писать полиморфные функции и параметризовать типы данных является потенциал к декомпозиции программ на компоненты, которые можно определять отдельно друг от друга и затем комбинировать в произвольной последовательности, при условии, что отдельные компоненты согласуются с требованиями четко определенного интерфейса. Такой подход исторически принято называть "обобщенным программированием" (generic), а обобщенные компоненты принято называть "обобщенностями" (generics).

Исторически термин "обобщенность" заимствуется из языка программирования Ada, для которого была создана экспериментальная библиотека Ada Generic Library, содержавшая отдельные модули для работы с произвольными последовательностями из произвольных элементов. То есть, представление данных было отделено от абстрактных типов и операций над абстрактными типами. Это позволяло скрыть конкретную реализацию, не обращаясь к ней напрямую. Вместо этого явно вызывался абстрактный интерфейс, который автоматически подменялся на правильную реализацию.  

В качестве примера можно рассмотреть три абстрактных типа данных: динамический массив, односвязный список и двусвязный список. Эти три типа объединяет то, что элементы, хранящиеся в них, упорядочены. Следовательно, обход элементов с точки зрения пользователя не отличается для этих трех типов: все элементы будут пройдены от начала до конца, и ассимптотичность прохода будет линейная. Достаточно предоставить абстрактный алгоритм прохода по упорядоченной последовательности, чтобы удовлетворить ожидания всех пользователей. Такой абстрактный алгоритм должен состоять из трех элементов: "геттера" для конкретного элемента в конкретной позиции; предиката, который определяет выход за пределы последовательности; оператора, который переходит на следующий элемент из произвольного текущего элемента -- конкретные реализации этих трех компонентов могут быть скрыты самими абстрактными типами данных. Достаточно предоставить возможность программе выбирать нужную реализацию при вызове абстрактного алгоритма. Или, если посмотреть на ситуацию с другой стороны, достаточно позволить программе игнорировать те свойства абстрактных типов данных, которые не имеют отношения к абстрактному алгоритму. 

Этот подход позже был перенесен в язык С++ вместе с добавлением в С++ языка шаблонов. Как говорил Строуструп,
> Для многих людей главная проблема в использовании С++ заключается в отсутствии обширной стандартной библиотеки. Большой трудностью в создании такой библиотеки является то, что С++ не предоставляет достаточно общий способ для определения "классов-контейнеров" типа списка, вектора, ассоциативного массива и т.п.

Шаблоны стали таким "общим способом", потому что они позволили создавать абстрактные классы без наследования, пожертвовав динамическим полиморфизмом в пользу проверяемости кода компилятором.

Reuse has been successful in the area of libraries. However, these libraries have the characteristic that they use fully specified interfaces that support a pre-determined set of types, and make little or no attempt to operate on arbitrary user types. Generic programming recognizes that dramatic productivity improvements must come from reuse without modification, as with the successful libraries. Breadth of use, however, must come from the separation of underlying data types, data structures, and algorithms, allowing users to combine components of each sort from either the library or their own code. Accomplishing this requires more than just simple, abstract interfaces -- it requires that a wide variety of components share the same interface so that they can be substituted for one another. It is vital that we go beyond the old library model of reusing identical interfaces with pre-determined types, to one which identifies the minimal requirements on interfaces and allows reuse by similar interfaces which meet those requirements but may differ quite widely otherwise. 

We call the set of axioms satisfied by a data type and a set of operations on it a concept. Examples of concepts might be an integer data type with an addition operation satisfying the usual axioms; or a list of data objects with a first element, an iterator for traversing the list, and a test for identifying the end of the list. Highly reusable components must be programmed assuming a minimal collection of such concepts, and that the concepts used must match as wide a variety of concrete program structures as possible.

STL achieves the performance objectives by using the C++ template mechanism to tailor concept references to the underlying concrete structures at compile time instead of resolving generality at runtime. However, it must be extended far beyond its current domain in order to achieve full industrialization of software development. 

The development of built-in types and operators on them in programming languages over the years has led to relatively consistent definitions which match both programmer intuition and our
underlying mathematical understanding. Therefore, concepts which match the semantics of built-in types and operators provide an excellent foundation for generic programming.
## Regular types
> User-defined types behave like built-in types.

The built-in types in C++ vary substantially in the number and semantics of the
built-in operators they support, so this is far from a rigorous definition. However, we
observe that there is a core set of built-in operators which are defined for all built-in
types (see table).  We attempt to identify the essential semantics of these operations, which
we call the fundamental operations on a type T.
### Copy, Assignment, and Equality
1. T a = b; assert(a==b);
2. T a; a = b; ⇔ T a = b;
3. T a = c; T b = c; a = d; assert(b==c);
4. T a = c; T b = c; zap(a); assert(b==c && a!=b);
### Equality of Regular Types
The equivalence,

    x == y ⇔ ∀ predicate P, P(x) == P(y)
doesn't hold for the right-to-left case, even if P is restricted to well behaved predicates, for the simple reason that
there are far too many predicates P to make this a useful basis for deciding equality.

Computer hardware generally defines an equality relation on the
built-in types which it implements efficiently. This equality relation is normally
bitwise equality (although there are sometimes minor deviations like distinct positive
and negative zero representations). Starting from this basis, there is a natural default
equality for types composed of simpler types, i.e. equality of corresponding parts of the composite objects.

Objects which are naturally variable sized must be constructed in C++ out of multiple simple structs, connected by pointers. In such
cases, we say that the object has remote parts. Our second caveat then is that an equality
operator should ignore inessential components.

> Two objects are equal if their corresponding parts are equal (applied
recursively), including remote parts (but not comparing their addresses), excluding
inessential components, and excluding components which identify related objects.

Most of us would intuitively assume that a visible accessor function, that is a
public function which returns the value of some component of a composite type,
would be a reasonable function which should satisfy the above condition. However,

    r1 == r2 ⇒ r1.p == r2.p
    (1,2) == (2,4) ⇒ 1 == 2
First, we could avoid defining an equality operator (perhaps
defining an equiv function with the mathematical definition instead). Second, we
could avoid making p and q visible parts of our rational number type. Finally, we
could require that any rational number represented by this type is always in reduced
form, i.e. its numerator and denominator have no common divisors.
## Концепции
If we are to
succeed in producing widely reusable components, idiosyncratic interfaces are no
longer usable. A component programmer must be able to make some fundamental
assumptions about the interfaces she uses, without ever seeing their implementations
or even imagining their applications. Similarly, her eventual users must provide the
types implementing those interfaces, and if the same types are to interface with a
variety of generic components, the interfaces must be consistent with one another.

    x == y ⇒ ∀ “reasonable” function foo, foo(x)==foo(y)
What is a reasonable function? For optimization purposes, there are several
classes of functions we would like to capture. First are the standard operators on
built-in types that do not have side effects, for example a+b, c-d, or p%q. Second are
the visible member accesses, e.g. s.first or c->imaginary. A third class is the wellknown pure functions, e.g. abs(x), sqrt(y), and cos(z). The ultimate solution,
then, must be to identify the important attributes, and allow programmers to specify
them explicitly. 

For regular types, we therefore require that constructors, destructors, and
assignment operators be linear (average-case) in the area (i.e. the total size of all
parts) of the object involved. Similarly, we require that the equality operator have
linear worst-case complexity. (The average-case complexity of equality is typically
nearly constant, since unequal objects tend to test unequal in an early part.)

