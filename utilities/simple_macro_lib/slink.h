#ifndef $cap($myclass)_H
#define $cap($myclass)_H

/* explain file $myclass.h
 * Description:
 *   single linked list template
 *
 * Author: Thomas Wang
 * http://www.concentric.net/~ttwang/macro/uuSlink.h
 * History:
 * (ID)   (name)   (date)    (bug#)      (message)
 * 000TW  Thomas   07/01/93  0000-00000  Sample msg
 */


class $myclass; // forward declaration


#include <stddef.h>


$if($inc,
#include <$inc>
)
$if($inc2,
#include <$inc2>
)
$if($inc3,
#include <$inc3>
)


/* explain class $myclass
 * The $myclass data structure consists of an data item of
 * type $T, and the 'next' pointer. 
 *
 * If the data item is of pointer type, deleting a linked list node
 * will NOT cause the data item pointer to be deleted.  In any
 * case, it is not safe to delete the pointer, as it may be shared.
 */
class $myclass // from template class uuSlink
{
  public:

    typedef $T value_type;

  protected:
    value_type data_item;  /* the data item in node */
    $myclass *the_next;  /* the next pointer */

  public:
    value_type & Item();
    $myclass*& Next();
    $myclass* Reverse();

    $myclass();
    $myclass(const $myclass&);
    $myclass(value_type);
    $myclass(value_type, $myclass*);

    $myclass& operator = (const $myclass& cpy);
};


/* explain function
 * Description:
 *   Default constructor
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass()
  : the_next(NULL)
{
}


/* explain function
 * Description:
 *   Copy constructor
 *
 * Parameters:
 *   cpy - node to be copied
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass(const $myclass& cpy)
  : data_item(cpy.data_item), the_next(cpy.the_next)
{
}


/* explain function
 * Description:
 *   Constructor with a data value
 *
 * Parameters:
 *   obj - data value of the node
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass(value_type obj)
  : data_item(obj), the_next(NULL)
{
}


/* explain function
 * Description:
 *   Constructor with a data value, and next pointer.
 *
 * Parameters:
 *   obj      - data value of the node
 *   next_ptr - next pointer value
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass(value_type obj,$myclass* next_ptr)
  : data_item(obj), the_next(next_ptr)
{
}


/* explain function
 * Description:
 *   Item() would return the content of the linked list node.
 *
 * Parameters: none
 *
 * Return Value: content of linked list node
 *
 * Assumes: none
 */
inline $myclass::value_type& $myclass::Item()
{
  return this->data_item;
}


/* explain function
 * Description:
 *   Next() would return the next uuSlink node.
 *
 * Parameters: none
 *
 * Return Value: next uuSlink node
 *
 * Assumes: none
 */
inline $myclass*& $myclass::Next()
{
  return this->the_next;
}

#endif
