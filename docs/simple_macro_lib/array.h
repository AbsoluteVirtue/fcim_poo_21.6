#ifndef $cap($myclass)_H
#define $cap($myclass)_H

/* explain file $myclass.h
 *
 * Description: expansion array template declaration file
 *
 * Author: Thomas Wang
 * http://www.concentric.net/~ttwang/macro/uuArray.h
 */


class $myclass; // forward declaration


#include <stddef.h>


$if($inc,
#include <$inc>
)
$if($inc2
#include <$inc2>
)
$if($inc3
#include <$inc3>
)


#define UUARRAY_INITIAL_SIZE 15
#define UUARRAY_MAX_SLOT 28

/*  15 * (2 ^ 28) does not overflow 32 bits, while 15 * (2^ 29) does.
 *  Therefore 28 slots will cover the increasing slice sizes for 32 bit
 *  range.
 */


/* explain class $myclass
 * The class $myclass provides expansion array capability
 * over data item of class $T.
 *
 * An array is created initially with length of 0.  The length of the
 * array can be increased with IncreaseLength(), and decreased with
 * DecreaseLength().  An array of increasing length of buffers is used
 * for the storage of data.
 *
 * If the data item is of pointer type, deleting the array
 * will NOT cause the data item pointer to be deleted.  In any
 * case, it is not safe to delete the pointer, as it may be shared.
 */
class $myclass // from template class uuArray
{
  public:

    typedef $T value_type;

  protected:

    size_t total_elem; // number of elements in the array
    size_t num_buffer; // number of allocated buffer
    value_type* the_desc[UUARRAY_MAX_SLOT];
    // array buffer, in increasing size sequence

    char GrowBuffer(size_t the_length);

  public:

    size_t Length() const;
    $T& operator [] (size_t the_indx) const;
    $myclass& operator = (const $myclass& cpy); /* assignment operator */

    size_t Append(const value_type the_obj);
    size_t IncreaseLength(size_t amount, const value_type init_value);
    size_t DecreaseLength(size_t amount);

    $myclass(); /* default constructor */
    $myclass(const $myclass& cpy); /* copy constructor */
    ~$myclass(); /* destructor */
};



/* explain function
 * Description:
 *   Length() will return the number of elements in the array.
 *
 * Parameters: none
 *
 * Return Value: unsigned 32 bit integer
 *
 * Assumes: none
 */
inline size_t $myclass::Length() const
{
  return this->total_elem;
}


/* explain function
 * Description:
 *   Default constructor of uuArray.
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass()
  : total_elem(0), num_buffer(0)
{
}


/* explain function
 * Description:
 *   Copy constructor of uuArray.
 *   If out of memory, the new array will have length of 0.
 *   If error occurred while copying objects, the length of the
 *   array will be at the place where error occurred.
 *
 * Parameters:
 *   cpy - uuArray to be copied
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass(const $myclass& cpy)
  : total_elem(0), num_buffer(0)
{
  (*this) = cpy;
}


#endif
