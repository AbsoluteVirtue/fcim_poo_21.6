
/*
 * Description:
 *   single linked list template implementation file
 *
 * Author: Thomas Wang
 * http://www.concentric.net/~ttwang/macro/uuSlink.cc
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
 *   Assignment operator
 *
 * Parameters:
 *   cpy - node to be copied from
 *
 * Return Value: reference to the copied object
 *
 * Assumes: none
 */
$myclass& $myclass::operator = (const $myclass& cpy)
{
  this->data_item = cpy.data_item;
  this->the_next = cpy.the_next;
  return *this;
}


/* explain function
 * Description:
 *   Reverse() will update the single linked list to reverse
 *   its ordering.  The reversed single linked list will be returned.
 *
 * Parameters: none
 *
 * Return Value: Reversed uuSlink
 *
 * Assumes: none
 */
$myclass* $myclass::Reverse()
{
  $myclass* result = NULL;
  $myclass* cur_ptr = this;
  $myclass* next_ptr;
  do
  {
    /* reverse one link */
    next_ptr = cur_ptr->the_next;
    cur_ptr->the_next = result;
    result = cur_ptr;
    cur_ptr = next_ptr;
  } while (cur_ptr != NULL);

  return result;
}

/* purecov: end inspected */
