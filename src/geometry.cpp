struct Point {
  double x;
  double y;
};

struct Circle {
  Point p;
  double r;
};

double distance(const Point& p1, const Point& p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

vector<Point> intersect(const Circle& c1, const Circle& c2) {
  double eps = 0;
  double dist = distance(c1.p, c2.p);
  double rsum = c1.r + c2.r;
  double rdiff = abs(c1.r - c2.r);
  if (dist > rsum || dist < rdiff || (dist < eps && rdiff < eps)) {  // No intersections.
    return {};
  } else {
    double dx = c2.p.x - c1.p.x;
    double dy = c2.p.y - c1.p.y;
    double x = (dist * dist + c1.r * c1.r - c2.r * c2.r) / (2 * dist);
    if (abs(dist - rsum) < eps || abs(dist - rdiff) < eps) {  // 1 intersection.
      return { { c1.p.x + (x * dx) / dist, c1.p.y + (x * dy) / dist } };
    } else {  // 2 intersections.
      double y = sqrt(abs(c1.r * c1.r - x * x));
      return { { c1.p.x + (x * dx - y * dy) / dist, c1.p.y + (x * dy + y * dx) / dist },
               { c1.p.x + (x * dx + y * dy) / dist, c1.p.y + (x * dy - y * dx) / dist } };
    }
  }
}
