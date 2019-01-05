template <class T>
vector<T> getPrimeFactors(T n) {
  vector<T> prime_factors;
  // Print the number of 2s that divide n.
  while (n % 2 == 0) {
    prime_factors.push_back(2);
    n = n / 2;
  }

  // i must be odd at this point. So we can skip
  // one element (Note i = i + 2).
  for (int i = 3; i <= sqrt(n); i = i+2) {
    // While i divides n, add i and divide n.
    while (n % i == 0) {
      prime_factors.push_back(i);
      n = n / i;
    }
  }

  // This condition is to handle the case when n
  // is a prime number greater than 2.
  if (n > 2) {
    prime_factors.push_back(n);
  }

  return prime_factors;
}

template <class T>
vector<T> getDivisors(T n) {
  vector<T> divisors;

  for (int i = 1; i <= sqrt(n); ++i) {
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

template <class T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}
