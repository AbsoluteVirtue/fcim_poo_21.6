# Что значит "объектно-ориентированный"?
Если поискать информацию о термине "объектно-ориентированный" в произвольных открытых источниках, в большинстве случаев приводится пример "трех китов ООП":
* инкапсуляция;
* наследованиеж;
* полиморфизм.

Эпиграфом может служить цитата известного дизайнера Грэди Буча, взятая из книги "Object-Oriented Analysis, Design and Implementation".

> "Язык считается объектным, если он напрямую поддерживает абстракцию данных и классы. Объектный язык является объектно-ориентированным, если он поддерживает наследование и полиморфизм."

Возможно, именно отсюда и пошла традиция привязывать три этих явления к ООП. Данный курс попытается доказать, что ни один из этих элементов не является критической частью ООП в отдельности. 

Инкапсуляция в Smalltalk (первом официально "объектно-ориентированном" языке) - это результат неправильных выводов, сделанных Аланом Кеем под влиянием дизайна Sketchpad (где инкапсуляции не было) и языка Simula (где она носила схематичный характер, о чем речь пойдет ниже).

Наследование никогда не было составной частью ООП, и даже в языке С++ от наследования какой-то общей структуры ушли к наследованию общего поведения через интерфейсы, а в итоге от него отказались в пользу статического полиморфизма. Тем не менее, наследование заслуживает более подробного рассмотрения, так как первоначально широко применялось в Smalltalk, в последствии оказавшись ненужным.

Полиморфизм - это свойство системы типов, которое само собой не подталкивает использовать объекты, скорее, являясь инструментом к достижению высокой степени обобщенности в коде. Полиморфизму будет посвящена отдельная глава. 

Начать стоит с изучения двух базовых элементов, о которых говорит Буч в своей книге: абстрактных данных и классов. И не только потому, что эти понятия сейчас тесно связаны с ООП. Алан Кей пользовался этими механизмами во время работы над языком Smalltalk, что требует их более внимательного рассмотрения.

В середине 1960х годов Кей работал в новой команде разработки, где ему порекомендовали ознакомиться с двумя на тот момент новыми примерами инновационного использования компьютерных технологий. Первой технологией была система компьютерного дизайна Sketchpad Айвана Сазерленда, которая стала одной из самых значимых работ в сфере компьютерных технологий. Второй был язык программирования Simula, использующий новую концепцию "классов как процессов" в качестве основного инструмента организации кода.

Зная о том, что в группе по разработке языка Algol высказывались идеи об использовании "абстрактных типов данных" (которые условно были названы PLEX Дагласом Россом, о ком подробней будет сказано далее), Кей попытался объединить идею "плексов" из Algol, классов из Simula и обощенных структур данных из Sketchpad.

Общая идея системы, над которой он работал, заключалась в создании сети компьютерных процессов, которая не позволяет процессам напрямую изменять состояния друг-друга. Вместо этого процессы должны были отправлять друг другу запросы в виде правильно сформированных сообщений. Так, для изменения какого-то значения один процесс посылал сообщение с новым значением другому процессу, который отвечал за данную область памяти. Процесс-получатель читал сообщение и принимал окончательное решение о том, нужно ли изменять значение в памяти или нет. Это позволяло программисту, работающему в такой системе, вместо простых инструкций с присваиванием значений отдельным переменным писать более абстрактные инструкции, описывающие желаемый окончательный результат. Процессы же сами должны были выбирать правильные инструкции для достижения результата.

## Объекты
Эта концепция появилась не на пустом месте. Кей был биологом по первому образованию и часто обращался к билогии за вдохновением. Для своей системы он выбрал поведение биологических клеток, которые защищены от внешнего мира мембраной, но могут обмениваться информацией с другими клетками с помощью специальных белков и соответствующих рецепторов. Кею эта модель нравилась тем, что систему, построенную по такому принципу, можно расширять до бесконечности, получая результат любой сложности (по аналогии с тем, как из одних и тех же клеток с помощью ДНК получаются разные организмы).

Кей предполагал, что и в компьютерных системах возможно создание программы любой сложности из обобщенных процессов, которые работают каждый по своим правилам, отвечают каждый за свою зону ответственности и взаимодействуют друг с другом согласно определенным протоколам. Прототипом такой системы стал Интернет, к разработке которого Кей тоже приложил свою руку. Если рассматривать процессы как отдельные компьютеры, объединенные в компьютерную сеть, в таком сценарии компьютеры могут взаимодействовать друг с другом только посредством отправки сообщений другим компьютерам, оставаясь независимыми вычислительными объектами, данные которых скрыты от остальных компьютеров в одной с ними сети. Таким образом компьютеры инкапсулируют данные в памяти и вычислительный процесс, а объединение таких процессов в общую сеть позволяет умножать их вычислительные возможности.

Это привело Алана Кея к простой модели, согласно которой могла быть написана любая компьютерная программа:
* базовой исполняющей сущностью является вычислительный процесс;
* процесс создает и поддерживает операции над сегментами данных в памяти;
* операции поддерживают параллельное исполнение;
* процессы должны отвечать на события (где событие - event - понимается как действие, распознаваемое в системе, происходящее асинхронно основному выполнению программы, которое может быть как-то программой обработано в ответ на соответствующий сигнал от системы);
* и т.д.

Кей называл свои процессы "объектами", откуда и пошел термин "объектно-ориентированное программирование". Поэтому данный курс будет использовать следующее определение объекта в дальнейшем.

Объект - это описание вычислительного процесса или семейства процессов, которое скрывает свои данные от внешней среды и может работать независимо от других объектов, взаимодействуя с ними с помощью сообщений, отправленных согласно какому-то протоколу.

Далее будут рассмотрены более подробно три главных примера, которые использовал в своей работе Алан Кей: абстрактные типы данных, классы и обобщенные структуры данных.

## Sketchpad – a man-machine graphical communication system
Чтобы в полной мере оценить важность Sketchpad для ООП, надо отметить, что Алан Кей называл эту работу "наверное, самой значимой дипломной работой в истории". Стоит только добавить, что Кей также называл Sketchpad первой "объектно-ориентированной" системой. Несколько свойств Sketchpad были напрямую переняты в Smalltalk, для того, чтобы он мог быть по-настоящему объектно-ориентированным языком.

### Master - instance
В Sketchpad дизайнер оперировал световым пером для того, чтобы создавать на экране компьютера чертежи. Чертежи организовывались в иерархию, в которой была главный чертеж (master drawing), изменения которого отражались на всеъ копиях главного чертежа. Копии или "экземпляры" (instances) создавались на основе главного чертежа, повторяя все его свойства, причем изменения одной копии никак не отражались на остальных элементах чертежа. Экземпляры можно было использовать для создания новых "рекурсивных" иерархий любой степени вложенности. Этот принцип позже лег в основу иерархий наследования, которые создавались в Smalltalk.

### Constraints
Между фигурами на чертежах устанавливались определенные отношения. Например, можно было обозначить две линии отдельной фигуры параллельными, чтобы независимо от последующих манипуляций (повороты, уменьшение, увеличение экземпляров) это свойство гарантированно сохранялось. За сохранение таких отношений - атомарных ограничений - отвечал отдельный процесс.

За управление объектами, своевременное и правильное применение процедур к ним и т.п. отвечал процесс "разрешения ограничений", который решал динамическую задачу, когда задача по манипуляции фигурой ставилась действиями пользователя. То есть, пользователю нет необходимости явно задавать все шаги, нужные для правильного поворота экземпляра, достаточно просто обозначить свое намерение посредством интерфейса программы, и "решатель" запускал все нужные процедуры в правильной последовательности. Такая "непроцедурная" система описания программ стала одним из самых ранних примеров декларативного программирования.

### Абстрактный тип данных
В системе Sketchpad была определена иерархия - "вселенная" - возможных объектов: скаляров, точек в системе координат, строк текста и т.д. Возможные ограничения тоже формировали одну ветку данной иерархии. Все элементы данной иерархии описывались структурами данных в памяти программы. Все они имели общие свойства, но также каждый тип объекта имел уникальные свойства, которые отличали его от других типов объектов. Так, все структуры содержали поле "тип", для динамического определения типа текущего экземпляра; поле "имя" позволяло называть экземпляры; поле "вид" обозначало характер отображения; поле "дисплей" хранило процедуру ("подпрограмму") для отображения экземпляра; поле "движение" определяло процедуру для трансформаций на экране и т.д. Таким образом, в одной записи в памяти инкапсулировались и данные, и возможные операции над этими данными. 

Алан Кей понимал, что такой подход является хорошей моделью для его системы независимых объектов, которые можно комбинировать в любой конфигурации. На его вопрос Сазерленду: как тому удалось сделать первую интерактивную графическую программу, первый декларативный язык программирования и первую объектно-ориентированную систему - Сазерленд отвечал, что он просто тогда не знал, что это сложно.

Несмотря на это, у Sketchpad было одно свойство, которое Алан Кей не стал переносить в свою систему. Как он позже объяснял:

> "Еще одной важной системой, созданной в этот период, была Thinglab Алана Борнинга - первая серьезная попытка пойти дальше, чем Sketchpad. Алан придумал красивый подход к решению задач с ограничениями, в котором разрешающий процесс не обязан был быть всезнающим (т.е. не требовал знать состояние всей системы в каждый момент времени)."

Это важное замечание, которое дает представление о том, что Алан Кей считал критичным для дизайна объектно-ориентированных систем. Сокрытие данных было одним таким критичным свойством. Оно позволяло полностью отказаться от операций присваивания в языке и, как следствие, мотивировать программиста мыслить о программах в новой парадигме.

## SIMULA - Monte Carlo simulation language
Initial ideas based on a mathematically formulated discrete event network (1962).

Algol 60 used as the preprocessor for SIMULA I.

New storage management scheme developed for SIMULA I on Algol 60 and inclusion of "process" as the main encapsulation mechanism (1964).

SIMULA I compiler implemented (1964-65).
1. System consists of a finite number of "stations" (active components) and a finite variable number of "customers" (passive components).

        system <identifier> := <station list>

        station <identifier>;<statement>

        customer <customer list>
    
where elements of the list are:

        <identifier>(<list of characteristics>)[<upper limit of customers>] 

2. Station consists of a queue and a service (its actions form its "operating rule" and are described with Algol statements). 
3. Customer consists of variables named "characteristics".
4. Real number variables exist for all customers - named "time". Function called "position" also is defined for all customers.
5. Customer is generated by a service at a station, is transferred to that or other station's queue, then from the queue to the service of the respective station. Customers disappear from the system if they aren't transferred to any station's queue.
6. Services' actions are considered "instantly running" at discrete points in time.
7. Keywords "accept", "select", "if", "none", "hold", "route-to" describes the nodes of the network and the interconnections.
8. Process queues are represented by ordered sets (manipulated by "wait" and "include" statements) => processes were data carriers, replacing customer-objects.

Sets are similar to Hoare's condition variables, with SIMULA's wait/incite pair of operators being similar to Hoare's wait/signal.

Eventually sets were allowed to contain processes of different kinds, process pointers were introduced for that. With that the "network" concept disappeared, replaced by processes as the basic unifying concept.

    inspect <process reference>
        when passenger do
        when staff do
        otherwise
And the "incite" operator was also replaced:

    activate <process reference>
To quote OJD, "SIMULA should be problem-oriented and not computer-oriented, even if it implies an appreciable increase in the amount of work which has to be done by the computer."

The system became a variable collection of interacting processes - "each process being present in the program execution, the simulation, as an Algol stack."

The Algol stack proved to be hard to work with, in part due to the parallel nature of the system's process execution model. A new storage system was designed, based on a two-dimensional free area list (an allocation table). This prompted the evolution of processes from simple data structures to quasi-parallel Algol programs.

To implement built-in lists an abstract ordered set was included as a data type, in the form of a two-way circular list. The abstract aspect was desirable to enable processes to be members of abitrarily many sets at the same time. This was achieved by having "element objects" represent processes in different sets - through element pointers.

Two main lessons were:
1. The program text and execution are distinct, with execution being the dynamic instance of program text.
2. Data and operations belong together, and most useful program constructs contain both.

Another interesting side-effect was the fact that SIMULA because a powerful list processing language. 

Remote attribute accessing had to be redone, Hoare's record class idea was considered instead - full access security could be obtained in constructs like X.A by compile-time reference qualification. This was combined with run-time referencing via record subclasses.

Preprogramming the common properties of propcesses was viewed as beneficial, because structurally different processes often shared common properties in data attributes and actions. Parametrization wasn't flexible enough (mostly due to named parameters for processes didn't exist, for good reasons). This gave rise to the idea of subclasses.

Lisp's compacting garbage collector was used instead of reference counting when going from SIMULA I to SIMULA 67. This also included "constructor" and "destructor" actions for processes.

The class/subclass approach required:
1. subclasses of processes with own actions and local data stacks (closures?).
2. grouping together common process properties in such a way that they could be applied later, in a variety of different situations not necessarily known in advance.

Subclasses were implemented in terms of "prefixes" and "links": a two-layer system of a prefix layer containing a successor and a predecessor, coupled with the two-way list in the second layer. At this point the term "process" is replaced with "object".

Finally, to combat the limitations of the Algol block and the inability to name process parameters due to security reasons, a virtual quantity (class) concept was introduced to provie access to actions. The actual parameter is declared in the object at a deeper subclass level, while the virtual specification remains at the top level. Thus, generalized objects could be defined with their behavior pattern left partly unspecified in a prefix class body. Different subclasses could contain different procedure declarations. Unfortunately, due to Algol's parameter specifications, virtual procedure parameters had to be run-time checked.

