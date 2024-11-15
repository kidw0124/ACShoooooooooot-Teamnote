bool is_prime(i64 n) {
	if (n < 2 || n % 2 == 0 || n % 3 == 0) return n == 2 || n == 3;
	i64 k = __builtin_ctzll(n - 1), d = n - 1 >> k;
	for (i64 a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
		i64 p = modpow(a % n, d, n), i = k;
		while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
		if (p != n - 1 && i != k) return 0;
	}
	return 1;
}
i64 pollard(i64 n) {
	auto f = [n](i64 x) { return modadd(modmul(x, x, n), 3, n); };
	i64 x = 0, y = 0, t = 30, p = 2, i = 1, q;
	while (t++ % 40 || gcd(p, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if (q = modmul(p, abs(x - y), n)) p = q;
		x = f(x), y = f(f(y));
	}
	return gcd(p, n);
}
vector<i64> factor(i64 n) {
	if (n == 1) return {};
	if (is_prime(n)) return { n };
	i64 x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(), r.end());
	sort(l.begin(), l.end());
	return l;
}