auto sol_p_e = [](int q, const auto& qs, const int p, const int e, const int mod) {
  // qs[i] = {n, r}, nCr mod p^e in O(p^e)
  vector dp(mod, 1);
  for (int i = 0; i < mod; i++) {
    if (i) dp[i] = dp[i - 1];
    if (i % p == 0) continue;
    dp[i] = mul(dp[i], i);
  }
  auto f = [&](i64 n) {
    i64 res = 0;
    while (n /= p) res += n;
    return res;
  };
  auto g = [&](i64 n) {
    auto rec = [&](const auto& self, i64 n) -> int {
      if (n == 0) return 1;
      int q = n / mod, r = n % mod;
      int ret = mul(self(self, n / p), dp[r]);
      if (q & 1) ret = mul(ret, dp[mod - 1]);
      return ret;
    };
    return rec(rec, n);
  };
  auto bino = [&](i64 n, i64 r) {
    if (n < r) return 0;
    if (r == 0 || r == n) return 1;
    i64 a = f(n) - f(r) - f(n - r);
    if (a >= e) return 0;
    int b = mul(g(n), modinv(mul(g(r), g(n - r)), mod));
    return mul(pow(p, a), b);
  };
  vector res(q, 0);
  for (int i = 0; i < q; i++) {
    auto [n, r] = qs[i];
    res[i] = bino(n, r);
  }
  return res;
};
auto sol = [](int q, const auto& qs, const int mod) {
  vector fac = factor(mod);
  vector r(q, vector(fac.size(), 0));
  vector m(fac.size(), 1);
  for (int i = 0; i < fac.size(); i++) {
    auto [p, e] = fac[i];
    for (int j = 0; j < e; j++) m[i] *= p;
    auto res = sol_p_e(q, qs, p, e, m[i]);
    for (int j = 0; j < q; j++) r[j][i] = res[j];
  }
  vector res(q, 0);
  for (int i = 0; i < q; i++) res[i] = crt(r[i], m).first;
  return res;
};