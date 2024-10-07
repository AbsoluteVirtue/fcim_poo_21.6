
/*
 * Description:
 *   double linked list template implementation file
 *
 * Author: Thomas Wang
 * http://www.concentric.net/~ttwang/macro/uuDlist.cc
 * History:
 * (ID)   (name)   (date)    (bug#)      (message)
 * 000TW  Thomas   07/01/97  0000-00000  Sample msg
 */


$if($inc,
#include <$inc>
)
$if($inc2,
#include <$inc2>
)
$if($inc3,
#include <$inc3>
)


/* purecov: begin inspected */


/* explain function
 * Description:
 *   Destructor
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
$dlink::~$dlink()
{
}


/* explain function
 * Description:
 *   Assignment operator
 *
 * Parameters:
 *   cpy - node to be copied from
 *
 * Return Value: reference to the copied object
 *
 * Assumes: none
 */
$dlink& $dlink::operator = (const $dlink& cpy)
{
  this->data_item = cpy.data_item;
  this->the_next = cpy.the_next;
  this->the_prev = cpy.the_prev;
  return *this;
}


/* explain function
 * Description:
 *   Dequeue() would remove this node from the double linked list.
 *   The node will be returned.
 *
 * Parameters: none
 *
 * Return Value: self
 *
 * Assumes: none
 */
$dlink* $dlink::Dequeue()
{
  this->the_next->the_prev = this->the_prev;
  this->the_prev->the_next = this->the_next;
  this->the_prev = this->the_next = NULL;
  return this;
}


/* explain function
 * Description:
 *   InsertNext() would insert a specified node after this node.
 *
 * Parameters:
 *   inserted_node - the node to be inserted
 *
 * Return Value: none
 *
 * Assumes: none
 */
void $dlink::InsertNext($dlink* const inserted_node)
{
  inserted_node->the_prev = this;
  inserted_node->the_next = this->the_next;
  this->the_next = this->the_next->the_prev = inserted_node;
}


/* explain function
 * Description:
 *   InsertPrev() would insert a specified node prior to this node.
 *
 * Parameters:
 *   inserted_node - the node to be inserted
 *
 * Return Value: none
 *
 * Assumes: none
 */
void $dlink::InsertPrev($dlink* const inserted_node)
{
  inserted_node->the_prev = this->the_prev;
  inserted_node->the_next = this;
  this->the_prev = this->the_prev->the_next = inserted_node;
}


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
$dlist::$dlist()
  : head_node(NULL, &tail_node), tail_node(&head_node, NULL)
{
}


/* explain function
 * Description:
 *   Copy constructor
 *
 * Parameters:
 *   cpy - double linked list to be copied
 *
 * Return Value: none
 *
 * Assumes: none
 */
$dlist::$dlist(const $dlist & cpy)
  : head_node(NULL, &tail_node), tail_node(&head_node, NULL)
{
  *this = cpy;
}


/* explain function
 * Description:
 *   Destructor
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
$dlist::~$dlist()
{
}


/* explain function
 * Description:
 *   Assignment operator
 *   If assignment failed, the target double linked list will not
 *   contain any elements.
 *
 * Parameters:
 *   cpy - double linked list to be copied
 *
 * Return Value: none
 *
 * Assumes: none
 */
$dlist & $dlist::operator = (const $dlist & cpy)
{
  char no_memory = 0;

  while (! this->IsEmpty())
  {
    delete this->RemoveFirst();
  }

  $dlink* cur_ptr = cpy.head_node.Next();
  $dlink* new_node;
  while (cur_ptr != &(cpy.tail_node))
  {
    new_node = new $dlink(*cur_ptr);
    if (new_node != NULL)
    {
      this->InsertLast(new_node);
    }
    else
    {
      no_memory = 1;
      break;
    }
    cur_ptr = cur_ptr->Next();
  }

  if (no_memory)
  {
    while (! this->IsEmpty())
    {
      delete this->RemoveFirst();
    }
  }
  return *this;
}


/* explain function
 * Description:
 *   Length() would return the number of elements in the double
 *   linked list.  Since length information is not cached, calling
 *   this function is of order N operation.
 *
 * Parameters: none
 *
 * Return Value: length of double linked list
 *
 * Assumes: none
 */
size_t $dlist::Length() const
{
  size_t total = 0;
  $dlink* cur_ptr = this->head_node.Next();

  while (cur_ptr != & (this->tail_node))
  {
    cur_ptr = cur_ptr->Next();
    ++total;
  }
  return total;
}

/* purecov: end inspected */
