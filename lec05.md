# Наследование
Концепция наследования появилась на заре программирования, еще в 1960-е годы, но широкое распространиение получила благодаря языку Simula. Как говорилось в одной из предыдущих частей, для обозначения связи между подпроцессами в язык были введены понятия "класс" и "подкласс". Причем, "подклассы процессов представляли собой описания со своими собственными операциями и локальными данными (аналогично объектам-функциям в Lisp)," при этом уже включая свойства родительского процесса, расширяя его возможности.

    class Page;
    begin
        class Print_Block(Width,Length);integer Width, Length;
        begin
        ref(Print_Block)Next;
        text array Contents(1:Length);
        integer Count;
        for Count:=1 step 1 until Length do Contents(Count):-Blanks(Width)
        end--of--Print_Block;

        Print_Block class Title_Block(Title);text Title;
        begin
        Contents(Length//2):=Title
        end--of--Title_Block;

        Print_Block class Text_Block;
        begin
        for Count:=1 step 1 until Length do
        begin
            InImage;
            Contents(Count):=Intext(Width)
        end
        end--of--Text_Block;
    end..of..Page;
    new Page;
Строки *Print_Block class Title_Block* и *Print_Block class Text_Block* указывают на то, что процессы типа Title_Block и Text_Block расширяют процесс Print_Block, который выступает их "префиксом".

Алан Кей говорит о наследовании так:

> "Программирование с помощью наследования показывает силу дифференцированного описания. Например, есть общее понятие 'облако', представленное объектом. Программист может создать облако прямоугольной формы, таким образом дифференцировав его, получая объект 'прямоугольник', который один в один как облако, за исключением..."

Наследование в Simula-67 было обобщением идеи блоков в Algol 60. Но то, как оно было реализовано, не устраивало Алана Кея (слишком тесная связь между префиксом и подклассом, линейная иерархия, трудности в использовании в интерактивных приложениях с поступенчатой компиляцией, где необходима возможность изменять "горячий" код), поэтому в Smalltalk семантику наследования пришлось немного изменить.

Дэн Ингаллс, который писал реализацию Smalltalk, повторил принцип наследования из Simula, но внес в него необходимые изменения. Ниже представлен пример кода с наследованием в Smalltalk-76.

    Class new title: 'Window'; 
        fields='frame'; 
        asFollows!
        ...
    Default Event Responses
    enter [self show] 
    leave 
    outside [^false] 
    pendown 
    keyboard [keyboard next. frame flash] 
    Image 
    show

    Class new title= 'DocWindow'; 
        subclassof: Window; 
        flelds='document scrollbar edit Menu'; 
        asFollows!
    Event Responses
    enter [self show.editMenu show.scrollbar show] 
    leave [document hideselection.editMenu hide.scrollbar hide] 
    outside
        [editMenu startup => [] 
        scrollbar startup => [self showDoc] 
        ^false] 
    pendown [document pendown] 
    keyboard [document keyboard]
    Image
    show [super show.self showDoc]
    showDoc [doucument showin: frame at: scrollbar position] 
Класс DocWindow является подклассом класса Window, а значит предоставляет те же самые методы, расширяя функционал "окна" своими дополнительными методами, которые присущи только окну "документа".

Технически реализация наследования Алана Кея устраивала, но сама логика наследования оставляла желать лучшего. Например, нет четкого семантического разделения между наследованием класса и инстанциированием класса. В обоих случаях появляется объект со свойствами родительского класса. Отсюда и неясность относительно пользы одного из подходов относительно другого. К тому же, наследование позволяет выразить достаточно много идей одним и тем же синтаксисом, что может потом навредить программе, так как совсем не очевидно, какую именно из идей выражает программист в каждом конкретном случае, если применяет наследование.

Больше всего Алан Кей сомневался насчет полезности статического наследования. Основой Smalltalk было динамическое связывание значений, а значит конкретный тип объекта во время компиляции не должен быть известен. Тип аргумента должен определяться из контекста только во время вызова метода объекта, как и тип самого объекта. Также, Алан Кей считал, что множественное наследование важно поддерживать в языке (если "обычное" наследование позволяет много раз наследовать один и тот же родительский класс, множественное наследование позволяет одному дочернему классу иметь несколько родительских классов одновременно). 

В итоге, наследование не стали включать как механизм в следующую версию языка -- Smalltalk-72, так как "его можно симулировать другими способами, используя уже готовые возможности языка, который повторял гибкость Lisp." Пример такой симуляции можно видеть в том, как методы относятся к объектам. Определение произвольного метода в Smalltalk можно написать как угодно. Так, метод print может ничего не выводить. Чтобы дать какие-то гарантии относительно ожидаемого поведения метода, можно инстанциировать класс "Method", назвать класс-экземпляр "Print", благодаря чему все экземпляры Print тоже будут методами. Изменять тело таких методов уже будет нельзя, но его можно будет расширять, добавляя действия помимо вывода информации. Это позволит защитить "значение" метода, разрешив добавлять реализации. Такой вид наследования был предложен Ларри Теслером для "экспертных систем" -- искуственного интеллекта еще в ранних 1970-х. 
## C++ в 1979-1991 гг.
> "Smalltalk подталкивает программистов на использование наследования как основным, если не единственным, способом организовывать код программы и организовывать классы в иерархии с общим корнем. В С++ классы являются типами данных, и наследование -- это не единственный способ организовать код программы."

Эта цитата принадлежит Бъярне Строуструпу, оригинальному автору языка С++. Он неоднократно говорил, что многие идеи для С++ подчерпнул из Simula, включая классы как пользовательские типы данных, наследование как способ выделять отношения между типами данных. И самое главное -- ООП тоже, по мнению Строуструпа, пришел в С++ из Simula -- первого объектно-ориентированного языка.

"У Бэкуса была хорошая идея: программы должны быть написаны для людей, а не для машин, в первую очередь. Так появился Fortran. Но с легкой руки его последователей эта идея зашла слишком далеко. Появились отдельные языки для бухгалтерии, для логистики, для науки. Сотни языков выстраивали концепции какой-то отдельно взятой области. В результате получился хаос: у них не было возможности обмениваться данными, не было возможности использовать несколько языков одновременно. Так продолжалось, пока не появился Кристен Найгард с языком Simula. Он позволил создавать свои собственные типы данных, свои собственные абстракции -- так появилось ООП."
### Влияние Simula на С++
Строуструп очень высоко оценивал вохможности языка Simula. Он впервые познакомился с языком во время работы над своей диссертацией, для которой он писал симуляции сетевых приложений. Так как Simula был языком для симуляций, она почти идеально подходила для целей Струструпа. Языковые концепции очень хорошо подходили к задачам, которые необходимо было решать. Классы позволяли создавать объекты, которые имитировали реальные сущности: "компьютер", "сетевое подключение", "пакет с данными" и т.п. Это делало код легко читаемым, в отличие от того, к чему Строуструп привык в других языках (он особенно выделял Паскаль как пример плохо спроектированного языка). Его также поразила экспрессивность ошибок в обращении к типам данных. Ошибка компиляции практически всегда указывала на недоработку в дизайне класса

К сожалению Simula был не без своих недостатков, главным из которых была производительность. Причем, как в ходе работы программы, так и во время компиляции. Например, перекомпиляция одного класса занимала больше времени, чем перекомпиляция всей программы целиком. Другой проблемой была проверка типов данных в ходе работы программы, а также сбор "мусора". По наблюдениям Строуструпа, 80% всего времени уходило на сбор мусора, даже если никакого мусора программа не производила.  

Этот опыт подтолкнул Строуструпа на создание своего собственного инструмента для программирования, который бы сохранил все положительные стороны Simula и исправил отрицательные моменты.

1. Такой инструмент должен помогать организовать код программы с помощью классов и иерархий классов, с помощью сопроцессовости и статической проверки типов данных. То есть, классы становились главным инструментом дизайна приложений.
2. Хороший инструмент производить программы с высокой степенью быстродействия. Скорость выполнения должна быть сопоставима с ассемблерными языками. Это касается и компиляции. Компиляция также должна поддерживать комбинирование подпрограмм, написанных на разных языках, в одну программу. 
3. Хороший инструмент производит портативные программы.
> "Мой личный опыт показал, что 'хорошая реализация' чего-то, что мне было нужно, всегда была недоступна 'до следующего года', а тогда -- только для компьютеров, которые я не мог себе позволить."

Из этого следовало, что хороший инструмент должен поддерживать множество различных компьютерных систем для общей доступности. 
### Основные возможности первой реализации С++ (1980-81)
1. Классы.
2. Подклассы (наследование). 
3. Доступ к полям классов (public/private).  
4. Конструкторы и деструкторы
5. Функции-декораторы (call/return, позже были убраны из языка).  
6. Дружественные классы (friend). 
7. Статическая проверка типов, статическое приведение типов аргументов.
8. Встраиваимые функции (inline). 
9. Аргументы по-умолчанию. 
10. Перегрузка оператора присваивания. 

Первая реализация С++ была всего лишь расширением языка С и называлась "С с классами". Строуструп написал парсер, который генерировал код на языке С. Этот код затем компилировался любым С-компилятором. Как заметил Строуструп,
> "Язык программирования служит двум целям: позволяет программисту описать действия, которые компьютер должен выполнить, при этом предоставляя программисту набор концепций для обдумывания способов решения поставленной задачи. Первая цель требует близкий к 'железу' язык, чтобы все важные аспекты реализации решались просто и быстро. За это отвечал язык С. Вторая цель требует язык, близкий к поставленной задаче по своей выразительности. Это было добавлено в язык С для создания С++.
## Наследование реализации и наследование интерфейса
В то время как Smalltalk рассматривает классы в качестве собрания операций, доступных их объектам, Simula и С++ видят классы как конкретный интерфейс, предоставляемый множеству объектов (экземпляров соответствующего подкласса). В результате класс в Smalltalk способен обрабатывать сообщения с операциями, которые он не поддерживает, в то время как С++ гарантирует пользователю, что компилятор позволит вызывать только те методы, определение которых присутствует в классе.

The derived class concept is C++'s version of Simula's prefixed class notion and thus a sibling of 
Smalltalk's subclass concept. The names derived class and base class were chosen because I never 
could remember what was sub and what was super and observed that I was not the only one with this 
particular problem. It was also noted that many people found it counterintuitive that a subclass 
typically has more information than its superclass. Even without virtual functions, derived classes in C with Classes were useful for building new data 
structures out of old ones and for associating operations with the resulting types. In the absence of virtual functions, a user could use objects of a derived class and treat base classes 
as implementation details (only). Alternatively, an explicit type field could be introduced in a base 
class and used together with explicit type casts.

Access is granted by declaring a function in the public part of a class declaration, or by specifying 
a function or a class as a friend. Initially, only classes could be friends, thus granting access to all 
member functions of the friend class, but later it was found convenient to be able to grant access 
(friendship) to individual functions. In particular, it was found useful to be able to grant access to 
global functions.

 If you want to inherit an implementation only, you 
use private derivation in C++. Public derivation gives users of the derived class access to the interface 
provided by the base class. Private derivation leaves the base as an implementation detail; even the 
public members of the private base class are inaccessible except through the interface explicitly 
provided for the derived class. To provide "semitransparent scopes" a mechanism was provided to 
allow individual public names from a private base class to be made public.

many features were considered that later appeared in C++ . These included virtual functions, static members, templates, and multiple inheritance. 
> All of these generalizations have their uses, but every "feature" of a language takes time and effort to design, 
implement, document, and learn .... The base class concept is an engineering compromise, like the C class 
concept.

The most unusual for its time--aspect of Cfront was that it generated C code. This has caused 
no end of confusion. Cfront generated C because I needed extreme portability for an initial imp|e- 
mentation and I considered C the most portable assembler around. I could easily have generated some 
internal back-end format or assembler from Cfront, but that was not what my users needed. No 
assembler or compiler back-end served more than maybe a quarter of my user community and there 
was no way that ! could produce the, say, six back-ends needed

The major additions to C with Classes introduced to produce C++ were: 
Virtual functions 
Function name and operator overloading 
References 
Constants (const) 
User-controlled free-store memory control 
Improved type checking 
In addition, the notion of call and return functions (Section 15.2.4.8) was dropped due to lack of use, 
and many minor details were changed to produce a cleaner language.

The most obvious new feature in C++, and certainly the one that had the greatest impact on the style 
of programming one could use for the language, was virtual functions. 
> "An abstract data type defines a sort of black box. Once it has been defined, it does not really interact with 
the rest of the program. There is no way of adapting it to new uses except by modifying its definition. This 
can lead to severe inflexibility.

References were introduced primarily to support operator overloading. C passes every function 
argument by value, and where passing an object by value would be inefficient or inappropriate the 
user can pass a pointer. This strategy doesn't work where operator overloading is used. In that case, 
notational convenience is essential so that a user cannot be expected to insert address-of operators if 
the objects are large. 

n operating systems, it is common to have access to some piece of memory controlled directly or 
indirectly by two bits: one that indicates whether a user can write to it and one that indicates whether 
a user can read it. This idea seemed to me directly applicable to C++ and I considered allowing every 
type to be specified readonly or writeonly

 [ had experimented further with const in C with Classes and found 
that const was a useful alternative to macros for representing constants only ifa global consts were 
implicitly local to their compilation unit. Only in that case could the compiler easily deduce that their 
value really didn't change and allow simple consts in constant evaluations and thus avoid allocating 
space for such constants and use them in constant expressions.

I found per-class allocators and deallocators very effective. The fundamental idea is that free store 
memory usage is dominated by the allocation and deallocation of lots of small objects from very few 
classes. Take over the allocation of those objects in a separate allocator and you can save both time 
and space for those objects and also reduce the amount of fragmentation of the general free store.

Another side of the compatibility issue was more critical: "In which ways must C++ differ from 
C to meet its fundamental goals?" and also "In which ways must C++ be compatible with C to meet 
its fundamental goals?" Both sides of the issue are important, and revisions were made in both 
directions during the transition from C with Classes to C++, shipped as release 1.0. Slowly and 
painfully an agreement emerged that there would be no gratuitous incompatibilities between C++ and 
ANSI C (when it became a standard) [Stroustrup 1986b], but that there was such a thing as an 
incompatibility that was not gratuitous. Naturally, the concept of "gratuitous incompatibilities" was 
a topic of much debate and took up a disproportional part of my time and effort. This principle has 
lately been known as "C++: As close to C as possible but no closer."

> 'Theory and tools more advanced than a blackboard have not been given much space in the description 
of the history of C++. ! tried to use YACC (an LALR(1 ) parser generator) for the grammar work, and 
was defeated by C's syntax (Section 15.2.4.5). I looked at denotational semantics, but was again 
defeated by quirks in C. 

> Object-oriented programming is programming using inheritance. Data abstraction is programming using 
user-defined types. With few exceptions, object-oriented programming can and ought to be a superset of data 
abstraction. These techniques need proper support to be effective. Data abstraction primarily needs support 
in the form of language features and object-oriented programming needs further support from a programming 
environment. To be general purpose, a language supporting data abstraction or object-oriented programming 
must enable effective use of traditional hardware. 

> a Simula or C++ class specifies a fixed interface to a set of objects (of any derived class) whereas a Smalltalk 
class specifies an initial set of operations for objects (of any subclass). In other words, a Smalltalk class is a 
minimal specification and the user is free to try operations not specified whereas a C++ class is an exact 
specification and the user is guaranteed that only operations specified in the class declaration will be accepted 
by the compiler. 

Things to add to C++:
1. Parametrized types.
2. Exceptions.
3. Multiple inheritance.

The main features of 2.0 were first presented in Stroustrup [1987c] and summarized in the revised 
version of that paper [Stroustrup ] 989b], which accompanied 2.0 as part of its documentation: 
1. multiple inheritance, 
2. type-safe linkage, 
3. better resolution of overloaded functions, 
4. recursive definition of assignment and initialization, 
5. better facilities for user-defined memory management, 
6. abstract classes, 
7. static member functions, 
8. const member functions, 
9. protected members (first provided in release 1.2), 
10. overloading of operator ->, and 
11. pointers to members (first provided in release 1.2). 

The original and fundamental reason for considering multiple inheritance was simply to allow two 
classes to be combined into one in such a way that objects of the resulting class would behave as 
objects of either base class

Basically, I rejected all forms of dynamic resolution beyond the use of virtual functions as 
unsuitable for a statically typed language under severe efficiency constraints. Maybe, I should at this 
point have revived the notion of cal 1 and return functions 

Multiple inheritance in C++ became controversial [Cargill 1991; Carroll 1991; Waldo 1991; 
Sakkinen 1992] for several reasons. The arguments against it centered around the real and imaginary 
complexity of the concept, the utility of the concept, and the impact of multiple inheritance on other 
extensions and tool building. In addition, proponents of multiple inheritance can, and do, argue over 
exactly what multiple inheritance is supposed to be and how it is best supported in a language. I think, 
as I did then, that the fundamental flaw in these arguments is that they take multiple inheritance far 
too seriously. Multiple inheritance doesn't solve all of your problems, but it doesn't need to because 
it is quite cheap, and sometimes it is very convenient to have. Grady Booth [Booch 1991 ] expresses 
a slightly stronger sentiment: "Multiple inheritance is like a parachute, you don't need it very often, 
but when you do it is essential."

A common complaint about C++ was (and is) that private data is visible and that when private data 
is changed then code using that class must be recompiled. Often this complaint is expressed as 
"abstract types in C++ aren't really abstract." What I hadn't realized was that many people thought 
that because they could put the representation of an object in the private section of a class declaration 
then they actually hadto put it there. This is clearly wrong (and that is how I failed to spot the problem 
for years). If you don't want a representation in a class, thus making the class an interface only, then 
you simply delay the specification of the representation to some derived class and define only virtual 
functions.

The importance of the abstract class concept is that it allows a cleaner separation between a user 
and an implementor than is possible without it. This limits the amount of recompilation necessary 
after a change and also the amount of information necessary to compile an average piece of code. 

> For many people, the largest single problem using C++ is the lack of an extensive standard library. A major 
problem in producing such a library is that C++ does not provide a sufficiently general facility for defining 
"container classes" such as lists, vectors, and associative arrays. 

There are two approaches for providing such classes/types: One can either rely on dynamic typing 
and inheritance, as Smalltalk does, or one can rely on static typing and a facility for arguments of type 
type. The former is very flexible, but carries a high run-time cost, and more importantly, defies attempts 
to use static type checking to catch interface errors. Therefore, the latter approach was chosen. 

The following assumptions were made for the design: 
• Exceptions are used primarily for error handling. 
• Exception handlers are rare compared to function definitions. 
• Exceptions occur infrequently compared to function calls. 
These assumptions, together with the requirement that C++ with exceptions should cooperate 
smoothly with languages without exceptions, such as C and FORTRAN, led to a design with multilevel 
propagation. The view is that not every function should be a firewall and that the best error-handling 
strategies are those where only designated major interfaces are concerned With nonlocal error handling 
issues. 

During the design, the most contentious issue turned out to be whether the exception handling 
mechanism should support termination semantics or resumption semantics; that is, whether it should 
be possible for an exception handler to require execution to resume from the point where the exception 
was thrown. The main resumption vs. termination debate took place in the ANSI C++ committee. 
After a discussion that lasted for about a year, the exception handling proposal as presented in the 
ARM (that is, with termination semantics) was voted into C++ by an overwhelming majority. The 
key to that consensus were presentations of experience data based on decades of use of systems that 
supported both resumption and termination semantics by representatives of DEC, Sun, Texas 
Instruments, IBM, and others. Basically, every use of resumption had represented a failure to keep 
separate levels of abstraction disjoint. 
