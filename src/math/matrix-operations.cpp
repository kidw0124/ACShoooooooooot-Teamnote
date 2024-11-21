inline bool is_zero(ld a) { return abs(a) < eps; }
// returns {det(A), A^-1, rank(A), tr(A)}
// A becomes invalid after call this O(n^3)
tuple<ld,vector<vector<ld>>,ll,ll> inv_det_rnk(auto A) {
  ld n=A.size(); ld det = 1; vector out(n, vector<ld>(n)); ld tr=0;
  for (int i = 0; i < n; i++) {
    out[i][i] = 1; tr+=A[i][i];
  }
  for (int i = 0; i < n; i++) {
    if (is_zero(A[i][i])) {
      ld maxv = 0;
      int maxid = -1;
      for (int j = i + 1; j < n; j++) {
        auto cur = abs(A[j][i]);
        if (maxv < cur) {
          maxv = cur;
          maxid = j;
        }
      }
      if (maxid == -1 || is_zero(A[maxid][i])) return {0, out, i, tr};
      for (int k = 0; k < n; k++) {
        A[i][k] += A[maxid][k]; out[i][k] += out[maxid][k];
      }
    }
    det *= A[i][i];
    ld coeff = 1.0 / A[i][i];
    for (int j = 0; j < n; j++) A[i][j] *= coeff,out[i][j] *= coeff;
    for (int j = 0; j < n; j++) if (j != i) {
      ld mp = A[j][i];
      for (int k = 0; k < n; k++) A[j][k] -= A[i][k] * mp;
      for (int k = 0; k < n; k++) out[j][k] -= out[i][k] * mp;
    }
  }
  return {det, out, n, tr};
}