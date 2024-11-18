// test whether n is prime based on miller-rabin test
// O(logn*logn)
bool is_prime(ll n) {
  if (n < 2 || n % 2 == 0 || n % 3 == 0) return n == 2 || n == 3;
  ll k = __builtin_ctzll(n - 1), d = n - 1 >> k;
  for (ll a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
    ll p = modpow(a % n, d, n), i = k;
    while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
    if (p != n - 1 && i != k) return 0;
  }
  return 1;
}