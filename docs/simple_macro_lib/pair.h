#ifndef $cap($myclass)_H
#define $cap($myclass)_H

/* explain file $myclass.h
 *
 * Description: pair data structure
 * http://www.concentric.net/~ttwang/macro/uuPair.h
 * Author: Thomas Wang
 *
 */


class $myclass; // forward declaration


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
 * The class $myclass provides for a storage for a pair
 * of data of type $T1, and $T2.
 */
class $myclass // from template class uuPair
{
  public:

    $T1 a;
    $T2 b;

    $myclass();
    $myclass(const $myclass &);
    $myclass($T1, $T2);
    $myclass& operator = (const $myclass& cpy); /* assignment operator */
};


/* explain function
 * Description:
 *   default constructor
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass()
{
}


/* explain function
 * Description:
 *   copy constructor
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass(const $myclass & cpy)
  : a(cpy.a), b(cpy.b)
{
}


/* explain function
 * Description:
 *   alternate constructor
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass(
   $T1 a_val
  ,$T2 b_val)
  : a(a_val), b(b_val)
{
}


/* explain function
 * Description:
 *   assignment operator
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass& $myclass::operator = (const $myclass& cpy)
{
  this->a = cpy.a;
  this->b = cpy.b;
  return *this;
}

#endif
