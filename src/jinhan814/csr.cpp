vector e(m, tuple(0, 0, 0));
for (auto& [a, b, c] : e) cin >> a >> b >> c;
vector cnt(n + 2, 0); vector csr(m, pair(0, 0));
for (auto [a, b, c] : e) cnt[a + 1]++;
for (int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i - 1];
for (auto [a, b, c] : e) csr[cnt[a]++] = pair(b, c);
int cur = /* ... */;
for (int i = cnt[cur - 1]; i < cnt[cur]; i++) {
  auto [nxt, cost] = csr[i]; /* ... */
}