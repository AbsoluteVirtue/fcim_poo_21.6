#ifndef $cap($myclass)_H
#define $cap($myclass)_H


/* explain file $myclass.h
 * Description:
 *   hash table declaration file
 *
 * Author: Thomas Wang
 * http://www.concentric.net/~Ttwang/macro/uuMap.h
 * History:
 * (ID)   (name)   (date)    (bug#)      (message)
 * 000TW  Thomas   07/01/97  0000-00000  Sample msg
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


$include(uuPair.h,myclass=kvpair$myclass T1=$Key T2=$Val)


$include(uuSlink.h,myclass=kvlink$myclass T=kvpair$myclass)


$include(uuArray.h,myclass=kvarray$myclass T=kvlink$myclass*)




/* explain class $myclass
 * The $myclass data structure provides mapping capability
 * from a $Key type
 * to a $Val type, given a key
 * identity data structure $Keyid.
 *
 * $myclass is implemented using hash table.
 *
 * The class $Keyid should have three member functions
 * as follows:
 *
 *   struct $Keyid
 *   {
 *     char equal($Key x, $Key y) const; // x == y
 *     char less($Key x, $Key y) const; // x < y
 *     size_t hash($Key x) const;
 *   };
 *
 * At file generation time, just give the name
 * of the class with the above three member functions at
 * the parameter position for Keyid.
 *
 * The hash table algorithm used is 'linear hashing' discussed in
 * CACM, Apr 1988.  This algorithm features hash table expansion
 * capability with amortized expansion processing.
 *
 */
class $myclass // from template class uuMap
{
  public:
    typedef $Key key_type;
    typedef $Val val_type;
    typedef $Keyid keyid_type;

    typedef kvlink$myclass link_type;

  protected:
    size_t key_count;  /* number of records in the table */
    size_t split_ptr;  /* next bucket to be split */
    size_t max_split;  /* upper bound on 'split_ptr' during this expansion */
    keyid_type  ident; /* Key's identity data structure */
    kvarray$myclass slots; /* bucket table */

    size_t BucketOffset(size_t maxsplit,
                        size_t splitptr,
                        size_t hashval) const;

    void SplitBucket();
    void MergeBucket();

  public:
    size_t Length() const;
    void ClearAll();
    char Exists(const key_type& the_key) const;
    val_type& operator [] (const key_type& the_key) const;
    key_type GetAnyKey(const size_t offset = 0) const;
    key_type GetNextKey(const key_type& the_key) const;

    size_t Insert(const key_type& the_key, const val_type& the_val);
    size_t RemoveWith(const key_type& the_key);

    $myclass& operator = (const $myclass& cpy);

    $myclass(); // default constructor
    $myclass(const $myclass& cpy); // copy constructor
    ~$myclass(); // destructor
};


/* explain function
 * Description:
 *   Length() will return the number of elements in the hash table.
 *
 * Parameters: none
 *
 * Return Value: unsigned 32 bit integer
 *
 * Assumes: none
 */
inline size_t $myclass::Length() const
{
  return this->key_count;
}


/* explain function
 * Description:
 *   This function will return a bucket number suitable with linear
 *   hashing.
 *
 * Parameters:
 *   maxsplit - max split value
 *   splitptr - split pointer value
 *   hashval  - a hash value
 *
 * Return Value: bucket number
 *
 * Assumes: none
 */
inline size_t
  $myclass::BucketOffset(size_t maxsplit,
                         size_t splitptr,
                         size_t hashval) const
{
  return (hashval % maxsplit < splitptr) ?
         hashval % (maxsplit + maxsplit) :
         hashval % maxsplit;
}


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
  : key_count(0), split_ptr(0), max_split(1)
{
}


/* explain function
 * Description:
 *   copy constructor
 *
 * Parameters:
 *   cpy - hash table to be copied
 *
 * Return Value: none
 *
 * Assumes: none
 */
inline $myclass::$myclass(const $myclass& cpy)
  : key_count(0), split_ptr(0), max_split(1)
{
  (*this) = cpy;
}


#endif
