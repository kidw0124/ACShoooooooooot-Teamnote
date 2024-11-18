// Extended Euclidean Algorithm, O(lgn)
// ax+by=g, return (g,x,y)
tuple<ll, ll, ll> extended_gcd(ll a, ll b){
  if (a == 0) {b, 0, 1};
  auto [g, x, y] = extended_gcd(b % a, a);
  return {g, y - (b / a) * x, x};
}
// find x in [0,m) s.t. ax === gcd(a, m) (mod m)
ll modinverse(ll a, ll m) {
    return (get<1>(extended_gcd(a, m))%m+m)%m;
}