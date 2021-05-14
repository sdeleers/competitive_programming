class Fraction {
 public:
  int64_t num;
  int64_t den;

  Fraction(int64_t n, int64_t d) : num(n), den(d) {
    normalize();
  }

  void normalize() {
    const int64_t g = gcd(num, den);
    num = num / g;
    den = den / g;
  }

  bool operator>(const Fraction& f) const { return num * f.den > den * f.num;}
  bool operator<(const Fraction& f) const { return num * f.den < den * f.num;}
  bool operator<=(const Fraction& f) const { return num * f.den <= den * f.num;}
  bool operator>=(const Fraction& f) const { return num * f.den >= den * f.num;}
  bool operator==(const Fraction& f) const { return num * f.den == den * f.num;}

  Fraction& operator+=(const Fraction& rhs) {
    int64_t new_den = den * rhs.den;
    int64_t new_num = num * rhs.den + den * rhs.num;

    num = new_num;
    den = new_den;
    normalize();
    return *this;
  }

  Fraction& operator-=(const Fraction& rhs) {
    int64_t new_den = den * rhs.den;
    int64_t new_num = num * rhs.den - den * rhs.num;
    
    num = new_num;
    den = new_den;
    normalize();
    return *this;
  }

  Fraction& operator*=(const Fraction& rhs) {
    num *= rhs.num;
    den *= rhs.den;
    normalize();
    return *this;
  }

  Fraction& operator/=(const Fraction& rhs) {
    num *= rhs.den;
    den *= rhs.num;
    normalize();
    return *this;
  }

  friend Fraction operator*(const Fraction &a, const Fraction &b) { return Fraction(a) *= b; }
  friend Fraction operator/(const Fraction &a, const Fraction &b) { return Fraction(a) /= b; }
  friend Fraction operator+(const Fraction &a, const Fraction &b) { return Fraction(a) += b; }
  friend Fraction operator-(const Fraction &a, const Fraction &b) { return Fraction(a) -= b; }
};
