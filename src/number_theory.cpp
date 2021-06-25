template <class T>
bool isPrime(T n) {
  if (n < 2) return false;
  for (T i = 2; i <= n / 2; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

template <class T>
vector<T> getPrimeFactors(T n) {
  vector<T> prime_factors;
  // Print the number of 2s that divide n.
  while (n % 2 == 0) {
    prime_factors.push_back(2);
    n = n / 2;
  }

  // i must be odd at this point. So we can do i = i + 2.
  for (int i = 3; i * i <= n; i = i+2) {
    // While i divides n, add i and divide n.
    while (n % i == 0) {
      prime_factors.push_back(i);
      n = n / i;
    }
  }

  if (n > 2) {
    // What remains must be a prime factor.
    prime_factors.push_back(n);
  }

  return prime_factors;
}

template <class T>
vector<T> getDivisors(T n) {
  vector<T> divisors;

  for (T i = 1; i <= sqrt(n); ++i) {
    if (n % i == 0) {
      if (n/i == i) {
        divisors.push_back(i);
      } else {
        divisors.push_back(i);
        divisors.push_back(n / i);
      }
    }
  }
  return divisors;
}

// Euclid's algorithm.
template <class T>
T gcd(T a, T b) {
  T a_mod_b = a % b;
  return a_mod_b == 0 ? b : gcd(b, a_mod_b);
}

// a + b modulo P
template <class T>
T add(T a, T b, T P) {
  T sum = a + b;
  if (sum >= P) {
    sum -= P;
  }
  return sum;
}

// Finds integers x, y such that Bézout identity holds:
// x * a + y * b = gcd(a, b).
template <class T>
T extendedEuclid(T a, T b, T& x, T& y) {
  // Base Case
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }

  T x1, y1; // To store results of recursive call
  T gcd = extendedEuclid(b % a, a, x1, y1);

  // Update x and y using results of recursive call.
  x = y1 - (b / a) * x1;
  y = x1;

  return gcd;
}

// a * b modulo P
template <class T>
T multiply(T a, T b, T P) {
  return (int64_t) a * b % P;
}

// Efficient calculation of a ^ b modulo P
template <class T>
T power(T a, T b, T P) {
  T result = 1;
  while (b > 0) {
    if (b & 1) {
      result = multiply(result, a, P);
    }
    b >>= 1;
    a = multiply(a, a, P);
  }
  return result;
}

// Modular inverse of a modulo P using Fermat's little theorem.
// Only works when P is a prime.
template <class T>
T inverseFermat(T a, T P) {
  return power(a, P - 2, P);
}

// Modular inverse of a modulo P using extended Euclid's algorithm.
// Always works (if inverse exists, i.e. when a and P are coprime).
template <class T>
T inverseEuclid(T a, T P) {
  T a_inverse, k;
  // a * a_inverse + k * P = 1
  extendedEuclid(a, P, a_inverse, k);
  return a_inverse;
}

const int MAX_VAL = 100000;
int64_t fact[MAX_VAL];
int64_t invfact[MAX_VAL];

template <class T>
void computeFactorials() {
  fact[0] = 1;
  fact[1] = 1;
  for (int i = 2; i < MAX_VAL; ++i) {
    fact[i] = i * fact[i - 1];
    if (fact[i] >= P) fact[i] %= P;
  }

  invfact[0] = 1;
  for (int i = 1; i < MAX_VAL; ++i) {
    invfact[i] = inverseEuclid<T>(fact[i], P);
    while (invfact[i] < 0) invfact[i] += P;
    if (invfact[i] >= P) invfact[i] %= P;
  }
}

// n choose k modulo P
template <class T>
T choose(T n, T k, T P) {
  if (k > n) {
    return 0;
  } else {
    return multiply(fact[n], multiply(invfact[k], invfact[n - k], P), P);
  }
}

void modularize(int64_t& number, int64_t P) {
  if (number >= P) {
    number %= P;
  } else if (number < 0) {
    if (number >= -P) {
      number += P;
    } else {
      int64_t positive = -number;
      modularize(positive, P);
      number = -positive + P;
    }
  }
}
