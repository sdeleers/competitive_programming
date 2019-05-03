template <class T>
struct RangeMaximumQuery {
  vector<T> arr;
  vector<vector<T>> table;

  RangeMaximumQuery(const vector<T>& a) : arr(a) {
    precompute();
  };

  void precompute() {
    int N = arr.size();
    int logN = log2(N);
    table = vector<vector<T>>(N, vector<T>(logN + 1));

    // Bottom up DP. Base cases.
    for (int i = 0; i < N; ++i) {
      table[i][0] = arr[i];
    }

    // Recursion. Loop over length (i.e. j) should be first.
    for (int j = 1; j < logN + 1; ++j) {
      for (int i = 0; i + (1 << j) - 1 < N; ++i) {
        table[i][j] = max(table[i][j - 1],
                          table[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  int query(int left, int right) {
    if (left == right) return table[left][0];
    int k = log2(right - left);
    T answer = max(table[left][k],
                   table[right - (1 << k) + 1][k]);
    return answer;
  }
};
