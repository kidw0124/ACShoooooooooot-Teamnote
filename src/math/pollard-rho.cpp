ll pollard(ll n) {
  auto f = [n](ll x) { return modadd(modmul(x, x, n), 3, n); };
  ll x = 0, y = 0, t = 30, p = 2, i = 1, q;
  while (t++ % 40 || gcd(p, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if (q = modmul(p, abs(x - y), n)) p = q;
    x = f(x), y = f(f(y));
  }
  return gcd(p, n);
}
// integer factorization
// O(n^0.25 * logn)
vector<ll> factor(ll n) {
  if (n == 1) return {};
  if (is_prime(n)) return { n };
  ll x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), r.begin(), r.end());
  sort(l.begin(), l.end());
  return l;
}