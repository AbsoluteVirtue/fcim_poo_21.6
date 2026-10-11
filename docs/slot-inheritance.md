# What is slot inheritance?
Alan Kay, April, 2002, https://lists.squeak.org/archives/list/squeak-dev@lists.squeakfoundation.org/thread/HEZT34YIILGPABVBH2WMZDMGT3POONH6/#576OLUMIQJX6RYCLOBJOUDUSR55N24OD

In Smalltalk-72, variables were theoretically objects, and thus required quoting in order to do assignment. So:
- `'a`          meant give me the symbol `a`. BTW `'` is an actual object in Smalltalk-72
- `a`           meant give me the value that is associated with the symbol `a`, the symbol `a` would look itself up in the current context to find the value
- `'a <- foo`   meant send the message `<- foo` to the symbol `a` which would look itself up in current context and store the value
- `a  <- foo`   meant send the message `<- foo` to the object associated with the symbol `a`

In retrospect, it might have been a better idea to use the opposite convention instead of one that worked like LISP--so a symbol would be a literal (like a number), and there would have been a message to get the value associated with it. But maybe not...

Also, a number of inheritance ideas were tried out in Smalltalk-72, none of which I liked all that much. My favorite were the "slot inheritance" experiments that were done by Larry Tesler.

> As I understand it that was a precursor of delegation a la Lieberman and then Self and so on: inheritance goes via the slots instead of via the class.--Henrik Gedenryd

Slot inheritance was invented for AI and other reasoning systems--and also for providing protection of polymorphic meanings. One of the ways of looking at it is that for many objects, the contents of the instance variables can be thought of as "parts". Thus, one could imagine a lookup strategy that would search down through the instance variables for ideas and info about the object.

An example might be to deal with the question "how heavy?" the idea might be to look at the slot called `material` and ask the actual value for help. It could in turn ask its variables for help, etc. So this gives a dynamic way to enlarge the property space of an object. If you include the static superclass chain in the mix of searched variables, then you get regular inheritance. This is one of the many inheritance strategies used in CYC.
      
Another view of this is to consider the polymorphic meaning of `print` in Smalltalk. There is no protection of the generic meaning, any programmer can write whatever they want in a method. However, we could make a subclass of class `Method` called `Print` whose instances are `Print-Method`s. These would not allow arbitrary code to be written in them, but might have places where programmers could add useful idiosyncratic information. All of these `print` methods would really try to print something. So slot classes and *slot inheritance allow real definitions and protections of meanings*. This idea also goes back to the early 70s.

All these were easy to do in ST-72 because each class/closure/instance really got passed control *before* the message was received. There were some suggestions that a `prereceive` method be allowed in ST-76 and -80--if present, a flag would be set somewhere efficient, and it would be called first with the actual message put in a place where it could be received later. This would have allowed all of these schemes, delegation, etc, to also be done in the later versions of ST. 

Someone on the list might want to figure out good ways to do these schemes in Squeak. Folks like Nathanial Scharli and Stephane Ducasse, who are playing with metasystems, should add these kinds of considerations into their play.
