/* Solve x for x^P = A mod Q
 * O((lgQ)^2 + Q^0.25 (lgQ)^3)
 * (P, Q-1) = 1 -> P^-1 mod (Q-1) exists
 * x has solution iff A^((Q-1) / P) = 1 mod Q
 * PP | (Q-1) -> P < sqrt(Q), solve lgQ rounds of discrete log
 * else -> find a s.t. s | (Pa - 1) -> ans = A^a */
const int X = 1e5;
ll base, ae[X], aXe[X], iaXe[X];
unordered_map<ll, ll> ht;
#define FOR(i, c) for (int i = 0; i < (c); ++i)
#define REP(i, l, r) for (int i = (l); i <= (r); ++i)
void build(ll a) { // ord(a) = P < sqrt(Q)
  base = a;
  ht.clear();
  ae[0] = 1; ae[1] = a; aXe[0] = 1; aXe[1] = pw(a, X, Q);
  iaXe[0] = 1; iaXe[1] = pw(aXe[1], Q-2, Q);
  REP(i, 2, X-1) {
    ae[i] = mul(ae[i-1], ae[1], Q);
    aXe[i] = mul(aXe[i-1], aXe[1], Q);
    iaXe[i] = mul(iaXe[i-1], iaXe[1], Q);
  }
  FOR(i, X) ht[ae[i]] = i;
}
ll dis_log(ll x) {
  FOR(i, X) {
    ll iaXi = iaXe[i];
    ll rst = mul(x, iaXi, Q);
    if (ht.count(rst)) return i*X + ht[rst];
  }
}
ll main2() {
  ll g;
  ll t = 0, s = Q-1;
  while (s % P == 0) {
    ++t;
    s /= P;
  }
  if (A == 0) return 0;
  if (t == 0) {
    // a^{P^-1 mod phi(Q)}
    auto [x, y, _] = extended_gcd(P, Q-1);
    if (x < 0) {
      x = (x % (Q-1) + Q-1) % (Q-1);
    }
    ll ans = pw(A, x, Q);
    if (pw(ans, P, Q) != A) while(1);
    return ans;
  }
  // A is not P-residue
  if (pw(A, (Q-1) / P, Q) != 1) return -1;
  for (g = 2; g < Q; ++g) {
    if (pw(g, (Q-1) / P, Q) != 1) break;
  }
  ll alpha = 0;
  {
    ll y, _;
    gcd(P, s, alpha, y, _);
    if (alpha < 0) alpha = (alpha % (Q-1) + Q-1) % (Q-1);
  }
  if (t == 1) {
    ll ans = pw(A, alpha, Q);
    return ans;
  }
  ll a = pw(g, (Q-1) / P, Q);
  build(a);
  ll b = pw(A, add(mul(P%(Q-1), alpha, Q-1), Q-2, Q-1), Q);
  ll c = pw(g, s, Q);
  ll h = 1;
  ll e = (Q-1) / s / P; // r^{t-1}
  REP(i, 1, t-1) {
    e /= P;
    ll d = pw(b, e, Q);
    ll j = 0;
    if (d != 1) {
      j = -dis_log(d);
      if (j < 0) j = (j % (Q-1) + Q-1) % (Q-1);
    }
    b = mul(b, pw(c, mul(P%(Q-1), j, Q-1), Q), Q);
    h = mul(h, pw(c, j, Q), Q);
    c = pw(c, P, Q);
  }
  return mul(pw(A, alpha, Q), h, Q);
}
// only for sqrt
void calcH(int &t, int &h, const int p) {
	int tmp=p-1; for(t=0;(tmp&1)==0;tmp/=2) t++; h=tmp;
}
// solve equation x^2 mod p = a
bool solve(int a, int p, int &x, int &y) {
	if(p == 2) { x = y = 1; return true; }
	int p2 = p / 2, tmp = pw(a, p2, p);
	if (tmp == p - 1) return false;
	if ((p + 1) % 4 == 0) {
		x=pw(a,(p+1)/4,p); y=p-x; return true;
	} else {
		int t, h, b, pb; calcH(t, h, p);
		if (t >= 2) {
			do {b = rand() % (p - 2) + 2;
			} while (pw(b, p / 2, p) != p - 1);
			pb = pw(b, h, p);
		} int s = pw(a, h / 2, p);
		for (int step = 2; step <= t; step++) {
			int ss = (((ll)(s * s) % p) * a) % p;
			for(int i=0;i<t-step;i++) ss=mul(ss,ss,p);
			if (ss + 1 == p) s = (s * pb) % p;
      pb = ((ll)pb * pb) % p;
		} x = ((ll)s * a) % p; y = p - x;
	} return true; 
}