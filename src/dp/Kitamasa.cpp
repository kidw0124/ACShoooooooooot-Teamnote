// linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$
// Time: O(n^2 \log k)
ll get_nth(Poly S, Poly tr, ll k) {  // get kth term of recurrence
  int n = sz(tr);
  auto combine = [&](Poly a, Poly b) {
    Poly res(n * 2 + 1);
    rep(i, 0, n + 1) rep(j, 0, n + 1) res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
    for (int i=2*n;i>n;--i)rep(j,0,n)res[i-1-j]=(res[i-1-j]+res[i]*tr[j])%mod;
    res.resize(n + 1);
    return res;
  };
  Poly pol(n + 1), e(pol);
  pol[0] = e[1] = 1;
  for (++k; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }
  ll res = 0;
  rep(i, 0, n) res = (res + pol[i + 1] * S[i]) % mod;
  return res;
}
// Usage: berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
// Time: O(N^2)
vector<ll> berlekampMassey(vector<ll> s) {
  ll n = s.size(), L = 0, m = 0, d, coef, b = 1;
  vector<ll> C(n), B(n), T; C[0] = B[0] = 1;
  for (ll i = 0; i < n; i++) {
    ++m, d = s[i] % mod;
    for (ll j = 1; j <= L; j++) d = (d + C[j] * s[i - j]) % mod;
    if (!d) continue;
    T = C, coef = d * modpow(b, mod - 2) % mod;
    for (j = m; j < n; j++) C[j] = (C[j] - coef * B[j - m]) % mod;
    if (2 * L > i) continue;
    L = i + 1 - L, B = T, b = d, m = 0;
  }
  C.resize(L + 1), C.erase(C.begin());
  for (ll& x : C) x = (mod - x) % mod;
  return C;
}
ll guess_nth_term(vector<ll> x, lint n) {
  if (n < x.size()) return x[n];
  vector<ll> v = berlekamp_massey(x);
  if (v.empty()) return 0;
  return get_nth(v, x, n);
}