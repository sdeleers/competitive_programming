struct Point {
  int64_t x;
  int64_t y;

  Point operator-(const Point& rhs) const {
    return { x - rhs.x, y - rhs.y };
  }

  double length() const {
    return sqrt(x * x + y * y);
  }

  bool operator<(const Point& p) const {
    if (x != p.x) {
      return x < p.x;
    } else {
      return y < p.y;
    }
  }
};

int64_t cross(const Point& a, const Point& b) {
  return a.x * b.y - a.y * b.x;
}

bool strict_cw(const Point& a, const Point& b, const Point& c) {
  return cross(b - a, c - a) < 0;
}

bool cw(const Point& a, const Point& b, const Point& c) {
  return cross(b - a, c - a) <= 0;
}

bool strict_ccw(const Point& a, const Point& b, const Point& c) {
  return cross(b - a, c - a) > 0;
}

bool ccw(const Point& a, const Point& b, const Point& c) {
  return cross(b - a, c - a) >= 0;
}

vector<Point> convexHull(vector<Point>& points) {
  const int N = points.size();
  sort(points.begin(), points.end());
  const Point& a = points.front();
  const Point& b = points.back();
  
  vector<Point> upper = { a };
  vector<Point> lower = { a };
  for (int i = 1; i + 1 < N; ++i) {
    const Point& p = points[i];
    if (strict_ccw(a, b, p)) {   // Upper.
      // Potentially remove older points.
      while (upper.size() >= 2 && ccw(upper[upper.size() - 2], upper.back(), p)) {
        upper.pop_back();
      }

      // Should we add current point?
      if (strict_cw(upper.back(), p, b)) {
        upper.push_back(p);
      }
    } else if (strict_cw(a, b, p)) {  // Lower.
      // Potentially remove older points.
      while (lower.size() >= 2 && cw(lower[lower.size() - 2], lower.back(), p)) {
        lower.pop_back();
      }

      // Should we add current point?
      if (strict_ccw(lower.back(), p, b)) {
        lower.push_back(p);
      }
    }
  }
  upper.push_back(b);

  reverse(lower.begin(), lower.end());
  if (!lower.empty()) lower.pop_back();  // Remove a.

  for (const auto& point : lower) {
    upper.push_back(point);
  }

  return upper;
}

vector<vector<Point>> convexHullSegments(vector<Point>& points) {
  const int N = points.size();
  sort(points.begin(), points.end());
  const Point& a = points.front();
  const Point& b = points.back();
  
  vector<Point> upper = { a };
  vector<Point> lower = { a };
  for (int i = 1; i + 1 < N; ++i) {
    const Point& p = points[i];
    if (strict_ccw(a, b, p)) {   // Upper.
      // Potentially remove older points.
      while (upper.size() >= 2 && strict_ccw(upper[upper.size() - 2], upper.back(), p)) {
        upper.pop_back();
      }

      // Should we add current point?
      if (strict_cw(upper.back(), p, b)) {
        upper.push_back(p);
      }
    } else if (strict_cw(a, b, p)) {  // Lower.
      // Potentially remove older points.
      while (lower.size() >= 2 && strict_cw(lower[lower.size() - 2], lower.back(), p)) {
        lower.pop_back();
      }

      // Should we add current point?
      if (strict_ccw(lower.back(), p, b)) {
        lower.push_back(p);
      }
    }
  }
  lower.push_back(b);
  upper.push_back(b);
  return { lower, upper };
}

int64_t dot(const Point& a, const Point& b) {
  return a.x * b.x + a.y * b.y;
}

vector<Point> normalDirections(const Point& direction) {
  return { { direction.y, -direction.x }, { -direction.y, direction.x } };
}

Point farthestPointInDirection(const vector<Point>& hull_segment, const Point& direction) {
  // Binary search on edges (i.e. ternary search on points).
  int lo = 0;
  int hi = hull_segment.size() - 2;
  while (lo < hi) {
    const int mid = lo + (hi - lo) / 2;
    const auto dot1 = dot(direction, hull_segment[mid]);
    const auto dot2 = dot(direction, hull_segment[mid + 1]);
    if (dot1 == dot2) {
      return hull_segment[mid];
    } else if (dot1 > dot2) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  // Only one edge left, take the farthest end point.
  const auto dot1 = dot(direction, hull_segment[lo]);
  const auto dot2 = dot(direction, hull_segment[lo + 1]);
  return (dot1 > dot2) ? hull_segment[lo] : hull_segment[lo + 1];
}

double pointToLineDistance(const Point& a, const Point& b, const Point& p) {
  const double k = (p - a).length();
  const double l = abs(dot(p - a, b - a)) / (b - a).length();
  // k * k = l * l + m * m
  const double m = sqrt(k * k - l * l);
  return m;
}

// ------------------------------

struct Point {
  double x;
  double y;
};

// Represents the (normalized) direction of a line
// There is no "opposite direction", i.e. the == operator will
// return true for (-1, -1) == (1, 1).
struct Direction {
  long long x;
  long long y;

  Direction(long long x_dir, long long y_dir) {
    long long g = __gcd(abs(x_dir), abs(y_dir));
    if (g > 0) {
      x_dir /= g;
      y_dir /= g;
    }

    if (x_dir == 0) {
      y_dir = abs(y_dir);
    } else if (y_dir == 0) {
      x_dir = abs(x_dir);
    } else if (x_dir < 0) {
      x_dir *= -1;
      y_dir *= -1;
    }
    
    x = x_dir;
    y = y_dir;
  }

  bool operator<(const Direction& dir) const {
    if (x != dir.x) return x < dir.x;
    if (y != dir.y) return y < dir.y;
    return false;
  }

  bool operator==(const Direction& dir) const {
    return x == dir.x && y == dir.y;
  }
};

// Collinear lines represent the same line.
// == operator returns true if lines are collinear.
struct Line {
  Direction direction;
  Point p; // any point on the line.

  Line(const Point& p1, const Point& p2) : direction(p1.x - p2.x, p1.y - p2.y), p(p1) {
  }

  bool goesThrough(const Point& point) const {
    Direction d(point.x - p.x, point.y - p.y);
    if (d.x == 0 && d.y == 0) return true;
    return direction == d;
  }

  bool operator==(const Line& line) const {
    return direction == line.direction && goesThrough(line.p);
  }
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
