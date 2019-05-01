// Gaussian elimination code based on code from book
// Competitive Programming 3 by Steven and Felix Halim.
// Solve A * x = b.
// matrix: augmented matrix of size N x (N + 1). [A | b]
// solution: vector of length N
bool gaussianElimination(int N,
                         vector<vector<double>>& matrix,
                         vector<double>& solution) {
  solution.resize(N);
  fill(solution.begin(), solution.end(), 0);
  // Forward elimination.
  for (int j = 0; j < N - 1; ++j) {
    int l = j;
    for (int i = j + 1; i < N; ++i) {
      if (fabs(matrix[i][j]) > fabs(matrix[l][j])) {
        l = i;
      }
    }

    for (int k = j; k <= N; ++k) {
      double tmp = matrix[j][k];
      matrix[j][k] = matrix[l][k];
      matrix[l][k] = tmp;
    }

    for (int i = j + 1; i < N; ++i) {
      for (int k = N; k >= j; --k) {
        matrix[i][k] -= matrix[j][k] * matrix[i][j] / matrix[j][j];
      }
    }
  }
  // Back substitution.
  for (int j = N - 1; j >= 0; --j) {
    double tmp = 0.0;
    for (int k = j + 1; k < N; ++k) {
      tmp += matrix[j][k] * solution[k];
    }
    solution[j] = (matrix[j][N] - tmp) / matrix[j][j];
    if (isnan(solution[j])) return false;
  }
  return true;
}
