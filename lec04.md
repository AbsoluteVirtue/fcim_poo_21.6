# Smalltalk и инкапсуляция в ООП
## Источники вдохновения
Алан Кей указывал на Sketchpad, SIMULA и LISP как на основные системы, с которых он брал пример при разработке концепции ООП. Но в большой статье, посвященной истории языка Smalltalk, он упоминает менее известные примеры технологий, которые, тем не менее, также оказали на его подход к дизайну компьютерных систем большое влияние.

## Работа над FLEX
В 1961 году Алан Кей работал программистом на департамент обороны США перед тем как начать работать над своими собственными системами в университете Юты. Он отвечал за работу компьютеров системы Burroughs 220. На этих компьютерах не было операционной системы, и программисты должны были работать с памятью и файлами напрямую. Кто-то из предшественников Алана Кея на должности программиста написал свою файловую систему для этих компьютеров. Она разделяла все файлы на три части:
* структуры данных произвольного размера и формата;
* процедуры, доступные на Burroughs 220 "из коробки", которые могли обновлять данные в структурах;
* массив указателей на процедуры, описанные во второй части.
Дословно,
> "Очевидно, что это была отличная идея, которая использовалась во многих последующих системах до тех пор, пока всех не заставили перейти на COBOL и не похоронили ее."

Тут может броситься в глаза два интересных момента:
1. Точно такая же система использовалась в Sketchpad для описания "мастера" экземпляров.
2. Похожая идея использовалась в SIMULA 67 для развития концепции процесса и окончательного варианта с классами.

Эту идею Алан Кей принес с собой в университет Юты, куда его пригласили на позицию аспиранта. Первым его заданием стало прочитать диссертацию Сазерленда о Sketchpad, а вторым -- разобраться, почему копия компилятора Algol, которая лежала в департаменте, не запускалась на местных компьютерах. При ближайшем рассмотрении оказалось, что это вовсе не Algol, а какой-то никому не известный язык SIMULA, написанный на базе Algol. Таким образом, основные представления об организации процессов в компьютерных программах сложились под влиянием этих трех систем. Под впечатлением от Sketchpad, а также от статьи Гордона Мура, в которой появилось предсказание о темпах роста производительности компьютеров (см. "Закон Мура"), Алан Кей принял решение разработать концепцию персонального компьютера. Для этого нужно было разработать собственный язык, который воплощает новые идеи, подчерпнутые из других работ, в жизнь в новой парадигме.
### Объектно-ориентированный подход
> "Новая парадигма разработки для решения сложных проблем профессиональными программистами и для решения простых проблем новичками. Объектно-ориентированный дизайн -- это удачная попытка качественно улучшить эффективность процесса моделирования сложных динамических систем и пользовательских отношений с этими системами, которые стали возможны благодаря кремниевому взрыву."

Главными мотивационными факторами для разработки этой парадигмы были:
1. Необходимость в лучшей схеме для поддержания модульности сложных систем посредством скрытия деталей реализации.
2. Необходимость в более гибкой версии присваивания, которую впоследствии можно вовсе убрать. 

Важность сокрытия деталей реализации для ООП станет понятна позднее. Важность отсутствия операции присваивания уже упоминалась в статье Джона Бакуса, где подчеркивалась природа присваивания "по одному слову за раз" как негативный аспект в "традиционных" языках программирования. Алан Кей видел в присваивании и другие недостатки. 

Так, присваивание должно быть обобщенной операцией. Компьютеры до распространения ООП в основном оперировали значениями двух видов: l-lvalue ("левосторонние") и r-value ("правосторонние") -- где первая буква обозначает отношение значения к оператору присваивания. Такое разделение делает выражения очень ограниченными, так как не все выражения могут быть левыми операндами присваивания. Для объектов, которые Алан Кей задумывал реализовать в рамках своей системы, такое присваивание не подходило.

В качестве примера он приводит простое выражение:

    a[55] := 0
где имя "а" означает массив. Проблема такой записи в том, что даже если в массиве уже по заданному индексу есть значение "0", оператор присваивания все равно его вынужден заменить на тот же "0". Это произойдет потому, что оператор "[]" должен сначала разыменовать область памяти и вернуть значение по ссылке, так как оператор ":=" требует слева от себя l-value. Было бы лучше в таком случае использовать другую форму выражения: 

    a(55, ':= ', 0)
которая может предварительно проверить все операнды перед тем, как обращаться по ссылке и изменять значение в памяти. То есть, по замыслу Алана Кея запись ":=" должна быть не оператором, а индексом в таблице возможных процедур, описывающих поведение объекта.

В итоге, Алан Кей взял лучшие решения из Burroughs (мастер-версия объекта и ее экземпляры, которые ссылались на мастер указателями), SIMULA (класс и его экземпляры, организованные в иерархию "префикс-подкласс", процессы как сопрограммы), Sketchpad (абстрактные типы данных и инкапсуляция) для своей системы FLEX.

    while i <= 1 to 30 by 2 ^ j <= 2 to k by 3 do j<- j * i;
Выше показан пример кода FLEX, где в качестве цикла выступает процесс, который можно при желании приостановить, чтобы потом продолжить с той же инструкции ("генератор"). Это было возможно благодаря организации программ в комбинацию подпрограмм, которые могли быть независимыми друг от друга, аналогично подходу, который использовался в SIMULA. Сопрограммы FLEX были аналогами "объектов" в SIMULA. 
> “Объекты являются чем-то сродни соответствию между множеством объектов и множеством поведений объектов.”

Еще одной малоизвестной системой была IMP, идея которой залючалась в создании специальных формальных грамматик, где каждая "фраза" могла играть роль процедуры, семантиеское определение которой можно было написать в рамках других определений, доступных на том этапе. Алан Кей увидел в этом возможный "мост" между "процедурными" и "объектными" системами: каждый объект мог быть синтаксическим интерпретатором сообщений, которые ему посылаются. Благодаря этой одной идее можно было получить бескончено расширяемый язык, аналогично формальным грамматикам.

Чтобы более четко себе представить такую систему, можно посомтреть на компьютерную сеть, где одни компьютеры отправляют другим компьютерам запросы. Чтобы правильно обработать запрос и ответить на него, адресат должен понимать сообщение в запросе. По аналогии объекты в "объектном" языке могли играть роль "сервера", который предоставляет услуги другим объектам. Объект сам определял: предоставлять услугу или нет -- в зависимости от установленных отношений между адресатом и адресантом.
### Влияние Lisp на ООП
Семантика языка Lisp полностью основывалась на идее функций как объектов, но самыми важными компонентами были не функции, а λ-выражения, "ленивые" символы и условные операторы ("специальные формы"). Причем, последние два были выражены в языке посредством λ-выражений. Специальные формы были реализованы в виде FEXPR -- пользовательских функций, которые не вычисляли значения своих аргументов (для высокой производительности). Обычные же функции (встроенные и пользовательские) были реализованы в виде EXPR -- они вычисляли значения аргументов при вызове. Алан Кей считал такую двойственность дефектом языка, который в остальных аспектах был близок к идеалу. Он считал, что весь язык надо было бы базировать на идее FEXPR -- "ленивых" функциональных форм.

Несмотря на это, Алан Кей часто пользовался языком Lisp. Существует анекдот о событии, с этим связанным, произошедшим в ходе одной из конференций. Ален Ньюэлл, разработчик нового языка IPL-V делал презентацию своего детища, пытаясь убедить других участников переходить на этот язык. Ему предложили доказать полезность языка, решив простую задачу: для произвольного списка целых чисел передвинуть все нечетные в начало списка, а все четные в конец списка. Задачу нужно было решить за время, которое потребуется участникам для подписания протокола встречи. Ньюэлл возился с решением больше 30 минут. Алан Кей, который присутствовал на встрече, предложил решение, написанное на Lisp за 5 минут:

    oddsEvens (x) = append (odds (x), evens (x)) 
        where odds(x) = if null(x) or null(tl(x)) then x 
              else hd(x) and odds(ttl(x)) 
              evens(x) = if null(x) or null(tl(x)) then nil 
              else odds(tl(x))

Как он потом говорил,
> "Характеристика языка, позволяющая писать решения задач в декларативной форме, при этом оставаясь полноценными программами, является очень привлекательной и элегантной частью языков такого рода. Я в очередной раз убедился, что 'точка зрения стоит 80 очков интеллекта.' Я не был умнее в той ситуации, но у меня был намного лучший инструмент для организации мыслей, который усиливал мои возможности."
### Влияние SIMULA на ООП
Сокрытие деталей реализации (то, как объекты были реализованы с SIMULA 67). 

> "От SIMULA я заимствовал идею заменить связывание значений параметров и присваивание значений переменным на "цели". Худшее, что можно разрешить программисту -- это ковыряться во внутреннем состоянии объекта, даже если состояние представлено абстрактно. Вместо этого объекты должны быть представлениями высокоуровневого поведения, которые удобно использовать в качестве динамических компонентов."  

Smalltalk is a recursion on the notion of computer itself. Instead of dividing "computer stuff" into things each less strong than the whole--such as data structures, procedures, and functions that are the usual paraphernalia of programming languages--each Smalltalk object is a recursion of the entire possibilities of the computer. Questions of concrete representation can thus be postponed almost indefinitely because we are mainly concerned that the computers behave appropriately, and are interested in particular strategies only if the results are off or come back too slowly.

This Smalltalk language (today labeled -71) was very influenced by FLEX, PLANNER, LOGO, 
META II, and my own derivatives from them. It was a kind of parser with object-attachment that 
executed tokens directly. (I think the awkward quoting conventions came from META.) I was less 
interested in programs as algebraic patterns than I was in a clear scheme that could handle a variety 
of styles of programming. The patterned front-end allowed simple extension, patterns as "data" to be 
retrieved, a simple way to attach behaviors to objects, and a rudimentary but clear expression of its 
eval in terms that I thought children could understand after a few years experience with simpler 
programming. Program storage was sorted into a discrimination net and evaluation was straightfor- 
ward pattern-matching.
    to T 'and' :y do 'y' 
    to F 'and' :y do F
    
    to 'factorial' 0 is 1 
    to 'factorial' :n do 'n'factorial n-l'

    to 'fact' :n do 'to 'fact' n do factorial n. ^ fact n'
    
    to :e 'is-member-of [] do F 
    to :e 'is-member-of :group 
        do 'if e = first of group then T 
            else e is-member-of rest of group'

 how objects could be characterized as 
universal computers without having to have any exceptions in the central metaphor. What seemed to 
be needed was complete control over what was passed in a message send; in particular, when and in 
what environment did expressions get evaluated? An elegant approach was suggested in a CMU thesis of Dave Fisher [Fisher ! 970] on the synthesis 
of control structures. ALGOL60 required a separate link for dynamic subroutine linking and for access 
to static global state. Fisher showed how a generalization of these links could be used to simulate a 
wide variety of control environments. One of the ways to solve the "funarg problem" of LISP is to 
associate the proper global state link with expressions and functions that are to be evaluated later so that the free variables referenced are the ones that were actually implied by the static form of the language. The notion of "lazy evaluation" is anticipated here as well. 
Nowadays this approach would be called reflective design.

1. Everything is an object 
2. Objects communicate by sending 
and receiving messages (in terms 
of objects) 
3. Objects have their own memory 
(in terms of objects) 
4. Every object is an instance of a 
class (which must be an object) 
5. The class holds the shared 
behavior for its instances (in 
the form of objects in a program 
list)
6. To eval a program list, control 
is passed to the first object 
and the remainder is treated as 
its message

This led to a style of finding generic behaviors for message symbols. "Polymorphism" is the 
official term (I believe derived from Strachey), but it is not really apt as its original meaning applied 
only to functions that could take more than one type of argument. Because control is passed to the class before any of the rest of the message is considered---the class 
can decide not to receive at its discretion----complete protection is retained. Smalltalk-72 objects are 
"shiny" and impervious to attack.

Smalltalk-72 classes looked like and could be used as functions, but it was easy to 
produce an instance (a kind of closure) by using the object ISNEW. Thus factorial could be written 
"extensionally" as: 
    to fact n (^if :n=O then 1 else n'fact n-l) 

or "intensionally", as part of class integer: 
    (... *! >> (^:n=0 >> (1)(n-1)!) )
    
Of course, the whole idea of Smalltalk (and OOP in general) is to define everything intensionally. 
And this was the direction of movement as we learned how to program in the new style. 