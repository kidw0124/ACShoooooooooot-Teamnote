// (fwht_or(a))_i = sum of a_j for all j s.t. i | j = j
// (fwht_and(a))_i = sum of a_j for all j s.t. i & j = i
// x @ y = popcount(x & y) mod 2
// (fwht_xor(a))_i = (sum of a_j for all j s.t. i @ j = 0)
//                   - (sum of a_j for all j s.t. i @ j = 1)
// inv = 0 for fwht, 1 for ifwht(inverse fwht)
// {convolution(a,b)}_i = sum of a_j * b_k for all j,k s.t. j op k = i
//  = ifwht(fwht(a) * fwht(b))
vector<ll> fwht_or(vector<ll> &x, bool inv) {
  vector<ll> a = x; ll n = a.size();
  int dir = inv ? -1 : 1;
  for(int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
    for(int l = 0; l < n; l += s) {
      for(int i = 0; i < h; i++)a[l + h + i] += dir * a[l + i];
    }
  }
  return a;
}
vector<ll> fwht_and(vector<ll> &x, bool inv) {
  vector<ll> a = x; ll n = a.size();
  int dir = inv ? -1 : 1;
  for(int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
    for(int l = 0; l < n; l += s) {
      for(int i = 0; i < h; i++)a[l + h] += dir * a[l + h + i];
    }
  }
  return a;
}
vector<ll> fwht_xor(vector<ll> &x, bool inv) {
  vector<ll> a = x;
  ll n = a.size();
  for(int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
    for(int l = 0; l < n; l += s) {
      for(int i = 0; i < h; i++) {
        int t = a[l + h + i];a[l + h + i] = a[l + i] - t;a[l + i] += t;
        if(inv) a[l + h + i] /= 2, a[l + i] /= 2;
      }
    }
  }
  return a;
}