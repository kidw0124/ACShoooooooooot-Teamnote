// x = r_i mod m_i
// (y, m) 'x = y mod m' 'm = lcm(m_i)', if not exists return (0, 0)
auto crt = [](auto r, auto m) {
  const int n = r.size(); i64 r0 = 0, m0 = 1;
  for (int i = 0; i < n; i++) {
    i64 r1 = r[i], m1 = m[i];
    if (m0 < m1) swap(r0, r1), swap(m0, m1);
    if (m0 % m1 == 0 && r0 % m1 != r1) return pair(0LL, 0LL);
    if (m0 % m1 == 0) continue;
    i64 g = gcd(m0, m1);
    if ((r1 - r0) % g) return pair(0LL, 0LL);
    i64 u0 = m0 / g, u1 = m1 / g;
    i64 x = (r1 - r0) / g % u1 * modinv(u0, u1) % u1;
    r0 += x * m0, m0 *= u1; if (r0 < 0) r0 += m0;
  }
  return pair(r0, m0);
};