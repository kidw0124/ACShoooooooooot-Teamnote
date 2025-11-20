#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target ("avx,avx2,fma")
#define debug(...) __dbg(#__VA_ARGS__, __VA_ARGS__)
template<typename T>
ostream& operator<<(ostream& out, vector<T> v) {
  string _;out << '('; for (T x : v) out << _ << x, _ = " ";out << ')';
  return out;
}
void __dbg(string s, auto... x) {
  string _;cout<<'('<<s<<") : ";(..., (cout << _ << x, _ = ", "));cout<<'\n';
}
auto gen_tree = [](int n) {
  auto prufer_decode = [](const vector<int>& v) {
    const int n = v.size() + 2; int p = 1, leaf = 1;
    vector deg(n + 1, 1);
    for (int i : v) deg[i]++; while (deg[p] != 1) p++, leaf++;
    vector res(0, pair(0, 0));
    for (int i : v) {
      res.push_back({ leaf, i });
      if (--deg[i] == 1 && i < p) leaf = i;
      else { do p++; while (deg[p] != 1); leaf = p; }
    }
    res.push_back({ leaf, n });
    return res;
  };
  vector v(n - 2, 0);
  for (int& i : v) i = gen_rand(1, n);
  return prufer_decode(v);
};
auto vectors(const int n, auto&& val) {
  return vector(n, val);
}
auto vectors(const int n, auto&&... args) {
  return vector(n, vectors(args...));
}
struct query { // mo's algorithm
  int l, r, i;
  bool operator< (const query& x) {
  if ((l ^ x.l) >> 9) return l < x.l;
    return l >> 9 & 1 ^ r < x.r;
  }
};
template<typename T>
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator() (T x) const {
    static const uint64_t seed = chrono::steady_clock::now().time_since_epoch().count();
      return splitmix64(x + seed);
  }
};