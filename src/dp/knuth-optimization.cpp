for (i = 1; i <= n; i++) {
  cin >> a[i];
  s[i] = s[i - 1] + a[i]; dp[i - 1][i] = 0; assist[i - 1][i] = i;
}
for (i = 2; i <= n; i++) {
  for (j = 0; j <= n - i; j++) {
    dp[j][i + j] = 1e9 + 7;
    for (k = assist[j][i + j - 1]; k <= assist[j + 1][i + j]; k++) {
      if (dp[j][i + j] > dp[j][k] + dp[k][i + j] + s[i + j] - s[j]) {
        dp[j][i + j] = dp[j][k] + dp[k][i + j] + s[i + j] - s[j];
        assist[j][i + j] = k;
      }
    }
  }
}