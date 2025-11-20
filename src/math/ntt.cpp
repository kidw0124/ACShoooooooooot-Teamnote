void ntt(poly& f, bool inv = 0) {
  int n = f.size(), j = 0;
  vector<ll> root(n >> 1);
  for (int i = 1; i < n; i++) {
    int bit = (n >> 1);
    while (j >= bit) {
      j -= bit;
      bit >>= 1;
    }
    j += bit;
    if (i < j) swap(f[i], f[j]);
  }
  ll ang = pw(w, (mod - 1) / n);
  if (inv) ang = pw(ang, mod - 2);
  root[0] = 1;
  for (int i = 1; i < (n >> 1); i++) root[i] = root[i - 1] * ang % mod;
  for (int i = 2; i <= n; i <<= 1) {
    int step = n / i;
    for (int j = 0; j < n; j += i) {
      for (int k = 0; k < (i >> 1); k++) {
        ll u = f[j | k], v = f[j | k | i >> 1] * root[step * k] % mod;
        f[j | k] = (u + v) % mod; f[j | k | i >> 1] = (u - v) % mod;
        if (f[j | k | i >> 1] < 0) f[j | k | i >> 1] += mod;
      }
    }
  }
  ll t = pw(n, mod - 2);
  if (inv) for (int i = 0; i < n; i++) f[i] = f[i] * t % mod;
}

vector<ll> multiply(poly& _a, poly& _b) {
  vector<ll> a(all(_a)), b(all(_b));
  int n = 2;
  while (n < a.size() + b.size()) n <<= 1;
  a.resize(n);b.resize(n);ntt(a);ntt(b);
  for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;
  ntt(a, 1);
  return a;
}