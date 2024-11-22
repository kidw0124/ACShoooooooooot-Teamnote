#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// order_of_key (k) : Number of items strictly smaller than k
// find_by_order(k) : K‐th element in a set (counting from zero) 
// O(lgn)
using ordered_set =
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multi_set = tree<int, null_type, less_equal<int>, rb_tree_tag,
                               tree_order_statistics_node_update>;
void m_erase(ordered_multi_set &OS, int val) {
  int index = OS.order_of_key(val);
  ordered_multi_set::iterator it = OS.find_by_order(index);
  if (*it == val) OS.erase(it);
}
