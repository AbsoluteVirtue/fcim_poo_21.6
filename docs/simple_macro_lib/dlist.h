#ifndef $cap($dlist)_H
#define $cap($dlist)_H

/* explain file $dlist.h
 * Description:
 *   Double linked list template
 *
 * Author: Thomas Wang
 * http://www.concentric.net/~ttwang/macro/uuDlist.h
 * History:
 * (ID)   (name)   (date)    (bug#)      (message)
 * 000TW  Thomas   09/30/96  0000-00000  Sample msg
 */


class $dlink; // forward declaration

class $dlist; // forward declaration


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


/* explain class $dlink
 * The $dlink data structure consists of an data item of
 * type $T, a 'next' pointer and a 'previous' pointer. 
 *
 * If the data item is of pointer type, deleting a linked list node
 * will NOT cause the data item pointer to be deleted.  In any
 * case, it is not safe to delete the pointer, as it may be shared.
 */
class $dlink // from template class dlink
{
  public:
    typedef $T value_type;

  protected:
    $dlink* the_next;  /* the next pointer */
    $dlink* the_prev;  /* the previous pointer */
    value_type data_item;  /* the data item in node */

  public:
    const value_type & Item() const;
    value_type & Item();
    $dlink* const & Next() const;
    $dlink* const & Prev() const;
    int IsOutsideList() const;
    int IsHeadNode() const;
    int IsTailNode() const;
    $dlink* Dequeue();
    void InsertNext($dlink* const inserted_node);
    void InsertPrev($dlink* const inserted_node);

    $dlink();
    $dlink(const $dlink &);
    $dlink(value_type);
    $dlink(value_type, $dlink *, $dlink *);
    $dlink($dlink *, $dlink *);
    $dlink & operator = (const $dlink & cpy);
    virtual ~$dlink();

$if($classinc,
#include <$classinc>
)

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
inline $dlink::$dlink()
  : the_next(NULL), the_prev(NULL)
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
inline $dlink::$dlink(const $dlink & cpy)
  : data_item(cpy.data_item), the_next(cpy.the_next), the_prev(cpy.the_prev)
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
inline $dlink::$dlink(value_type obj)
  : data_item(obj), the_next(NULL), the_prev(NULL)
{
}


/* explain function
 * Description:
 *   Constructor with prev pointer, and next pointer
 *
 * Parameters:
 *   prev_ptr - previous pointer value
 *   next_ptr - next pointer value
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $dlink::$dlink($dlink* prev_ptr, $dlink* next_ptr)
  : the_next(next_ptr), the_prev(prev_ptr)
{
}


/* explain function
 * Description:
 *   Constructor with a data value, previous pointer, and next pointer.
 *
 * Parameters:
 *   obj      - data value of the node
 *   prev_ptr - previous pointer value
 *   next_ptr - next pointer value
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $dlink::$dlink(
  value_type obj
 ,$dlink* prev_ptr
 ,$dlink* next_ptr)
  : data_item(obj), the_next(next_ptr), the_prev(prev_ptr)
{
}


/* explain function
 * Description:
 *   IsOutsideList() would return true if the node is outside a
 *   list.  FALSE would be returned otherwise.
 *
 * Parameters: none
 *
 * Return Value: TRUE if outside, FALSE if inside
 *
 * Assumes: none
 */
inline int $dlink::IsOutsideList() const
{
  return (this->the_next == NULL) && (this->the_prev == NULL);
}


/* explain function
 * Description:
 *   IsHeadNode() would return true if the node is the head node
 *   of a list.  FALSE would be returned otherwise.
 *
 * Parameters: none
 *
 * Return Value: TRUE if node is head node, FALSE if inside
 *
 * Assumes: none
 */
inline int $dlink::IsHeadNode() const
{
  return this->the_prev == NULL;
}


/* explain function
 * Description:
 *   IsTailNode() would return true if the node is the tail node
 *   of a list.  FALSE would be returned otherwise.
 *
 * Parameters: none
 *
 * Return Value: TRUE if node is tail node, FALSE if inside
 *
 * Assumes: none
 */
inline int $dlink::IsTailNode() const
{
  return this->the_next == NULL;
}


/* explain function
 * Description:
 *   Item() would return the content of the linked list node.
 *   This is the const version.
 *
 * Parameters: none
 *
 * Return Value: content of linked list node
 *
 * Assumes: none
 */
inline const value_type& $dlink::Item() const
{
  return this->data_item;
}


/* explain function
 * Description:
 *   Item() would return the content of the linked list node.
 *   This is the non-const version.
 *
 * Parameters: none
 *
 * Return Value: content of linked list node
 *
 * Assumes: none
 */
inline value_type& $dlink::Item()
{
  return this->data_item;
}


/* explain function
 * Description:
 *   Next() would return the next double linked node.
 *
 * Parameters: none
 *
 * Return Value: next dlink node
 *
 * Assumes: none
 */
inline $dlink* const & $dlink::Next() const
{
  return this->the_next;
}


/* explain function
 * Description:
 *   Prev() would return the previous double linked node.
 *
 * Parameters: none
 *
 * Return Value: previous dlink node
 *
 * Assumes: none
 */
inline $dlink* const & $dlink::Prev() const
{
  return this->the_prev;
}


/* explain class $dlist
 * The $dlist data structure represents a double linked list.  Items of
 * type $T are stored in the linked list.
 *
 * If the data item is of pointer type, deleting a linked list node
 * will NOT cause the data item pointer to be deleted.  In any
 * case, it is not safe to delete the pointer, as it may be shared.
 */
class $dlist // from template class dlist
{
  public:
    typedef $T value_type;

  protected:
    $dlink head_node;
    $dlink tail_node;

  public:
    char IsEmpty() const;
    size_t Length() const;

    $dlink* First() const;
    $dlink* Last() const;

    void InsertFirst($dlink* const inserted_node);
    void InsertLast($dlink* const inserted_node);

    $dlink* RemoveFirst();
    $dlink* RemoveLast();

    $dlist();
    virtual ~$dlist();
    $dlist(const $dlist &);

    $dlist & operator = (const $dlist & cpy);
};


/* explain function
 * Description:
 *   IsEmpty() would return TRUE if the linked list is empty.
 *   FALSE will be returned otherwise.
 *
 * Parameters: none
 *
 * Return Value:
 *   TRUE if empty, FALSE if not empty
 *
 * Assumes: none
 */
inline char $dlist::IsEmpty() const
{
  return this->head_node.Next() == &(this->tail_node);
}


/* explain function
 * Description:
 *   First() would return the first element stored in the linked list.
 *   If the list is empty, the tail linked list node will be returned.
 *
 * Parameters: none
 *
 * Return Value: pointer to first node
 *
 * Assumes: none
 */
inline $dlink* $dlist::First() const
{
  return this->head_node.Next();
}


/* explain function
 * Description:
 *   Last() would return the last element stored in the linked list.
 *   If the list is empty, the head linked list node will be returned.
 *
 * Parameters: none
 *
 * Return Value: pointer to last element node
 *
 * Assumes: none
 */
inline $dlink* $dlist::Last() const
{
  return this->tail_node.Prev();
}


/* explain function
 * Description:
 *   RemoveFirst() would remove the first element from the
 *   linked list, and return the removed node.
 *
 * Parameters: none
 *
 * Return Value: pointer to removed node
 *
 * Assumes: linked list is not empty
 */
inline $dlink* $dlist::RemoveFirst()
{
  return this->head_node.Next()->Dequeue();
}

 
/* explain function
 * Description:
 *   RemoveLast() would remove the last element from the
 *   linked list, and return the removed node.
 *
 * Parameters: none
 *
 * Return Value: pointer to removed node
 *
 * Assumes: linked list is not empty
 */
inline $dlink* $dlist::RemoveLast()
{
  return this->tail_node.Prev()->Dequeue();
}


/* explain function
 * Description:
 *   InsertFirst() would insert a linked list node in the front of
 *   the double linked list.
 *
 * Parameters:
 *   inserted_node - the linked list node to be inserted
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline void $dlist::InsertFirst($dlink* const inserted_node)
{
  this->head_node.InsertNext(inserted_node);
}


/* explain function
 * Description:
 *   InsertLast() would insert a linked list node in the last
 *   position of the double linked list.
 *
 * Parameters:
 *   inserted_node - the linked list node to be inserted
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline void $dlist::InsertLast($dlink* const inserted_node)
{
  this->tail_node.InsertPrev(inserted_node);
}

#endif
