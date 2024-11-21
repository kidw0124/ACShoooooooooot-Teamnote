// calculates suffix array with O(n*logn)
auto get_sa(const string& s) {
  const int n = s.size(), m = max(256, n) + 1;
  vector<int> sa(n), r(n << 1), nr(n << 1), cnt(m), idx(n);
  for (int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
  for (int d = 1; d < n; d <<= 1) {
    auto cmp = [&](int a, int b) { return r[a] < r[b] || r[a] == r[b] && r[a + d] < r[b + d];};
    for (int i = 0; i < m; ++i) cnt[i] = 0;
    for (int i = 0; i < n; ++i) cnt[r[i + d]]++;
    for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
    for (int i = n - 1; ~i; --i) idx[--cnt[r[i + d]]] = i;
    for (int i = 0; i < m; ++i) cnt[i] = 0;
    for (int i = 0; i < n; ++i) cnt[r[i]]++;
    for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
    for (int i = n - 1; ~i; --i) sa[--cnt[r[idx[i]]]] = idx[i];
    nr[sa[0]] = 1;
    for (int i = 1; i < n; ++i) nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
    for (int i = 0; i < n; ++i) r[i] = nr[i];
    if (r[sa[n - 1]] == n) break; 
  }
  return sa;
}
// calculates lcp array. it needs suffix array & original sequence with O(n)
auto get_lcp(const string& s, const auto& sa) {
  const int n = s.size(); vector lcp(n - 1, 0), isa(n, 0);
  for (int i = 0; i < n; i++) isa[sa[i]] = i;
  for (int i = 0, k = 0; i < n; i++) if (isa[i]) {
    for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
    lcp[isa[i] - 1] = k ? k-- : 0;
  }
  return lcp;
}