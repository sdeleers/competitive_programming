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

vector<mod_int> fact;
vector<mod_int> inverse_fact;

void computeFactorials(int max_value) {
  const int num_already_computed = fact.size();
  max_value = max(1, max_value);
  if (num_already_computed > max_value) return;  // Already computed.

  fact.resize(max_value + 1);
  inverse_fact.resize(max_value + 1);
  fact[0] = 1;
  fact[1] = 1;
  for (int64_t i = max(2, num_already_computed); i <= max_value; ++i) {
    fact[i] = i * fact[i - 1];
  }

  inverse_fact[max_value] = 1 / fact[max_value];
  for (int64_t i = max_value - 1; i >= num_already_computed; --i) {
    inverse_fact[i] = (i + 1) * inverse_fact[i + 1];
  }
}

mod_int factorial(int64_t n) {
  if (n < 0) return 0;
  computeFactorials(n);
  return fact[n];
}

mod_int inverse_factorial(int64_t n) {
  if (n < 0) return 0;
  computeFactorials(n);
  return inverse_fact[n];
}

mod_int choose(int64_t n, int64_t k) {
  if (n < 0 || k > n) return 0;
  computeFactorials(n);
  return fact[n] * inverse_fact[k] * inverse_fact[n - k];
}
