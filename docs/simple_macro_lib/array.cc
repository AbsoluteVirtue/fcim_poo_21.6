
/* file $myclass.cc
 *
 * Description: expansion array template implementation file
 *
 * Author: Thomas Wang
 * http://www.concentric.net/~ttwang/macro/uuArray.cc
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
 *   Operator [] will obtain an object inside the array, given an index.
 *   The index starts from 0.
 *
 *   Warning: if retrieval is out of bound, program will
 *            segmentation fault!
 *
 * Parameters:
 *   the_index - position number of array
 *
 * Return Value: object at the specified index position
 *
 * Assumes:
 *   Variable 'the_index' is within the array bound.
 */
$T& $myclass::operator [] (size_t the_index) const
{
  register size_t buf_index = 0;
  register size_t cur_buflen = UUARRAY_INITIAL_SIZE;

  /* determine which slice buffer to use */

  /* while the index is not in the current buffer */
  while (the_index >= cur_buflen)
  {
    the_index -= cur_buflen;
    ++buf_index; // double buffer index
    cur_buflen += cur_buflen; // double buffer size
  }
  return *((this->the_desc[buf_index]) + the_index);
}


/* explain function
 * Description:
 *   GrowBuffer() will extend the buffers to the length
 *   indicated by 'the_length'.  If out of memory happens, the
 *   grown buffers will be deleted.
 *
 *   Returns TRUE if out of memory.
 *
 * Parameters:
 *   the_length - length to grow to
 *
 * Return Value: TRUE if out of memory, FALSE if OK
 *
 * Assumes: none
 */
char $myclass::GrowBuffer(size_t the_length)
{
  register size_t buf_index = 0;
  register size_t cur_buflen = UUARRAY_INITIAL_SIZE;
  size_t old_num_buffer = this->num_buffer;

  while (the_length > 0)
  {
    if (buf_index >= this->num_buffer)
    {
      // beyond the current buffer limit
      value_type *new_buffer = new value_type[cur_buflen];
      if (new_buffer == NULL)
      {
        // out of memory, delete any newly allocated buffer
        while (this->num_buffer > old_num_buffer)
        {
          delete [] this->the_desc[--(this->num_buffer)];
        }
        return 1; // out of memory status
      }
      this->the_desc[(this->num_buffer)++] = new_buffer; // assign new buffer
    }
      
    if (the_length <= cur_buflen)
      break; // end of the loop
    else
    {
      the_length -= cur_buflen; // decrease length by current buffer length
      ++buf_index; // increase buffer index
      cur_buflen += cur_buflen; // double current buffer length
    }
  }
  return 0; // ok
}


/* explain function
 * Description:
 *   Append() will append an object to the end of an array.
 *   The resulting length of the array will be returned.
 * 
 *   If out of memory, the object will not be appended, and
 *   the length of the array will not be modified.
 *
 * Parameters:
 *   the_obj - object to be appended
 *
 * Return Value: resulting length in unsigned 32 bit integer
 *
 * Assumes: none
 */
size_t $myclass::Append(const value_type the_obj)
{
  size_t buf_index = 0;
  register size_t cur_buflen = UUARRAY_INITIAL_SIZE;
  register size_t the_index = this->total_elem;

  if (the_index + 1 != 0)
  {
    /* number did not wrap around past 2^32 - 1 back to 0 */

    /* determine which slice buffer to use */

    /* while the index is not covered by current buffer */
    while (the_index >= cur_buflen)
    {
      the_index -= cur_buflen; // decrease array index by current buffer len
      ++buf_index; // increase buffer index
      cur_buflen += cur_buflen; // double buffer size
    }

    if (buf_index < this->num_buffer)
    {
      // no expansion required

      *((this->the_desc[buf_index])+the_index) = the_obj; // assign the object
      ++(this->total_elem); // increase length by 1
    }
    else
    {
      // expansion required

      value_type* new_buffer = new value_type[cur_buflen];
      // allocate a new buffer

      if (new_buffer != NULL)
      {
        ++(this->num_buffer); // increase number of buffer by 1
        this->the_desc[buf_index] = new_buffer; // assign the new buffer
        *(this->the_desc[buf_index]) = the_obj; // assign the object
        ++(this->total_elem); // increase length by 1
      }
    }
  }
  return this->total_elem; // return resulting array length
}


/* explain function
 * Description:
 *   IncreaseLength() increases the length of the array.
 *   The newly created elements will be initialized with the
 *   value of 'init_value'.
 *
 *   The resulting length will be returned.
 *
 *   If out of memory occurred during array expansion, the
 *   array length will not be modified.
 *   If error occurred during object assignment, the array length
 *   will be increased up to the position where the error occurred.
 *
 * Parameters:
 *   amount     - amount of length to increase
 *   init_value - initialize value
 *
 * Return Value: resulting length in unsigned 32 bit integer
 *
 * Assumes: none
 */
size_t $myclass::IncreaseLength(size_t amount, const value_type init_value)
{
  size_t buf_index = 0;
  size_t cur_buflen = UUARRAY_INITIAL_SIZE;
  size_t old_size = this->total_elem;
  size_t the_index = 0;

  if (old_size + amount > old_size)
  {
    /* number did not wrap around past 2^32 - 1 back to 0, and amount != 0 */

    amount += old_size;

    /* increase buffer length */
    if (this->GrowBuffer(amount))
    {
      /* out of memory */
      return this->total_elem;
    }

    while (the_index < amount)
    {
      if (the_index + cur_buflen <= old_size)
      {
        // this buffer does not need copy, part of existing array
        the_index += cur_buflen; // increase index by current buffer length
        ++buf_index; // increase buffer index
        cur_buflen += cur_buflen; // double the current buffer length
      }
      else
      {
        // this buffer need copying
        // find out the number of objects to copy,
        // and the starting offset

        // find out how many objects to copy, based on current buffer length
        // and the left over amount to completion
        size_t num_to_copy =
          (amount - the_index > cur_buflen) ? cur_buflen : amount - the_index;

        // copy_index starts greater than 0 when the current position is
        // less than the old array length
        register size_t copy_index =
          (old_size > the_index) ? old_size - the_index : 0;

        do
        {
          *(this->the_desc[buf_index] + copy_index) = init_value; // copy
          ++(this->total_elem); // increase array length
        } while (++copy_index < num_to_copy);
        the_index += num_to_copy; // increase index by amount copied
        ++buf_index; // increse buffer index
        cur_buflen += cur_buflen; // double current buffer length
      }
    }
  }
  return this->total_elem; // return resulting array length
}


/* explain function
 * Description:
 *   DecreaseLength() decreases the length of the array.
 *   The resulting length will be returned.
 * 
 *   If the amount to be decreased is larger than the length of
 *   the array, the length will be set to 0.
 *
 * Parameters:
 *   amount - amount of length to decrease
 *
 * Return Value: resulting length in unsigned 32 bit integer
 *
 * Assumes: none
 */
size_t $myclass::DecreaseLength(size_t amount)
{
  size_t buf_index = 0;
  register size_t cur_buflen = UUARRAY_INITIAL_SIZE;
  register size_t the_length;

  /* adjust length */
  if (amount > this->Length())
  {
    the_length = this->total_elem = 0;
  }
  else
  {
    the_length = (this->total_elem -= amount);
  }

  /* determine which slice buffer to use */

  // while the length is not covered by current buffer
  while (the_length >= cur_buflen)
  {
    the_length -= cur_buflen; // decrease length by current buffer length
    ++buf_index; // increase buffer index
    cur_buflen += cur_buflen; // double current buffer length
  }

  /* remove unused slices - somewhat conservative to avoid boucing
     around the boundary conditions:
     eg. increase at the end of a buffer followed by decrease at the
     start of a buffer */
  while (buf_index + 2 < this->num_buffer)
  {
    delete [] this->the_desc[--(this->num_buffer)];
  }

  return this->total_elem; // return resulting array length
}


/* explain function
 * Description:
 *   Assigns the 'cpy' array to this array.
 *
 *   If assignment fails due to out of memory, the array's length
 *   will be set to 0.
 *
 *   If error occurs during object assignment, the length of the
 *   array will be set to the location of the error.
 *
 * Parameters:
 *   cpy - array to copy from
 *
 * Return Value: this array
 *
 * Assumes: none
 */
$myclass& $myclass::operator = (const $myclass& cpy)
{
  size_t num_to_copy = cpy.total_elem;
  register size_t buf_index = 0;
  size_t cur_buflen = UUARRAY_INITIAL_SIZE;

  this->total_elem = 0;
  if (this->GrowBuffer(cpy.Length()) == 0) // array length increase OK
  {
    while (num_to_copy > 0) // while has data to copy
    {
      // find out how many items to copy
      size_t copy_len = (num_to_copy < cur_buflen) ? num_to_copy : cur_buflen;

      for (register size_t copy_index= 0; copy_index < copy_len; ++copy_index)
      {
        // copy item
        *(this->the_desc[buf_index] + copy_index) =
          *(cpy.the_desc[buf_index] + copy_index);
        ++(this->total_elem); // increase number of elements in array
      }
      num_to_copy -= copy_len; // decrease no. of items to copy
      cur_buflen += cur_buflen; // double current buffer length
      ++buf_index; // increase buffer index
    }
  }
  else
  {
    // out of memory, delete array buffers
    while (this->num_buffer > 0)
      delete [] this->the_desc[--(this->num_buffer)];
  }

  return *this;
}


/* explain function
 * Description:
 *   Destructor of uuArray.
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
$myclass::~$myclass()
{
  while (this->num_buffer > 0)
  {
    delete [] this->the_desc[--(this->num_buffer)];
  }
}

/* purecov: end inspected */
