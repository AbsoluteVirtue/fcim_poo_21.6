#include <algorithm>
#include <cassert>
#include <numeric>
#include <set>
#include <unordered_map>
#include <vector>

using map = std::unordered_map<int, int>;
using set = std::set<int>;
using vector = std::vector<int>;

template <typename Container>
int at(const Container& c, int index) {
    if (index < 0) index = c.size() - index;
    index = std::clamp(index, 0, (int)c.size() - 1);
    return c[index];
}

int main()
{
    vector v{1, 2, 3, 4, 5, 56, 6};
    assert(v.rbegin()[5] == 2);

    // TODO: compare with for loop
    std::iota(v.begin(), v.end(), -10);
    assert(v.rbegin()[0] == -4);

    std::iota(v.rbegin(), v.rend(), 10);

    map a = {{1, 2}, {3, 4}};
    map b = {{3, 4}, {1, 2}};

    assert(a == b);
    assert(! std::equal(a.begin(), a.end(), b.begin()));

    set s{1, 2, 3, 4, 5, 56, 6};

    assert(std::all_of(s.begin(), s.end(), [](int x) { return x >= 0; }));

    s.insert(s.begin(), -1);

    assert(std::any_of(s.begin(), s.end(), [](int x) { return x < 0; }));

    set t{10, 20, 3, 4, 5, 56, 16};
    set u{10, 20};

    // includes
    auto bo = std::set_union(t.begin(), t.end(), u.begin(), u.end(), v.begin());

    // set_difference
    // set_intersection
    // set_symmetric_difference
    // set_union

    return 0;
}

// all_of
// any_of
// none_of

// for_each
// for_each_n

// count
// count_if

// mismatch

// find
// find_if
// find_if_not
// find_end
// find_first_of

// adjacent_find
// search
// search_n

// copy
// copy_if
// copy_n
// copy_backward

// move
// move_backward

// fill
// fill_n

// transform

// generate
// generate_n

// remove
// remove_if
// remove_copy
// remove_copy_if

// replace
// replace_if
// replace_copy
// replace_copy_if

// swap
// swap_ranges
// iter_swap

// reverse
// reverse_copy

// rotate
// rotate_copy

// shift_left
// shift_right

// random_shuffle
// shuffle

// sample

// unique
// unique_copy

// is_partitioned
// partition
// partition_copy
// stable_partition
// partition_point

// is_sorted
// is_sorted_until
// sort
// partial_sort
// partial_sort_copy
// stable_sort

// nth_element

// lower_bound
// upper_bound

// binary_search

// equal_range

// merge
// inplace_merge

// includes
// set_difference
// set_intersection
// set_symmetric_difference
// set_union

// is_heap
// is_heap_until
// make_heap
// push_heap
// pop_heap
// sort_heap

// max
// max_element
// min
// min_element
// minmax
// minmax_element

// clamp

// equal
// lexicographical_compare
// lexicographical_compare_three_way

// is_permutation
// next_permutation
// prev_permutation

// iota
// accumulate
// inner_product
// adjacent_difference
// partial_sum

// reduce
// exclusive_scan
// inclusive_scan
// transform_reduce
// transform_exclusive_scan
// transform_inclusive_scan

// uninitialized_copy
// uninitialized_copy_n
// uninitialized_fill
// uninitialized_fill_n
// uninitialized_move
// uninitialized_move_n
// uninitialized_default_construct
// uninitialized_default_construct_n
// uninitialized_value_construct
// uninitialized_value_construct_n

// destroy
// destroy_n
// destroy_at

// construct_at
