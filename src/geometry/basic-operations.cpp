const ld eps = 1e-12;
inline ll diff(ld lhs, ld rhs) {
  if (lhs - eps < rhs && rhs < lhs + eps) return 0;
  return (lhs < rhs) ? -1 : 1;
}
inline bool is_between(ld check, ld a, ld b) {
  return (a < b) ? (a - eps < check && check < b + eps)
                 : (b - eps < check && check < a + eps);
}
struct Point {
  ld x, y;
  bool operator==(const Point& rhs) const {
    return diff(x, rhs.x) == 0 && diff(y, rhs.y) == 0;
  }
  Point operator+(const Point& rhs) const { return Point{x + rhs.x, y + rhs.y}; }
  Point operator-(const Point& rhs) const { return Point{x - rhs.x, y - rhs.y}; }
  Point operator*(ld t) const { return Point{x * t, y * t}; }
  int pos() const {
    if (y < 0) return -1;
    if (y == 0 && 0 <= x) return 0;
    return 1;
  }
  bool operator<(Point r) const { // sort by angle, ccw order from half line x≤0,y=0
      if (pos() != r.pos()) return pos() < r.pos();
      return 0 < (x * r.y - y * r.x);
  }
  Point rotate(ld theta) const {// rotate ccw by theta
    return Point{x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta)};
  }
};
struct Circle {
  Point center;
  ld r;
};
struct Line {
  Point pos, dir;
};
inline ld inner(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
inline ld outer(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
inline ll ccw_line(const Line& line, const Point& point) {
  return diff(outer(line.dir, point - line.pos), 0);
}
inline ll ccw(const Point& a, const Point& b, const Point& c) {
  return diff(outer(b - a, c - a), 0);
}
inline ld dist(const Point& a, const Point& b) { return sqrt(inner(a - b, a - b)); }
inline ld dist2(const Point& a, const Point& b) { return inner(a - b, a - b); }
inline ld dist(const Line& line, const Point& point, bool segment = false) {
  ld c1 = inner(point - line.pos, line.dir);
  if (segment && diff(c1, 0) <= 0) return dist(line.pos, point);
  ld c2 = inner(line.dir, line.dir);
  if (segment && diff(c2, c1) <= 0) return dist(line.pos + line.dir, point);
  return dist(line.pos + line.dir * (c1 / c2), point);
}
bool get_cross(const Line& a, const Line& b, Point& ret) {
  ld mdet = outer(b.dir, a.dir);
  if (diff(mdet, 0) == 0) return false;
  ld t2 = outer(a.dir, b.pos - a.pos) / mdet;
  ret = b.pos + b.dir * t2;
  return true;
}
bool get_segment_cross(const Line& a, const Line& b, Point& ret) {
  ld mdet = outer(b.dir, a.dir);
  if (diff(mdet, 0) == 0) return false;
  ld t1 = -outer(b.pos - a.pos, b.dir) / mdet;
  ld t2 = outer(a.dir, b.pos - a.pos) / mdet;
  if (!is_between(t1, 0, 1) || !is_between(t2, 0, 1)) return false;
  ret = b.pos + b.dir * t2;
  return true;
}
Point inner_center(const Point& a, const Point& b, const Point& c) {
  ld wa = dist(b, c), wb = dist(c, a), wc = dist(a, b);
  ld w = wa + wb + wc;
  return Point{(wa * a.x + wb * b.x + wc * c.x) / w,
               (wa * a.y + wb * b.y + wc * c.y) / w};
}
Point outer_center(const Point& a, const Point& b, const Point& c) {
  Point d1 = b - a, d2 = c - a;
  ld area = outer(d1, d2);
  ld dx = d1.x * d1.x * d2.y - d2.x * d2.x * d1.y + d1.y * d2.y * (d1.y - d2.y);
  ld dy = d1.y * d1.y * d2.x - d2.y * d2.y * d1.x + d1.x * d2.x * (d1.x - d2.y);
  return Point{a.x + dx / area / 2.0, a.y - dy / area / 2.0};
}
vector<Point> circle_line(const Circle& circle, const Line& line) {
  vector<Point> result;
  ld a = 2 * inner(line.dir, line.dir);
  ld b = 2 * (line.dir.x * (line.pos.x - circle.center.x) +
              line.dir.y * (line.pos.y - circle.center.y));
  ld c = inner(line.pos - circle.center, line.pos - circle.center) - circle.r * circle.r;
  ld det = b * b - 2 * a * c;
  ll pred = diff(det, 0);
  if (pred == 0)
    result.push_back(line.pos + line.dir * (-b / a));
  else if (pred > 0) {
    det = sqrt(det);
    result.push_back(line.pos + line.dir * ((-b + det) / a));
    result.push_back(line.pos + line.dir * ((-b - det) / a));
  }
  return result;
}
vector<Point> circle_circle(const Circle& a, const Circle& b) {
  vector<Point> result;
  ll pred = diff(dist(a.center, b.center), a.r + b.r);
  if (pred > 0) return result;
  if (pred == 0) {
    result.push_back((a.center * b.r + b.center * a.r) * (1 / (a.r + b.r)));
    return result;
  }
  ld aa = a.center.x * a.center.x + a.center.y * a.center.y - a.r * a.r;
  ld bb = b.center.x * b.center.x + b.center.y * b.center.y - b.r * b.r;
  ld tmp = (bb - aa) / 2.0;
  Point cdiff = b.center - a.center;
  if (diff(cdiff.x, 0) == 0) {
    if (diff(cdiff.y, 0) == 0) return result;
    return circle_line(a, Line{Point{0, tmp / cdiff.y}, Point{1, 0}});
  }
  return circle_line(a, Line{Point{tmp / cdiff.x, 0}, Point{-cdiff.y, cdiff.x}});
}
Circle circle_from_3pts(const Point& a, const Point& b, const Point& c) {
  Point ba = b - a, cb = c - b;
  Line p{(a + b) * 0.5, Point{ba.y, -ba.x}};
  Line q{(b + c) * 0.5, Point{cb.y, -cb.x}};
  Circle circle;
  if (!get_cross(p, q, circle.center))
    circle.r = -1;
  else
    circle.r = dist(circle.center, a);
  return circle;
}
Circle circle_from_2pts_rad(const Point& a, const Point& b, ld r) {
  ld det = r * r / dist2(a, b) - 0.25;
  Circle circle;
  if (det < 0)
    circle.r = -1;
  else {
    ld h = sqrt(det);
    // center is to the left of a->b
    circle.center = (a + b) * 0.5 + Point{a.y - b.y, b.x - a.x} * h;
    circle.r = r;
  }
  return circle;
}
Circle circle_from_2pts(const Point& a, const Point& b) {
  Circle circle;
  circle.center = (a + b) * 0.5;
  circle.r = dist(a, b) / 2;
  return circle;
}
