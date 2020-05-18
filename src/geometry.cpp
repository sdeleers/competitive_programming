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
