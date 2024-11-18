// find longest palindromic span for each element in str with O(|str|)
auto manacher = [](const string& s) {
  const int n = s.size();
  vector d(n, 0);
  for (int i = 0, l = -1, r = -1; i < n; i++) {
    if (i < r) d[i] = min(r - i, d[l + r - i]);
    while (d[i] < min(i + 1, n - i) && s[i - d[i]] == s[i + d[i]]) d[i]++;
    if (i + d[i] > r) l = i - d[i], r = i + d[i];
  }
  return d;
};