template <int MOD>
struct ModInt {
  int _v;

  ModInt(int64_t v = 0) {
    if (v < 0) v = v % MOD + MOD;
    if (v >= MOD) v %= MOD;
    _v = int(v);
  }

  ModInt(uint64_t v) {
    if (v >= MOD) v %= MOD;
    _v = int(v);
  }

  ModInt(int v) : ModInt(int64_t(v)) {}
  ModInt(unsigned v) : ModInt(uint64_t(v)) {}

  ModInt& operator++() {
    ++_v;
    if (_v == MOD) _v = 0;
    return *this;
  }

  ModInt& operator--() {
    if (_v == 0) _v = MOD;
    --_v;
    return *this;
  }

  ModInt& operator+=(const ModInt& rhs) {
    _v += rhs._v;
    if (_v >= MOD) _v -= MOD;
    return *this;
  }

  ModInt& operator-=(const ModInt& rhs) {
    _v -= rhs._v;
    if (_v < 0) _v += MOD;
    return *this;
  }

  ModInt& operator*=(const ModInt& rhs) {
    int64_t z = _v;
    z *= rhs._v;
    _v = z % MOD;
    return *this;
  }

  ModInt power(int64_t p) const {
    if (p < 0) return inverse().power(-p);

    ModInt result = 1;
    ModInt a = *this;
    while (p > 0) {
      if (p & 1) {
        result *= a;
      }
      p >>= 1;
      a *= a;
    }
    return result;
  }

  // Modular inverse of a modulo P using Fermat's little theorem.
  // Only works when P is a prime.
  ModInt inverse() const {
    return power(MOD - 2);
  }

  ModInt& operator/=(const ModInt& rhs) {
      return *this *= rhs.inverse();
  }

  ModInt operator++(int) { ModInt before = *this; ++*this; return before; }
  ModInt operator--(int) { ModInt before = *this; --*this; return before; }

  friend ModInt operator*(const ModInt &a, const ModInt &b) { return ModInt(a) *= b; }
  friend ModInt operator+(const ModInt &a, const ModInt &b) { return ModInt(a) += b; }
  friend ModInt operator-(const ModInt &a, const ModInt &b) { return ModInt(a) -= b; }
  friend ModInt operator/(const ModInt &a, const ModInt &b) { return ModInt(a) /= b; }

  friend bool operator==(const ModInt &a, const ModInt &b) { return a.val == b.val; }
  friend bool operator!=(const ModInt &a, const ModInt &b) { return a.val != b.val; }
  friend bool operator<(const ModInt &a, const ModInt &b) { return a.val < b.val; }
  friend bool operator>(const ModInt &a, const ModInt &b) { return a.val > b.val; }
  friend bool operator<=(const ModInt &a, const ModInt &b) { return a.val <= b.val; }
  friend bool operator>=(const ModInt &a, const ModInt &b) { return a.val >= b.val; }

  friend ostream& operator<<(ostream &os, const ModInt& a) { return os << a._v; }
};
 
const int MOD = 998244353;
using mod_int = ModInt<MOD>;
