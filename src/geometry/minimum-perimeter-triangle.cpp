bool cmp_x(pt a, pt b) {return a.x < b.x;}
bool cmp_y(pt a, pt b) {return a.y < b.y;}
double dist(pt a, pt b) {return hypot(abs(a.x - b.x), abs(a.y - b.y));}
double perimeter(pt a, pt b, pt c) {return dist(a, b) + dist(b, c) + dist(c, a);}
double dac3(int l, int r) {
  // get the smallest triangle perimeter in pts[l, r]
  if (r - l <= 1) return INF;
  if (r - l == 2) return perimeter(pts[l], pts[l + 1], pts[l + 2]);
  int mid = (l + r) / 2;
  double d1 = dac3(l, mid), d2 = dac3(mid + 1, r);
  double ans = min(d1, d2);
  vector<pt> strip;
  for (int i = l; i <= r; i++) {
    if (abs(pts[i].x - pts[mid].x) < ans) strip.push_back(pts[i]);
  }
  sort(strip.begin(), strip.end(), cmp_y);
  for (int i = 0; i < strip.size(); i++) {
    for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < ans; j++) {
      for (int k = j + 1; k < strip.size() && (strip[k].y - strip[j].y) < ans; k++) {
        ans = min(ans, perimeter(strip[i], strip[j], strip[k]));
      }
    }
  }
  return ans;
}
double closest_triple(vector<pt> &pts) {
  sort(pts.begin(), pts.end(), cmp_x);
  return dac3(0, pts.size() - 1);
}
