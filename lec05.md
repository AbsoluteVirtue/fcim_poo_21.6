# Наследование
## Наследование в Smalltalk 76
    Class new title: 'Window'; 
        fields= 'frame'; 
        asFollows!
    Scheduling 
    startup
        [frame contains: stylus => 
            self enter.
            repeat:
                [frame contains: stylus loc => 
                    [keybard active => [self keyboard]
                    stylus down => [self pendown]] 
                self outside => []
                stylus down => [^self leave]]]
            ^false]
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
        flelds= 'document scrollbar edit Menu'; 
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
    title [^document title]

Simula-67 added 
inheritance as a generalization to the ALGOL-60 block structure. This was a great idea. But it did 
have some drawbacks: minor ones, like name clashes in multiple threaded lists (no one uses threaded 
lists anymore), and major ones, like a rigidity in the extended type structures, a need to qualify types, 
only a single path of inheritance, and difficulty in adapting to an interactive development system with 
incremental compiling and other needs for instant changes.

Not all useful 
questions could be answered by following a static chain. Some of them required a kind of"inheritance" 
or "inferencing" through dynamically bound "parts" (that is, instance variables). Multiple inheritance 
also looked important.

Because things can be done with a dynamic language that are difficult with a 
statically compiled one, I just decided to leave inheritance out as a feature in Smalitalk-72, knowing 
that we could simulate it back using Smalltalk's LISPlike flexibility. The biggest contributer to these 
AI ideas was Larry Tesler, who used what is now called "slot inheritance" extensively in his various 
versions of early desktop publishing systems. Nowadays, this would be called a "delegation-style" 
inheritance scheme [Lieberman].

Dan Ingalls had come up with a scheme that was Simula-like 
in its semantics but could be incrementally changed on the fly to be in accord with our goals of close 
interaction. I was not completely thrilled with it because it seemed that we needed a better theory 
about inheritance entirely (and still do). For example, inheritance and instancing (which is a kind of 
inheritance) muddles both pragmatics (such as factoring code to save space) and semantics (used for 
way too many tasks such as: specialization, generalization, speciation, and so forth).

## C++ в 1979-1991 гг.
The features of 
Simula were almost ideal for the purpose and I was particularly impressed by the way the concepts 
of the language helped me think about the problems in my application. The class concept allowed me 
to map my application concepts into the language constructs in a direct way, that made my code more 
readable than I had seen in any other language.

During writing and initial debugging, I acquired a great respect for the expressiveness of Simula's 
type system and the ability of its compiler's ability to catch type errors. The observation was that a 
type error almost invariably reflected either a silly programming error or a conceptual flaw in the design. In contrast, I had found Pascal's type system worse than 
useless--a strait jacket that caused more problems than it solved by forcing me to warp my designs 
to suit an implementation-oriented artifact.

SIMULA's link times for separately compiled classes were abysmal: It 
took longer to compile 1/30th of the program and link it to a precompiled version of the rest than it 
took to compile and link the program as a monolith.  The cost 
arose from several language features and their interactions: run-time type checking, guaranteed 
initialization of variables, concurrency support, and garbage collection of both user-allocated objects 
and procedure activation records. For example, measurements showed that more than 80 percent of 
the time was spent in the garbage collector despite the fact that resource management was part of the 
simulated system so that no garbage was ever produced. 

1. 
A good tool would have Simula's support for program organization--that is, classes, some 
form of class hierarchies, some form of support for concurrency, and strong (that is, static) 
checking of a type system based on classes. This I saw as support for the process of inventing 
programs, as support for design rather than just support for implementation. 
2. A good tool would produce programs that ran as fast as BCPL programs and shared BCPL's 
ability to easily combine separately compiled units into a program. A simple linkage convention is essential for combining units written in languages such as C, ALGOL 68, FORTRAN, BCPL, 
assembler, and so on, into a single program and, thus, not to get caught by inherent limitations 
in a single language. 
3. A good tool should also allow for highly portable implementations. My experience was that 
the "good" implementation I needed would typically not be available until "next year" and only 
on a machine I couldn't afford. This implied that a tool must have multiple sources of 
implementations (no monopoly would be sufficiently responsive to users of "unusual" ma- 
chines and to poor graduate students), that there should be no complicated run-time support 
system to port, and that there should be only very limited integration between the tool and its 
host operating system. 

The features provided in the initial 1980 implementation can be summarized: 
1. classes 
2. derived classes 
3. public/private access control 
4. constructors and destructors 
5. call and return functions (Section 15.2.4.8) 
6. friend classes 
7. type checking and conversion of function arguments 
During 1981 three more features were added: 
8. inline functions 
9. default arguments 
10. overloading of the assignment operator 

People had made data members public to avoid the function call overhead incurred by 
a constructor for simple classes where only one or two assignments are needed for initialization. The 
immediate cause for the inclusion of inline functions into C with Classes was a project that couldn't 
afford function call overhead for some classes involved in real-time processing.

I 
have no recollection of discussions, no design notes, and no recollection of any implementation 
problems about the introduction of static ("strong") type checking into C with Classes. The C with 
Classes syntax and rules, the ones subsequently adopted for the ANSI C standard, simply appeared 
fully formed in the first C with Classes implementation.

Another early attempt to tighten C with Classes' type rules was to disallow "information destroy- 
ing" implicit conversions. Like others, I had been badly bitten by implicit long to :i.nt and 5.nt to 
char conversions. I decided to try to ban all implicit conversions that were not value preserving; that 
is, to require an explicit conversion operator wherever a larger object was stored into a smaller. The 
experiment failed miserably. Every C program I looked at contained large numbers of assignments 
of :i.nts to char variables.

> A programming language serves two related purposes: it provides a vehicle for the programmer to specify 
actions to be executed and a set of concepts for the programmer to use when thinking about what can be done. 
The first aspect ideally requires a language that is "close to the machine," so that all important aspects of a 
machine are handled simply and efficiently in a way that is reasonably obvious to the programmer. The C 
language was primarily designed with this in mind. The second aspect ideally requires a language that is 
"close tO the problem to be solved" so that the concepts of a solution can be expressed directly and concisely. 
The facilities added to C to create C++ were primarily designed with this in mind. 

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
