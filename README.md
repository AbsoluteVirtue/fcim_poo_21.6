# FCIM.POO21.6 -- Объектно-ориентированное программирование, вступительный курс


## Лекция 1, абстрактные типы данных
Прежде чем обсуждать историю и основные концепции, стоящие за понятием "объектно-ориентированный", необходимо вспомнить базовые принципы структурного или "дата-ориентированного" программирования. Язык С++ изначально разрабатывался как надмножество языка С с полной прямой совместимостью, в следствие чего многие нюансы работы с языком С плавно перешли в С++.

В качестве примера можно рассмотреть устройство массивов в языке С. Вспомним, что массив представляет собой переменную, содержащую адрес того байта, с которого начинается секция, выделенная под весь массив. В этом смысле массивы являются образом виртуальной памяти процесса, так как они полностью повторяют ее структуру: получить доступ к любому из байтов можно по известному адресу, который играет роль индекса. Используя арифметику указателей можно перейти на любой другой адрес, инкременировав или декрементировав указатель.

Отсюда следует, что массив не является типом данных в привычном понимании. Тип данных - это, в перую очередь, метод присвоения какого-то значения байтам в памяти компьютера (данным). Такое значение выражается в операциях, которые определены для этих данных, и свойствам, которые присущи этим данным. Массив не имеет свойств, присущих только ему, и операций, определенных только для него. Вместо этого массив подвержен операциям, определенным для указателей, и обладает свойствами указателей.

Так, для доступа к произвольному элементу массива достаточно обратиться к его указателю и прибавить нужное количество "скачков" от него в нужную сторону, после чего полученный таким образом адрес необходимо разыменовать.

    int a[10];
    int *p_in_a = a + 2; 
    int x_of_a = *p_in_a;

    // или 

    int x_of_a = *(a + 2); 

    // аналогично укороченной форме записи

    int x_of_a = a[2];

Единственной операцией здесь, которая ассоциируется непосредственно с массивами, является инициализация массива как сплошного блока памяти, равного 10 значениям типа int. Таким образом мы видим, что массивы в С -- это ссылки на уже существующие участки памяти, которые ассоциируются с конкретным именем при объявлении массива в программе. Статический массив полезен тем, что его размер известен компилятору (так как мы указываем его явно при инициализации). В случае с динамическим массивом эта информация компилятору не доступна, что делает массив аналогичным указателю соответствующего типа.

    int *a = (int *)malloc(sizeof(int) * 10);

И даже в случае со статическими массивами, при передаче их в функцию в качестве аргументов они "разлагаются" до обычных указателей, теряя информацию о своем первоначальном размере.

    unsigned int count(int a[10])
    {
        return sizeof(a) / sizeof(int);
        // вернет 2, так как размер переменной a будет равен размеру указателя (8 байтов)
        // а не размеру статического массива (40 байтов), т.о. 8/4 = 2.
    }

Такое поведение является следствием большого "возраста" языка С, который создавался во времена компьютеров, обладавших очень небольшим запасом оперативной памяти. Для экономии драгоценных байтов разработчики пошли на хитрость, сделав все аргументы-массивы такого же размера как аргументы-указатели. И это поведение сохраняется во всех компиляторах С++.

Теперь рассмотрим пример реализации массива в С++.

    #include <array>

    unsigned int count(std::array<int, 10> &a)
    {
        return sizeof(a) / sizeof(int);
    }

    std::array<int, 10> a;
    unsigned int len_of_a = count(a);

Здесь размер массива определится правильно -- 10 элементов. Это возможно благодаря двум свойствам. Первое свойство перекочевало из языка С. Оно относится к структурам данных (struct). Конкретней, состоит в том, что структуры передаются в функции как полноценные копии значений всех полей. Благодаря этому статические массивы, заключенные в структуру, копируются полностью, что позволяет определить их размер из структуры.

    struct c_struct
    {
        int v[10];
    };

    unsigned int count(c_struct a)
    {
        return sizeof(a.v) / sizeof(int);
    }

    c_struct a;
    unsigned int len_of_a = count(a);

Второе свойство заключается в том, что структуры позволяют создавать новые типы данных, которым можно задать определенное поведение с помощью методов, которые были добавлены в С++. Одним из таких инструментов является возможность определять функции внутри структур и скрывать данные структуры от внешнего доступа.

    struct cpp_struct
    {
        unsigned int count()
        {
            return sizeof(v) / sizeof(int);
        }
    private:
        int v[10];
    };

    unsigned int len_of_a = cpp_struct().count();

Здесь важно отметить тот факт, что функция вызывается через оператор-точку, как любое другое поле структуры. Такие функции называются "методами структуры" и имеют ряд полезных свойств, главным из которых является полный доступ к другим полям родительской структуры. 

Другой важный момент -- ключевое слово private, добавленное в С++ для запрета доступа к полям структуры извне. Это логическое следует из идеи "типа данных". Если мы создаем свой тип, он должен определять операции над собой и формулировать представление своих данных. Но если позволить внешнему коду изменять внутренние поля структуры в обход определенных им операций, нарушается целостность данных, нарушаются свойства типа, обязательные к соблюдению -- инварианты. отсюда и возникла необходимость скрывать поля структуры, давая возможность воздействовать на данные того или иного типа используя его методы, которые однозначно определяют условия изменения данных. Так ярлык private скрывает все поля, находящиеся непосредственно под ним. В противоположность ему ярлык public делает все поля под собой доступными извне.

    class cpp_struct 
    {
        int v[10];
    public:
        unsigned int count()
        {
            return sizeof(v) / sizeof(int);
        }
    };

Обратите внимание на использование ключевого слова class. Оно является аналогом struct в языке С, но с добавлением семантики уровней доступа. При использовании этого варианта для определения структуры все поля по умолчанию скрыты.

Таким образом структуры удобно использовать для реализации динамических массивов. Несмотря на то, что размер такого массива не определить через использование sizeof, для этих целей можно создать служебную переменную, скрытую от внешнего воздействия.

    class cpp_struct 
    {
        int *v;
        unsigned int length;
    public:
        unsigned int count()
        {
            return length;
        }
    };

В этом случае необходим метод, который задает определенные значения скрытым полям согласно определенным правилам.

    void cons(unsigned int n)
    {
        v = new int [n];
        length = n;
    }

Этот метод будет гарантировать правильность данных в обоих полях, так как устанавливает их значения одновременно на основе одного и того же аргумента. Это называется "состоянием" объекта -- значения внутренних полей инициализированной структуры в заданный момент времени. Суть скрытых полей заключается в сохранении состояния объекта и защиты от изменения состояния извне в обход правил, заданных его типом данных.

Единственным затруднением будет возможность вызова этого метода для одной и той же переменной несколько раз подряд.

    cpp_struct a;
    a.cons(5);
    a.cons(10);

Нетрудно заметить, что в таком случае информация о 5 элементах, созданных при первом вызове, будет утеряна -- заменена информацией о новых 10 элементах. Такая утечка памяти должна быть предвидена заранее.

    void cons(unsigned int n)
    {
        delete [] v;
        v = new int [n];
        length = n;
    }

Но есть более надежный способ добиться нужного эффекта -- "конструктор". Конструкторы типа -- это специализированные методы, которые вызываются при создании переменной заданного типа. Так как они вызываются не на переменную, а в момент ее создания, они обладают несколькими дополнительными свойствами. Во-первых они не могут иметь возвращаемое значение. Во-вторых, они не могут иметь произвольное имя. В-третьих, они не могут быть вызваны больше одного раза.

    class cpp_struct 
    {
        int *v;
        unsigned int length;
    public:
        unsigned int count()
        {
            return length;
        }

        cpp_struct(unsigned int n) : v(new int [n]), length(n) {}
    };

Выше показан пример конструктора, который заменяет функциональность метода cons. Обратите внимание на его имя (совпадает с именем родительской структуры), отсутствие возвращаемого типа данных, а также специальный синтаксис обращения к полям структуры (список инициализации позволяет вызывать конструкторы других типов). Благодаря этой особенности структур языка С++ становится возможным такое объявление переменной.

    cpp_struct a(10);
    unsigned int len_of_a = a.count();

Скобки явно указывают на вызов конструктора, который принимает целые числа в качестве аргумента. Причем, если бы структура этого конструктора не имела, компилятор бы синтезировал пустой конструктор самостоятельно, такой конструктор не принимает никаких аргументов и не устанавливает полям своей структуры никакие значения.

    cpp_struct() {}

Следовательно, переменная такого типа может быть инициализирована, но будет иметь неинициализированные внутренние поля, что для полей примитивных типов не так важно, но для указателей может иметь плохие последствия. Из-за этого поля внутри структуры принято инициализировать до вызова конструкторов.

    class cpp_struct 
    {
        int *v{nullptr};
        unsigned int length{0};
    };

Другим методом, который будет синтезирован компилятором в случае его отсутствия в структуре, является "деструктор". Деструкторы аналогичны "конструкторам по умолчанию", и вызываются при исчезновении переменной из программы (когда заканчивается область видимости, внутри которой переменная была объявлена). Компилятор синтезирует его в таком виде.

    ~cpp_struct() {}

При работе с динамически выделенной памятью оставлять деструктор без изменений не следует, потому что тело деструктора является лучшим местом для освобождения памяти, занимаемой объектом.

    ~cpp_struct()
    {
        delete [] v;
    }

Деструктор в структуре может быть только один, конструкторов может быть сколько угодно, при условии, что их списки аргументов отличаются. Это позволяет определить множество способов создания переменных заданного типа, которые будут присущи этому типу (так как они конструкторы определены внутри него), а также определить единственный правильный способ уничтожать переменные заданного типа. 

Пользователи такого типа освобождаются от необходимости создавать специальные функции для инициализации полей такой структуры и вручную освобождать память, которая для них выделяется конструкторами, что делает этот тип данных "абстрактным" (данные и операции над ними определены самим типом, и их конкретная реализация не нужна для пользования таким типом).


## Лекция 2, история возникновения термина "объектно-ориентированное программирование"
Термин "объектно-ориентированное программирование" тесно связан с такими языками, как <b>Java</b>, <b>C++</b> и даже <b>Python</b>. Но в период своего становления эта парадигма ассоциировалась совсем с другими языками и стилями программирования. В этой части мы попробуем понять как термин изначально возник, в чем была суть оригинальной идеи, и как термин постепенно вбирал в себя все новые и новые формы написания кода.

Объектно-ориентированное программирование не развивалось в вакууме. На него оказали влияние разные языки программирования и инструменты, разработчики которых в свое время стремились дать развитию своей индустрии мощный толчок. В контексте объектно-ориентированного программирования стоит особенно выделить следующие разработки.

Sketchpad (1963) -- одна из первых если не первая программа, которая позволяла взаимодействовать с системой, используя графический пользовательский интерфейс [1, Sutherland, I.E., Sketchpad: A man-machine graphical communication system, 2003, стр. 3]. Sketchpad оказала огромное влияние на все последующие графические программы, но графическая составляющая была не единственным ее достоинством. Программа использовала идею "плексов" -- предшественников абстрактных типов данных -- возникшую чуть ранее в работах Дагласа Росса[1, стр. 8]. Идея была дополнена засчет создания рекурсивных типов данных -- "экземпляров", которые позволяли расширять одни экземпляры засчет других[1, стр. 82]. Технически, экземпляр представляет собой (четырехмерный) вектор: набор из четырех переменных, хранящих данные о размере экземпляра, его повороте и его положении на экране. Экземпляры составляют "главное окно" (master picture), которое рисуется на экране, рекурсивно рисуя его экземпляры, каждый из которых тоже рисуется этим рекурсивным алгоритмом как "окна", до тех пор, пока не будет найдено окно, не содержащее ни одного экземпляра.

Другой важной идеей стала реализация "ограничений" -- математических условий, которые существуют для уже нарисованных частей окна, которые являются обязательными и будут автоматически удовлетворены системой для получения графических объектов нужной формы -- а вместе с ними и "методов", которые удовлетворяли требованиям ограничений[1, стр. 93]. "Типы ограничений" были блоками общего назначения (generic), содержащими свойства каждого конкретного типа. Такой блок отвечал за то, какие переменные входили в определение ограничения, какие из этих переменных можно изменять, сколько степеней свободы присуще каждой переменной, а также имя типа. Также были переменные, на которые можно было только ссылаться, но не изменять[1, стр. 94].

Эти свойства и блоки, их содержащие, позднее стали прототипом понятия "объект", которое через несколько лет стало использоваться в других языках программирования. Одним из первых таких языков стал язык Simula 67, написанный на основе ALGOL 60.

Simula (1967) -- изначально создаваемый как система для построения симуляций, основанная на "событиях"**, целью которой было простое описание комплексных социальных и индустриальных систем[2, Mitchell, J.C., "History of objects -- Simula and Smalltalk", Concepts in Programming Languages, Cambridge University Press, 2003, стр. 319]. Такая форма симуляции требовала для своей реализации составной тип данных, представляющий собой структуру-"очередь" (queue/priority queue). Рассмотрим следующий псевдо-код для примера:

    Q := создать_очередь(_событие):
    повторять
        достать следующее событие _e из Q
        симулировать событие _e
        занести все события сгенерированные в _e на Q
    пока Q не опустеет

Здесь используется процедура, которая должна работать для всех видов событий, создаваемых данной системой. Это указывает на необходимость системы определять тип события динамически. В типизированных системах типичным подходом для достижения этого является "наследование"[2, стр. 320]. Для реализации наследования (а также в следствие новой системы "конкурентных" вычислений -- возможности рассматривать процедуры не на одном стэке, а на нескольких одновременно) в язык были добавлены концепции объектов и классов[3, Nygaard, K., Dahl, O.-J., "The Development of the Simula Languages", History of Programming Languages, Academic, 1981].

В Simula 67 можно было сохранять структуру данных, которая включала в себя информацию о вызванной на стэке процедуре вместе с возвращаемым значением. На такую структуру можно было получить указатель. Процедура из такой структуры называлась "классом", а сама структура -- "объектом", экземпляром класса. Так как объект содержал указатели на код процедур, а также все локаьные переменные, с ними ассоциированные, он определял замкнутость***. Части класса также можно было переопределять в "подклассе", что являлось реализацией идеи наследования.

Ниже показан пример класса в Simula 67[2, стр. 324].

    class Point; real x, y;
    begin
        boolean procedure equals(p); ref(Point) p;
            if p =/= none then
                equals := abs(x - p.x) + abs(y - p.y) &lt; 0.00001;
        real procedure distance(p): ref(Point) p;
            if p == none then error else
                distance := sqrt((x - p.x)**2 + (y - p.y)**2);
    end Point
    p :- new Point(1.0, 2.5);

Нетрудно заметить, что пример выше местами очень сильно напоминает язык С++. Наверное, ни для кого из вас не будет удивительным то, что многие идеи, которые попали в первые версии С++ и в нем закрепились, были заимствованы из Simula 67. Но прежде чем перейти к истории возникновения языка С++, необзодимо остановиться еще на одном языке программирования.

Smalltalk (1971) -- считается первым действительно объектно-ориентированным языком****. И это имеет большое значение для обсуждения объектно-ориентированного программирования, потому что теперь вам надо каждый раз уточнять, что имеется ввиду под этим термином: идеи, возникшие до Smalltalk, которые перетекли в другие языки из Sketchpad и Simula; или идеи, которые были впервые постулированы в Smalltalk буквально как "объектно-ориентированный дизайн".

Основополагающей идеей, стоящей за объектами в Smalltalk является принцип "монады"[4, "Монада", Институт Философии Российской Академии Наук, 2018, https://iphlib.ru/library/collection/newphilenc/document/HASH019bdfeaf98c38848da2579b] -- любой алгоритм может быть описан рекурсивной композицией множества сущностей единого поведенческого вида, которые скрывают от алгоритма свои состояние и процессы, и с которыми можно взаимодействовать только через отправку им сообщений[5, Kay, A.C., "The Early History of Smalltalk", History of Programming Languages II, Association for Computing Machinery, 1996, стр. 513].

Если рассматривать весь язык на более высоком уровне абстракции, идея Smalltalk в том, чтобы представить каждый объект в программе как "абстрактный компьютер". Вместо того, чтобы разделять программу на компоненты, каждый из которых -- меньшая часть большего целого (процедуры, структуры данных и т.д.), каждый объект рекурсивно повторяет возможности всего компьютера. В такой системе от конкретного представления данных можно абстрагироваться полностью. В свою очередь, в идеальной системе это позволяет полностью отказаться от операции присваивания (мутации объектов напрямую самим пользователем).

На дизайн Smalltalk оказали большое влияние следующие языки. В перую очередь, Sketchpad -- с его системой сущностей: "главными окнами" и их дочерними окнами-экземплярами (см. выше). Во-вторых, Simula -- с его классами и объектами, который предоставлял более гибкий инструментарий для управления поведением объектов, чем "ограничения" в Sketchpad. В-третьих, LISP -- функциональный язык, построенный на рекурсивном комбинировании монадических сущностей, основанных на лямбда-выражениях[6, "Лямбда-исчисление", Вики-конспекты ИТМО, https://neerc.ifmo.ru/wiki/index.php?title=Лямбда-исчисление]. Примером того, что можно назвать самоописывающей системой является интерпретатор LISP, написанный на самом LISP.

Так, ниже представлен пример процедуры, написанной на LISP; процедура создает список на основе заданного списка x, с условием, что сначала в созданном списке будут идти элементы, находящиеся в нечетных позициях, а затем - в четных.

    oddsEvens(x) = append(odds(x), evens(x))
    where   odds(x)  =  if null(x) v null(tl(x)) then x
                        else hd(x) & odds(ttl(x))
            evens(x) =  if null(x) v null(tl(x)) then nil
                        else odds(tl(x))

В Smalltalk эту идею расширили на все объекты: каждый объект является интерпретатором сообщений, которые обрабатываются на основе конкретного синтаксиса, поглощая сообщения и отвечая только на те, которые написаны в понятной объекту форме. окончательной целью является рекурсивный дизайн программ, в которых каждая отдельная часть обладает всеми возможностями своего целого. Например, объекты поддерживаются в программе аналогично "корутинам" -- сопрограммам[7, Conway, M.E., "Design of a Separable Transition-Diagram Compiler", Communications of the ACM. Volume 6, Number 7, 1963, стр. 396]. Постоянные объекты (файлы и документы) рассматриваются как приостановленные процессы, циклы являются сопрограммами[5, стр. 520]. Так, для реализации генератора в виде цикла for, можно использовать оператор while и булевые проверки, которые проверяют поставляемые генератором данные, возвращая false, когда генератор ничего не возвращает. С помощью этого же механизма можно "склеить" несколько генераторов вместе:

    while i <= 1 to 30 by 2^j <= 2 to k by 3 do j <- j * i;

здесь to-by является сопрограммой. Другим примером является оператор when, являющийся аналогом системного прерывания, отвечающего на события в программе, которое строит бинарное дерево сортировки для более эффективной обработки условных операторов.

Таким образом, можно выделить несколько центральных принципов, которые легли в основу дизайна языка Smalltalk.
1. Все в программе является объектом.
2. Объекты взаимодействуют друг с другом путем отправки и приема сообщений, которые сформированы языком, понятным конкретному объекту.
3. Каждый объект имеет свою область памяти.
4. Каждый объект является экземпляром класса, каждый класс является объектом.
5. Класс описывает поведение, общее для всех своих экземпляров -- объектов в программе.
6. Выполнение инструкций программы имеет вид передачи контроля первому объекту, упоминаемому в сообщении, оставшаяся часть сообщения считается сообщением для этого объекта -- так до тех пор, пока все сообщение не будет "поглощено" объектами, упоминаемымы в нем.

Одним из главных направлений в дизайне был отказ от использования абстрактных типов данных (а также от связанного с ними создания переменных через присваивание) в пользу "целей": вместо того, чтобы позволять программистам изменять внутреннее состояние объекта, объекты представляются как высокоуровневые динамические компоненты программы, которые сами принимают решения как выполнять выполнять ту или иную инструкцию. Это требует абсолютной защиты состояния объекта от внешного воздействия (читай, полный отказ от "сеттеров" и "геттеров"). Результатом такого подхода является стратегия "позднего связывания" (тип объекта определяется в момент обращения к нему на основании формы сообщения), как следствие -- "полиморфизма" (обобщенного поведения объектов, которое зависит от символов в сообщении)[5, стр. 543].

Ниже представлен пример реализации простого класса в Smalltalk-72[8, Goldberg, A., Kay, A., "The Basic System Classes", Smalltalk-72 Instruction Manual, Xerox Palo Alto Research Center, 1976, стр. 61].

    to True | truthValue |
        (
            @ifTrue => (trueBlock (ifFalse (falseBlock (^trueBlock value))))!
            @ifFalse => (falseBlock (ifTrue (trueBlock (^trueBlock value))))!
            @ifTrue => (trueBlock (^trueBlock value))!
            @ifFalse => (falseBlock (^nil))!
            @not => (^false)!
            @& :aBoolean => (^aBoolean)!
            @| :aBoolean => (^true)!
            @eqv :aBoolean => (^aBoolean)!
            @xor :aBoolean => (^aBoolean not)!
            @and :aBlock => (^aBlock value)!
            @or :aBlock => (^true)!
            @printOn :aStream => (aStream nextPutAll :'true')!
        )!

Класс True объявляется как экземпляр класса Boolean, он имеет внутреннее состояние truthValue и список поддерживаемых методов*****. Каждый метод ассоциируется с определенным сообщением (сообщение отмечается символом @ -- "посмотреть"): например, в случае (=>) получения сообщения, начинающегося с термина or, необходимо посмотреть (@) в классе соответствующую строку ("or"), трактовать остаток сообщения как некий обобщенный блок aBlock и вызвать метод (^true), где символ ^ означает "вернуть". То есть, тело класса представляет собой "словарь" всех сообщений, которые класс может обработать, и методов обработки соответствующих сообщений.

Таким образом, класс сам решает: отвечать или не отвечать на сообщения -- в зависимости от того, как они сформулированы. Также класс сам решает, как именно ответить на каждое сообщение: если часть сообщения состоит из других объектов, выполнение метода приостанавливается, и остаток сообщения передается следующему в цепочке объекту, где оно также обрабатывается по аналогичной схеме.

Данная схема напоминает обмен сообщениями между компьютерами в сети. Неудивительно, что Алан Кей, один из авторов языка Smalltalk лучшим примером объектно-ориентированной системы считает сеть Интернет[9, Kay, A., комментарий к статье: Ben-Ari, M., "Objects Never? Well, Harly Ever!", Communications of the ACM, 2010, Volume 53, Number 9, стр. 32-35]. По его словам, "[Интернет] включает в себя миллиарды полностью инкапсулированных объектов (сами компьютеры) и использует "чистую" систему сообщений, состоящую из запросов, а не инструкций"******. Результатом такого подхода к созданию сложной системы является ее гибкость и резистентность. Если один или несколько компьютеров в сети внезапно перестанут существовать, сама сеть от этого не пострадает в такой мере, какая могла бы вызвать сбой всей системы. С момента ввода сети Интернет в работу ее ни разу не приходилось полностью выключать "на профилактику", при этом все составные компоненты системы были заменены не один раз.

Это и является основной целью объектно-ориентированной парадигмы в ее первоначальном представлении: предоставить инструменты для создания систем, состоящих из бесконечного количества самостоятельных сущностей, которые не могут быть изменены извне. Вместо привычных операций присваивания и статичного связывания (как инициализация переменных в языке С), используется отправка сообщений в классы через их экземпляры-объекты. Вам не приходит в голову возможность изменения данных на вашем компьютере по сети другим пользователем, когда ему заблагорассудится. Так же и здесь, изменять данные объекта из программы напрямую не следует, так как это чревато возникновением ситуаций, при которых состояние объекта перестает удовлетворять инвариантам класса, и объект становится источником ошибок.

Тем интересней наблюдать за развитием такого языка, как С++, потому что он считается одним из самых популярных объектно-ориентированных языков*******. Он также заимствовал идеи из Simula-67, но пошел по пути, отличному от того, по которому эволюционировал дизайн Smalltalk. Например, в Smalltalk изначально не было концепции наследования, потому что "в Simula [наследование] часто являлось источником кошмаров (слишком много возможностей, различных семантически********, из одного механизма)"[9]. В С++ наследование появилось практически сразу[10, Stroustrup, B., "A History of C++: 1979-1991", History of Programming Languages II, Association for Computing Machinery, 1996, стр. 703].

Чтобы понять, как объектно-ориентированное программирование выглядит через призму языка С++, необходимо рассмотреть первоначальные причины для его возникновения. Первая реализация не была полноценным самостоятельным языком, а всего лишь расширением, написанным для языка С. Задача расширения заключалась в том, чтобы позволить писать сопрограммы в С, используя экспрессивность, присущую коду Simula-67. Конкретно, в язык были добавлены возможность создавать иерархии классов (наследование) и возможность включать в классы функции (методы).

Изначально Строуструп, оригинальный автор языка С++, работал над симуляциями распределенных систем, которые он писал в Simula, и многие механизмы языка идеально для этого подходили. Классы позволяли переносить абстракции в код в том виде, в каком Строуструп их моделировал, сохраняя все связи[9, стр. 700]. Это делало текст программы легко читаемым, замысел программиста явно просматривался в самом коде, что в 1979 году было непривычным. Классы в Simula являлись сопрограммами, что позволяло легко писать независимые друг от друга модули в виде классов и моделировать сетевые связи между ними, "один объект класса "компьютьер" легко мог работать параллельно с другими объектами этого класса"[9, там же].
Иерархии классов описывали различные вариации одной концепции и т.п.. 

Система типов Simula позволяла рано обнаруживать ошибки в дизайне, так как любая ошибка в применении классов указывала либо на плохую концепцию изначально, либо на явную ошибку самого программиста. Эта особенность убедила Строуструпа в том, что модель, которую предлагает язык Simula, имеет большой потенциал[9, стр. 701]. Еще одним неожиданным открытием стало то, что структура программы, написанной на Simula, не страдала по мере увеличения объема написанного кода. В процедурных языках большие программы очень тяжело анализировать, так как они написаны в виде последовательных инструкций. Разбиение программы на классы позволяло инкапсулировать данные и код в соответствующем классе и обращаться к классу, который бы выполнял нужные инструкции неявно. Этот подход схож с тем, как объекты используются в Smalltalk.

Тем не менее, Строуструп столкнулся с проблемой производительности: на компьютере, к которому у него на тот момент был доступ, его программа обрабатывалась настолько долго, что на запуск непосредственных симуляций времени не хватало. Как утрвеждает Строуструп, в первую очередь в этом был виноват механизм автоматической очистки памяти компьютера в ходе работы программы (garbage collector)[9, там же]. Переписав всю симуляцию на более производительном языке Строуструп понял, что для его целей нужен язык, который совместит в себе экспрессивность Simula и скорость таких языков, как BCPL. Таким образом он выработал несколько требований к своему "языку будущего"[9, там же].

1. Инструменты для органиации кода в программе должны поддерживать: сопрограммы, классы, иерархии классов, статическую систему типов, построенную вокруг классов.
2. Сборка и выполнение программ должны выполняться очень быстро, сравнимо с тем, как это происходит в BCPL, C, языках assembly, ALGOL 68 и т.п..
3. Программы должны быть легко переносимыми: работать правильно независимо от того, на какой системе или на каком оборудовании их запускают.

Работая над проектом по построению распределенной операционной системы на базе UNIX, Строуструп столкнулся с необходимостью работать на языке С[9, стр. 702]. Первое, что он сделал для проекта -- написал расширение для С в виде классов как в Simula, согласно критериям описанным выше. Чуть позже на базе этого расширения была написана библиотека для работы с сопрограммами, что стало первым модулем будущего языка С++.

Так как базовый С отвечал за производительность, С++ должен был решить другую проблему -- проблему организации кода в программах. Причем, инструменты для такой организации в идеале не должны были отрицательно влиять на производительность. Например, классы строились на основе структур из С, поэтому в них не содержалось никакой дополнительной информации кроме той, которую в них помещал программист.

Минусом такого подхода стало то, что элементы дизайна С, которые не подходили новому языку из соображений дизайна, необходимо было оставлять в новом языке без изменений для совместимости программ, написанных на С, с новым языком[9, стр. 703]. Но для самых "опасных" механизмов (неявного приведения типов) были сделаны условия, при которых программист может сделать их явными (например, с помощью static_cast).

Строуструп не считал эту версию языка объектно-ориентированной, несмотря на то, что в языке уже было наследование, методы, перегрузка операторов (заимствована из ALGOL 68), возможность скрывать данные с помощью ключевого слова private и т.д.. По его мнению, первая объектно-ориентированная часть была добавлена в язык в 1983 году с реализацие виртуальных функций[9, стр. 704]. Без виртуальных функций пользователям приходилось обязательно создавать иерархию из двух классов и намеренно не использовать в программе базовый класс, а только дочерние, оставляя базовый класс как описание всех доступных операций (интерфейс). Другим подходом было хранение специального поля для указания на тип данных внутри класса, чтобы можно было приводить типы данных один у другому явно внутри класса для эмуляции полиморфизма[9, стр. 712]. В последствии первый подход заменили на виртуальные функции, а второй - на шаблоны типов данных. Ниже приведен пример обоих подходов. 

    enum kind { circle, triangle, square };

    class shape {
        point center;
        color col;
        kind k; // необходимо дополнительное поле для конкретизации того, какой это вид фигуры
    public:
        void draw();
        // реализация открытых методов здесь
    };

    void shape::draw() {
        switch(k) {
            case circle:
                // логика, которая рисует круг
                break;
            case triangle:
                // логика, которая рисует треугольник
                break;
            case square:
                // логика, которая рисует квадрат
        }
    }

Как видно из примера, методы класса должны знать о всех существующих в их среде видах фигур. Если добавляется новая фигура, методы тоже необходиом изменять. Чтобы это исправить можно использовать наследование и виртуальные функции.

    class shape {
        point center;
        color col;
        // дополнительное поле не нужно
    public:
        virtual void draw();
        // реализация открытых методов здесь
    };

    class circle : shape {
        int radius;
    public:
        void draw () {
            // логика, которая рисует круг
        }
    }

    void draw_all(shape** v, int size) {
        for (int i = 0; i &lt; size; ++i)
            v[i].draw(); // эта строка заранее не указывает какой именно фигуре принадлежит метод
    }

Все сказанное выше уже должно было создать у вас впечатление того, как Строуструп понимал объектно-ориентированное программирование. По его же собственным словам, "объектно-ориентированное программирование -- это программирование через наследование. Абстракция данных -- это программирование через типы данных, созданные самими пользователями. Таким образом, за редким исключением, объектно-ориентированное программирование должно быть надмножеством абстрактных типов данных"[9, стр. 730]. Более того, Строуструп подчеркивал, что, "в то время как Smalltalk видит классы как собрание операций, доступных их объектам, Simula и С++ видят классы как конкретный интерфейс, предоставляемый множеству объектов (экземпляров соотв. подкласса), в результате класс в Smalltalk способен обрабатывать сообщения с операциями, которые он не поддерживает, в то время как С++ гарантирует пользователю, что компилятор позволит вызывать только те методы, определение которых присутствует в классе"[9, там же].

Так становится очевидным фундаментальное расхождение во мнениях двух дизайнеров о том, что именно является объектно-ориентированным программированием. Строуструп особо подчеркивает, что не согласен с подходом к дизайну классов, используемому в Smalltalk. Загвоздка только в том, что сам термин "объектно-ориентированное программирование" как раз и означает то, как это делается в Smalltalk. Тем не менее, мы с вами не будем вдаваться в детали перипетий сторонников того и другого подходов, а сконцентрируемся на том, какие последствия для реализации программ эти подходы в себе несут.
