/* 
 * Description:
 *   hash table implementation file
 *
 * Author: Thomas Wang
 * http://www.concentric.net/~Ttwang/macro/uuMap.cc
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


$include(uuSlink.cc,myclass=kvlink$myclass T=kvpair$myclass)


$include(uuArray.cc,myclass=kvarray$myclass T=kvlink$myclass*)



/* explain function
 * Description:
 *   This function will split a bucket in the hash table.
 *   Do nothing if length of hash table < 2.
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
void $myclass::SplitBucket()
{
  link_type *old_chain = NULL;
  link_type *new_chain = NULL;
  link_type *cur_ptr;
  link_type *next_ptr;

  size_t old_place = this->split_ptr;
  size_t new_place = old_place + this->max_split;

  if (old_place + 1 >= this->max_split)
  {
    if (this->key_count < 2)
      return; // does not need to split when number of keys < 2

    this->max_split += this->max_split; // double max split
    this->split_ptr = 0; // wrap around the split pointer
  }
  else
  {
    this->split_ptr = old_place + 1;
  }

  /* split the original chain into old_chain, and new_chain */

  cur_ptr = this->slots[old_place];

  while (cur_ptr != NULL)
  {
    next_ptr = cur_ptr->Next();

    if (BucketOffset(this->max_split, this->split_ptr,
                     this->ident.hash(cur_ptr->Item().a)
                    ) == old_place
       )
    {
      cur_ptr->Next() = old_chain;
      old_chain = cur_ptr;
    }
    else
    {
      cur_ptr->Next() = new_chain;
      new_chain = cur_ptr;
    }
    cur_ptr = next_ptr;
  }

  /* the split operation makes the list in reversed order, need to
     re-order them. */

  if (old_chain != NULL)
    this->slots[old_place] = old_chain->Reverse();
  else
    this->slots[old_place] = NULL;

  if (new_chain != NULL)
    this->slots[new_place] = new_chain->Reverse();
  else
    this->slots[new_place] = NULL;
}


/* explain function
 * Description:
 *   This function will merge 2 buckets in the hash table.
 *   Do nothing if length of hash table < 2.
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
void $myclass::MergeBucket()
{
  if (this->split_ptr == 0)
  {
    if (this->key_count < 1)
      return; // does not need to merge when number of keys < 1

    this->max_split = this->max_split >> 1; // half the max split
    this->split_ptr = this->max_split - 1; // wrap around the split pointer
  }
  else
    --(this->split_ptr);

  size_t new_place = this->split_ptr;
  size_t old_place = new_place + this->max_split;
  char use_old_chain;

  link_type *old_chain = this->slots[old_place];
  link_type *new_chain = this->slots[new_place];
  link_type *merge_list = NULL;

  while ((old_chain != NULL) || (new_chain != NULL))
  {
    /* while a chain is not empty */

    if (old_chain == NULL)
    {
      /* old_chain is empty, use new_chain instead */
      use_old_chain = 0;
    }
    else if (new_chain == NULL)
    {
      /* new_chain is empty, use old_chain instead */
      use_old_chain = 1;
    }
    else
    {
      /* both chains are not empty */
      /* if old chain is less, use old chain */
      use_old_chain = this->ident.less(old_chain->Item().a,
                                       new_chain->Item().a);
    }

    if (use_old_chain)
    {
      link_type *old_chain_next = old_chain->Next();
      old_chain->Next() = merge_list;
      merge_list = old_chain;
      old_chain = old_chain_next;
    }
    else
    {
      link_type *new_chain_next = new_chain->Next();
      new_chain->Next() = merge_list;
      merge_list = new_chain;
      new_chain = new_chain_next;
    }
  }

  /* the merging operation makes the list in reversed order, need to
     re-order them. */

  if (merge_list != NULL)
    this->slots[new_place] = merge_list->Reverse();
  else
    this->slots[new_place] = NULL;

  /* the old bucket does not have items left */
  this->slots[old_place] = NULL;
}


/* explain function
 * Description:
 *   ClearAll() will remove all entries from the hash table.
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
void $myclass::ClearAll()
{
  link_type *cur_ptr;
  link_type *next_ptr;

  this->split_ptr = this->key_count = 0;
  this->max_split = 1;
  while (this->slots.Length() > 0)
  {
    cur_ptr = this->slots[this->slots.Length() - 1];
    while (cur_ptr != NULL)
    {
      next_ptr = cur_ptr->Next();
      delete cur_ptr;
      cur_ptr = next_ptr;
    }

    this->slots.DecreaseLength(1);
  }
}


/* explain function
 * Description:
 *   Exists(the_key) will return TRUE if the_key is in
 *   the hash table.  FALSE will be returned if the_key is not
 *   in the hash table.
 *
 * Parameters:
 *   the_key - key value to be searched in the hash table
 *
 * Return Value: TRUE if found, FALSE if not found
 *
 * Assumes: none
 */
char $myclass::Exists(const key_type& the_key) const
{
  if (this->key_count == 0)
    return 0; // zero length hash table, return not found

  size_t hash_val = this->ident.hash(the_key);
  size_t bucket_num =
    BucketOffset(this->max_split, this->split_ptr, hash_val);

  link_type *cur_link = this->slots[bucket_num];

  while (cur_link != NULL)
  {
    if (this->ident.equal(the_key, cur_link->Item().a))
    {
      return 1; // found
    }
    cur_link = cur_link->Next(); // travel down the chain
  }

  return 0; // not found
}


/* explain function
 * Description:
 *   Operator [] will return the value given the key.
 *
 *   If the key is not found in the hash, a default dummy
 *   value is returned.
 *
 * Parameters:
 *   the_key - key value to be searched in the hash table
 *
 * Return Value: the associated value
 *
 * Assumes: none
 */
$myclass::val_type&
  $myclass::operator [] (const key_type& the_key) const
{
  static val_type dummy;

  if (this->key_count == 0)
    return dummy; // zero length hash table

  size_t hash_val = this->ident.hash(the_key);
  size_t bucket_num =
    BucketOffset(this->max_split, this->split_ptr, hash_val);

  link_type *cur_link = this->slots[bucket_num];

  while (cur_link != NULL)
  {
    if (this->ident.equal(the_key, cur_link->Item().a))
    {
      return cur_link->Item().b; // found
    }
    cur_link = cur_link->Next(); // travel down the chain
  }

  return dummy; // not found
}


/* explain function
 * Description:
 *   GetAnyKey() would return a key in the hash table.  If there
 *   is not any insertion or deletion to the hash
 *   table, GetAnyKey() would always return the the same key.
 *
 *   If the hash table is length 0, a default key will be returned.
 *
 * Parameters:
 *   offset - this number will influence the key picked
 *
 * Return Value: a key in hash table, default key if length is 0
 *
 * Assumes: none
 */
$myclass::key_type $myclass::GetAnyKey(const size_t offset) const
{
  if (this->key_count == 0)
  {
    return key_type(); // return default key
  }

  // pick a starting bucket based on a hashing computation
  // 1640531551 is close to (1.0 - golden_ratio) of 2^32

  register size_t bucket_num =
    (this->key_count * 1640531551 + offset) % this->key_count;

  register link_type *cur_link = this->slots[bucket_num];

  while (cur_link == NULL)
  {
    if (++bucket_num == this->key_count)
      bucket_num = 0; // wrap around the table
    cur_link = this->slots[bucket_num];
  }
  return cur_link->Item().a; // return first key in this chain
}


/* explain function
 * Description:
 *   GetNextKey() would return a key considered to be immediately
 *   after the input key in the hash table.  This function can be
 *   used to iterate over the hash table if no elements are inserted
 *   or deleted.  If elements are inserted or deleted, the iteration
 *   may skip over some elements, while encountering other elements
 *   multiple times.
 *
 *   If there is not any insertion or deletion to the hash
 *   table, GetNextKey() would always return the the same key.
 *
 *   If the hash table is length 0, or if the input key is not in
 *   the hash table, a default key will be returned.
 *
 * Parameters:
 *   the_key - the input key
 *
 * Return Value: a key immediately after te input key
 *
 * Assumes: none
 */
$myclass::key_type
  $myclass::GetNextKey(const key_type& the_key) const
{
  static key_type dummy;

  if (this->key_count == 0)
    return dummy; // zero length hash table

  size_t hash_val = this->ident.hash(the_key);
  size_t bucket_num =
    BucketOffset(this->max_split, this->split_ptr, hash_val);

  link_type *cur_link = this->slots[bucket_num];

  while (cur_link != NULL)
  {
    if (this->ident.equal(the_key, cur_link->Item().a))
    {
      // found the input key
      cur_link = cur_link->Next(); // travel down the chain
      if (cur_link == NULL)
      {
        do
        {
          // go to next bucket
          if ((++bucket_num) == this->key_count)
            bucket_num = 0;
          cur_link = this->slots[bucket_num];
        } while (cur_link == NULL);
      }
      return cur_link->Item().a; // found
    }
    cur_link = cur_link->Next(); // travel down the chain
  }
  return dummy; // not found
}


/* explain function
 * Description:
 *   RemoveWith() will remove a mapping of key value pair in the
 *   hash table, given the key.
 *
 *   The resulting hash table length will be returned.
 *
 * Parameters:
 *   the_key  - the key
 *
 * Return Value: resulting hash table's length
 *
 * Assumes: none
 */
size_t $myclass::RemoveWith(const key_type& the_key)
{
  if (this->Length() == 0)
  {
    return 0; // removing items from length 0 hash table
  }

  size_t hash_val = this->ident.hash(the_key);
  size_t bucket_num =
    BucketOffset(this->max_split, this->split_ptr, hash_val);

  link_type *cur_ptr = this->slots[bucket_num];

  if (cur_ptr != NULL)
  {
    if (this->ident.equal(the_key, cur_ptr->Item().a))
    {
      // found the entry in the head of the list
      this->slots[bucket_num] = cur_ptr->Next(); // unlink the entry
      --(this->key_count); // decrease key count
      this->MergeBucket(); // merge two buckets
      this->slots.DecreaseLength(1); // decrease bucket table length
      delete cur_ptr; // free memory
      return this->key_count; 
    }
    link_type *prev_ptr = cur_ptr;
    cur_ptr = cur_ptr->Next();
    while (cur_ptr != NULL)
    {
      if (this->ident.equal(the_key, cur_ptr->Item().a))
      {
        // found the entry
        prev_ptr->Next() = cur_ptr->Next(); // unlink the entry
        --(this->key_count); // decrease key count
        this->MergeBucket(); // merge two buckets
        this->slots.DecreaseLength(1); // decrease bucket table length
        delete cur_ptr; // free memory
        return this->key_count; 
      }
      prev_ptr = cur_ptr;
      cur_ptr = cur_ptr->Next(); // go to next entry
    }
  }

  // not found
  return this->key_count;
}


/* explain function
 * Description:
 *   Insert() will insert into the hash table a new mapping of
 *   key and value pair.  If there is already an identical key in the
 *   hash table, the existing mapping will not be modified.
 *
 *   The resulting length of the hash table will be returned.
 *
 *   If out of memory occurred, the length of the hash table will
 *   not be modified.
 *
 * Parameters:
 *   the_key - the key
 *   the_value - the value
 *
 * Return Value: resulting hash table length
 *
 * Assumes:
 */
size_t
  $myclass::Insert(const key_type& the_key, const val_type& the_val)
{
  this->slots.Append(NULL); // increase bucket table length
  if (this->slots.Length() <= this->key_count)
  {
    // out of memory for bucket expansion
    return this->key_count;
  }

  size_t hash_val = this->ident.hash(the_key);
  size_t bucket_num =
    BucketOffset(this->max_split, this->split_ptr, hash_val);

  link_type *cur_ptr = this->slots[bucket_num];
  link_type *new_ptr;

  if ((cur_ptr == NULL) || this->ident.less(the_key, cur_ptr->Item().a))
  {
    // insert in head of list
    new_ptr = 
      new link_type(kvpair$myclass(the_key,the_val),cur_ptr);
    if (new_ptr != NULL)
    {
      // not out of memory for link node creation
      this->slots[bucket_num] = new_ptr;
      ++(this->key_count); // increase key count
      this->SplitBucket(); // split a bucket
    }
    else
    {
      // out of memory for link node creation
      this->slots.DecreaseLength(1);
    }
  }
  else if (this->ident.equal(the_key, cur_ptr->Item().a))
  {
    // key in head of list, not inserted
    this->slots.DecreaseLength(1);
  }
  else
  {
    link_type *prev_ptr;

    for(;;)
    {
      prev_ptr = cur_ptr;
      cur_ptr = cur_ptr->Next();
      if ((cur_ptr == NULL) || this->ident.less(the_key, cur_ptr->Item().a))
      {
        // insert in middle or end of list
        new_ptr = 
          new link_type(kvpair$myclass(the_key,the_val),cur_ptr);
        if (new_ptr != NULL)
        {
          // not out of memory for link node creation
          prev_ptr->Next() = new_ptr;
          ++(this->key_count); // increase key count
          this->SplitBucket(); // split a bucket
          break;
        }
        else
        {
          // out of memory for link node creation
          this->slots.DecreaseLength(1);
          break;
        }
      }
      else if (this->ident.equal(the_key, cur_ptr->Item().a))
      {
        // key in list, not inserted
        this->slots.DecreaseLength(1);
        break;
      }
    }
  }
  return this->key_count; // return resulting hash table length
}


/* explain function
 * Description:
 *   Assignment operator
 *
 *   If out of memory during copying, the target hash table will
 *   be set to length of 0.
 *
 * Parameters:
 *   cpy - hash table to copy from
 *
 * Return Value: this hash table
 *
 * Assumes: none
 */
$myclass& $myclass::operator =
  (const $myclass& cpy)
{
  this->ClearAll();
  for (size_t bucket_num = 0; bucket_num < cpy.Length(); ++bucket_num)
  {
    link_type *cur_ptr = cpy.slots[bucket_num];
    while (cur_ptr != NULL)
    {
      this->Insert(cur_ptr->Item().a, cur_ptr->Item().b);
      cur_ptr = cur_ptr->Next(); // go to next entry
    }
  }

  if (this->Length() != cpy.Length())
  {
    // ran out of memory during copying
    this->ClearAll();
  }
  return (*this);
}


/* explain function
 * Description:
 *   destructor
 *
 * Parameters: none
 *
 * Return Value: none
 *
 * Assumes: none
 */
$myclass::~$myclass()
{
  this->ClearAll(); // delete all elements
}
