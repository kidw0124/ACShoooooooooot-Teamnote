using i64 = long long;
// @param  (a, b) 'gcd(a, b) = 1'
// @return (x, y) 'ax + by = 1' 'max(|x|, |y|) <= max(|a|, |b|)'
auto ext_gcd = [](i64 a, i64 b) {
  auto rec = [&](const auto& self, i64 a, i64 b) -> pair<i64, i64> {
    if (!b) return pair(1, 0);
    auto [y, x] = self(self, b, a % b);
    return pair(x, y - a / b * x);
  };
  return rec(rec, a, b);
};
// @param  x 'gcd(x, m) = 1'
// @return y 'x * y = 1 mod m'
auto minv = [](i64 x, i64 m) {
  auto [y, _] = ext_gcd(x, m);
  if (y < 0) y += m;
  return y;
};
// @param  r_i
// @param  m_i    'x = r_i mod m_i'
// @return (y, m) 'x = y mod m' 'm = lcm(m_i)'
// @return (0, 0) 'if there doesn't exists such y'
auto crt = [](auto r, auto m) {
  const int n = r.size();
  i64 r0 = 0, m0 = 1;
  for (int i = 0; i < n; i++) {
    i64 r1 = r[i], m1 = m[i];
    if (m0 < m1) swap(r0, r1), swap(m0, m1);
    if (m0 % m1 == 0 && r0 % m1 != r1) return pair(0LL, 0LL);
    if (m0 % m1 == 0) continue;
    i64 g = gcd(m0, m1);
    if ((r1 - r0) % g) return pair(0LL, 0LL);
    i64 u0 = m0 / g, u1 = m1 / g;
    i64 x = (r1 - r0) / g % u1 * minv(u0, u1) % u1;
    r0 += x * m0, m0 *= u1;
    if (r0 < 0) r0 += m0;
  }
  return pair(r0, m0);
};
auto sol_p_e = [](int q, const auto& qs, const int p, const int e, const int mod) {
  auto mul = [&](int a, int b) -> int { return 1LL * a * b % mod; };
  auto pow = [&](int x, int n) {
    int ret = 1;
    for (; n; n >>= 1) { if (n & 1) ret = mul(ret, x); x = mul(x, x); }
    return ret;
  };
  vector dp(mod, 1);
  for (int i = 0; i < mod; i++) {
    if (i) dp[i] = dp[i - 1];
    if (i % p == 0) continue;
    dp[i] = mul(dp[i], i);
  }
  auto f = [&](i64 n) {
    int a = 0, b = 1;
    while (n) {
      i64 q = n / mod, r = n % mod;
      a += q, b = mul(b, dp[r]);
      if (q & 1) b = mul(b, dp[mod - 1]);
      n = q;
    }
    return pair(a, b);
  };
  auto bino = [&](i64 n, i64 r) {
    if (n < r) return 0;
    if (r == 0 || r == n) return 1;
    auto [a1, b1] = f(n);
    auto [a2, b2] = f(r);
    auto [a3, b3] = f(n - r);
    int a = a1 - a2 - a3;
    int b = mul(b1, minv(mul(b2, b3), mod));
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