// Z[i] : maximum common prefix length of &s[0] and &s[i] with O(|s|)
auto get_z = [](const string& s) {
  const int n = s.size(); vector z(n, 0); z[0] = n;
  for (int i = 1, l = -1, r = -1; i < n; i++) {
  if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (r < i + z[i] - 1) l = i, r = i + z[i] - 1;
  }
  return z;
};