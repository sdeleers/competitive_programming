template <class T>
struct FenwickTree {
  int N;
  std::vector<T> in;
  FenwickTree(int N) : N(N), in(N) {}
  void add(int at, T by) {
    for (int i = at; i < N; i += (i & -i)) {
      in[i] += by;
    }
  }
  T query(int at) {
    T sum = 0;
    for (int i = at; i; i -= (i & -i)) {
      sum += in[i];
    }
    return sum;
  }
};
