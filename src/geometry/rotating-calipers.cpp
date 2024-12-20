// get all antipodal pairs with O(n)
// calculate convex hull with O(nlgn)
void antipodal_pairs(vector<Point>& pt, vector<Point>& convex_hull) {
  sort(pt.begin(), pt.end(), [](const Point& a, const Point& b) {
    return (a.x == b.x) ? a.y < b.y : a.x < b.x;
  });
  vector<Point> up, lo;
  for (const auto& p : pt) {
    while (up.size() >= 2 && ccw(*++up.rbegin(), *up.rbegin(), p) >= 0) up.pop_back();
    while (lo.size() >= 2 && ccw(*++lo.rbegin(), *lo.rbegin(), p) <= 0) lo.pop_back();
    up.push_back(p);
    lo.push_back(p);
  }
  for (int i = 0, j = (int)lo.size() - 1; i + 1 < up.size() || j > 0;) {
    get_pair(up[i], lo[j]);  // DO WHAT YOU WANT
    if (i + 1 == up.size()) --j;
    else if (j == 0) ++i;
    else if ((up[i + 1].y - up[i].y) * (lo[j].x - lo[j - 1].x) >
               (up[i + 1].x - up[i].x) * (lo[j].y - lo[j - 1].y))++i;
    else--j;
  }
  upper.insert(upper.end(), ++lower.rbegin(), --lower.rend());
  swap(upper, convex_hull);
}