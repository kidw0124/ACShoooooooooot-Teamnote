// Two-phase simplex algorithm for solving linear programs of the form
//   maximize   c^T x s.t.     Ax <= b; x >= 0
// A -- m x n mat, b -- m-dimensional vec, c -- n-dimensional vec
// return {value of the optimal solution, solution vector}
struct LPSolver {
  ll m, n;
  vector<ll> B, N;
  vector<vector<ld>> D;
  LPSolver(const vector<vector<ld>>& A, const vector<ld>& b, const vector<ld>& c):
    m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<ld>(n + 2)) {
    for (ll i = 0; i < m; i++) for (ll j = 0; j < n; j++) D[i][j] = A[i][j];
    for (ll i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
    for (ll j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
    N[n] = -1; D[m + 1][n] = 1;
  }
  void pivot(ll r, ll s) {
    ld inv = 1.0 / D[r][s];
    for (ll i = 0; i < m + 2; i++) if (i != r)
      for (ll j = 0; j < n + 2; j++) if (j != s)
        D[i][j] -= D[r][j] * D[i][s] * inv;
    for (ll j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
    for (ll i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv; swap(B[r], N[s]);
  }
  bool simplex(ll phase) {
    ll x = phase == 1 ? m + 1 : m;
    while (true) {
      ll s = -1;
      for (ll j = 0; j <= n; j++) {
        if (phase == 2 && N[j] == -1) continue;
        if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
      }
      if (D[x][s] > -EPS) return true;
      ll r = -1;
      for (ll i = 0; i < m; i++) {
        if (D[i][s] < EPS) continue;
        if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
          (D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r]) r = i;
      }
      if (r == -1) return false;
      pivot(r, s);
    }
  }
  pair<ld,vector<ld>> solve() {
    ll r = 0; vector<ld> x(n);
    for (ll i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -EPS) {
      pivot(r, n);
      if (!simplex(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<ld>::infinity();
      for (ll i = 0; i < m; i++) if (B[i] == -1) {
        ll s = -1;
        for (ll j = 0; j <= n; j++)if(s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s])s=j;
        pivot(i, s);
      }
    }
    if (!simplex(2)) return numeric_limits<ld>::infinity();
    for (ll i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
    return D[m][n + 1];
  }
};