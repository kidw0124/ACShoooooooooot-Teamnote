struct bit_array { // 0-indexed
  using u64 = unsigned long long;
  explicit bit_array(int sz) : n(sz + 64 >> 6), data(n), psum(n) {}
  void set(int i) { data[i >> 6] |= u64(1) << (i & 63); }
  int rank(int i, bool x) const {
    auto res = rank(i);
    return x ? res : i - res;
  }
  int rank(int l, int r, bool x) const {
    auto res = rank(r) - rank(l);
    return x ? res : r - l - res;
  }
  bool operator[](int i) const {
    return data[i >> 6] >> (i & 63) & 1;
  }
  void init() {
    for (int i = 1; i < n; i++)
      psum[i] = psum[i - 1] + __builtin_popcountll(data[i - 1]);
  }
private:
  int n;
  vector<u64> data;
  vector<int> psum;
  int rank(int i) const {
    return psum[i >> 6] + __builtin_popcountll(data[i >> 6] & (u64(1) << (i & 63)) - 1);
  }
};
// 전처리 O(nlgn) 각 쿼리별 O(lgn)
template<typename T, enable_if_t<is_integral_v<T>, int> = 0>
struct wavelet_matrix { // 0-indexed
  explicit wavelet_matrix(vector<T> v) :
    n(v.size()),
    lg(__lg(*max_element(v.begin(), v.end())) + 1),
    data(lg, bit_array(n)),
    zero(lg, 0) {
    for (int i = lg - 1; i >= 0; i--) {
      for (int j = 0; j < n; j++) if (v[j] >> i & 1) data[i].set(j);
      data[i].init();
      auto it = stable_partition(v.begin(), v.end(), [&](T x) { return ~x >> i & 1; });
      zero[i] = it - v.begin();
    }
  }
  int rank(int l, int r, T x) const { // count i s.t. (l <= i < r) && (v[i] == x)
    if (x >> lg) return 0;
    for (int i = lg - 1; i >= 0; i--) {
      bool f = x >> i & 1;
      adjust(i, l, r, f);
    }
    return r - l;
  }
  int count(int l, int r, T x) const { // count i s.t. (l <= i < r) && (v[i] < x)
    if (x >> lg) return r - l + 1;
    int res = 0;
    for (int i = lg - 1; i >= 0; i--) {
      bool f = x >> i & 1;
      if (f) res += data[i].rank(l, r, 0);
      adjust(i, l, r, f);
    }
    return res;
  }
  T quantile(int l, int r, int k) const { // kth (0-indexed) smallest number in v[l, r)
    T res = 0;
    for (int i = lg - 1; i >= 0; i--) {
      int c = data[i].rank(l, r, 0);
      bool f = c <= k;
      if (f) res |= T(1) << i, k -= c;
      adjust(i, l, r, f);
    }
    return res;
  }
private:
  int n, lg;
  vector<bit_array> data;
  vector<int> zero;
  void adjust(int i, int& l, int& r, bool f) const {
    if (!f) {
      l = data[i].rank(l, 0);
      r = data[i].rank(r, 0);
    }
    else {
      l = zero[i] + data[i].rank(l, 1);
      r = zero[i] + data[i].rank(r, 1);
    }
  }
};