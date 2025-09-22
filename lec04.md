# Язык Smalltalk
Smalltalk is a recursion on the notion of computer itself. Instead of dividing
"computer stuff' into things each less strong than the whole--such as data structures, procedures, 
and functions that are the usual paraphernalia of programming languages--each Smalltaik object is 
a recursion of the entire possibilities of the computer. Thus its semantics are a bit like having thousands and thousands of computers all hooked together by a very fast network. Questions of concrete 
representation can thus be postponed almost indefinitely because we are mainly concerned that the 
computers behave appropriately, and are interested in particular strategies only if the results are off or come back too slowly.

Smalltalk is a recursion on the notion of computer itself. Instead of dividing "computer stuff" into things each less strong than the whole--such as data structures, procedures, and functions that are the usual paraphernalia of programming languages--each Smalltalk object is a recursion of the entire possibilities of the computer. Questions of concrete representation can thus be postponed almost indefinitely because we are mainly concerned that the computers behave appropriately, and are interested in particular strategies only if the results are off or come back too slowly.

OOP's two motivations:
1. Find a better module scheme for complex systems involving hiding of details.
2. Find a more flexible version of assignment, and then to try to eliminate it altogether.

1961: the Burroughs 220 had no standard operating systems or file formats, the designer (D.T. Ross?) decided to finesse the problem by taking each file and dividing it into three parts. The third 
part was all the actual data records of arbitrary size and 
format. The second part contained the B220 procedures 
that knew how to get at records and fields to copy and 
update the third part. And the first part was an array of 
relative pointers into entry points of the procedures in the 
second part (the initial pointers were in a standard order 
representing standard meanings). Needless to say, this was 
a great idea, and was used in many subsequent systems until the enforced use of COBOL drove it out of existence.

One of the interesting features of NLS was that its user interface was parametric and could be 
supplied by the end-user in the form of a "grammar of interaction" given in their compiler-compiler 
TreeMeta. This was similar to William Newman's early "Reaction Handler" work in specifying 
interfaces by having the end-user or developer construct through tablet and stylus an iconic regular 
expression grammar with action procedures at the states (NLS allowed embeddings via its context-free 
rules). This was attractive in many ways, particularly William's scheme, but to me there was a 
monstrous bug in this approach. Namely, these grammars forced the user to be in a system state that 
required getting out of before any new kind of interaction could be done. In hierarchical menus or 
"screens" one would have to backtrack to a master state in order to go somewhere else. What seemed 
to be required were states in which there was a transition arrow to every other state--not a fruitful 
concept in formal grammar theory. In other words, a much "flatter" interface seemed called for.

Object references were handled on the FLEX machine as a generalization of B5000 descriptors. 
Instead of a few formats for referencing numbers, arrays, and procedures, a FLEX descriptor contained 
two pointers: the first to the "master" of the object, and the second to the object instance (later we 
realized that we should put the master pointer in the instance to save space). A different method was 
taken for handling generalized assignment. The B5000 used i-values and r-values which 
worked for some cases but could not handle more complex objects. For example: a[55] : = 0, if a was 
a sparse array whose default element was 0 would still generate an element in the array because := is 
an "operator" and a[55] is dereferenced into an 1-value before anyone gets to see that the r-value is 
the default element, regardless of whether a is an array or a procedure fronting for an array. What is 
needed is something like: a(55, ':= ', 0), which can look at all relevant operands before any store is 
made. In other words, := is not an operator, but a kind of an index that can select a behavior from a 
complex object.

> “Objects are a kind of mapping whose values are its behaviors.”

As in Simula, a coroutining control structure [Conway 1963] was used as a way to suspend and 
resume objects. Persistent objects such as files and documents were treated as suspended processes 
and were organized according to their ALGOL-like static variable scopes. These were shown on the 
screen and could be opened by pointing at them. Coroutining was also used as a control structure for 
looping. A single operator while was used to test the generators which returned false when unable to 
furnish a new value. Booleans were used to link multiple generators. So a "for-type" loop would be 
written as:
    while i <= 1 to 30 by 2 ^ j <= 2 to k by 3 do j<- j * i; 

where the ... to ... by... was a kind of coroutine object. 

Another control structure of interest in FLEX was a kind of event-driven "soft interrupt" called 
when. Its Boolean expression was compiled into a "tournament sort" tree that cached all possible intermediate results. The relevant variables were threaded through all of the sorting trees in all of the 
whens so that any change only had to compute through the necessary parts of the Booleans. The 
efficiency was very high and was similar to the techniques now used for spreadsheets. it was 
a complex task to control the context of just when the whens should be sensitive. Part of the Boolean 
expression had to be used to check the contexts, where I felt that somehow the structure of the program 
should be able to set and unset the event drivers.

IMP, a system that had already been working for several years and was more elegant than 
most of the nonworking proposals. The basic idea of IMP was that you could use any phrase in the 
grammar as a procedure heading and write a semantic definition in terms of the language as extended 
so far (1970). I realized that the bridge to an object-based 
system could be in terms of each object as a syntax-directed interpreter of messages sent to it. In one 
fell swoop this would unify object-oriented semantics with the ideal of a completely extensible 
language. The mental image was one of separate computers sending requests to other computers that 
had to be accepted and understood by the receivers before anything could happen. In today's terms, 
every object would be a server offering services whose deployment and discretion depended entirely 
on the server's notion of relationship with the servee.

LISP  was supposed to be based on functions, but its 
most important components--such as iambda expressions, quotes, and conds--were not functions at 
all, and instead were called special forms. Landin and others had been able to get quotes and conds 
in terms of lambda by tricks that were variously clever and useful, but the flaw remained in the jewel. 
In the practical language things were better. There were not just EXPRS (which evaluated their 
arguments), but FEXPRS (which did not). My next question was, why on earth call it a functional 
language? Why not just base everything on FEXPRS and force evaluation on the receiving side when 
needed?

Allen Newell and IPL-V anecdote:
    oddsEvens (x) = append (odds (x), evens (x)) 
    where odds(x) = If null(x) v null(tl(x)) then x 
        else hd(x) & odds(ttl(x)) 
        evens(x) = if null(x) v null(tl(x)) then nil 
        else odds(tl(x)) 

This characteristic of writing 
down many solutions in declarative 
form and have them also be the pro- 
grams is part of the appeal and beauty 
of this kind of language.  It brought home to me once 
again that "point of view is worth 80 
IQ points." I wasn't smarter but I had 
a much better internal thinking tool 
to amplify my abilities.

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