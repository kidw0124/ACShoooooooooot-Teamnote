// gp_hash_table, cc_hash_table, hash for pair
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
  int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<int, int, chash> table;
struct pair_hash {
  template <class T1, class T2>
  size_t operator () (const pair<T1,T2> &p) const {
    auto h1 = hash<T1>{}(p.first);
    auto h2 = hash<T2>{}(p.second);
    return h1 ^ h2;
  }
};
gp_hash_table<int, int, chash> table;
unordered_set<pll, pair_hash> st;