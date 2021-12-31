// Ax = b % P
// A does not need to be square, equations can be over/under determined.
// matrix = [A | b]
// Validation of the solution needs to happen outside of this function.
// Because if there exists no solution, a solution will be returned anyway.
void gaussianElimination(int N,
                         vector<vector<mod_int>>& matrix,
                         vector<mod_int>& solution) {                         
  const int num_rows = matrix.size();                                 
  solution.resize(N);
  fill(solution.begin(), solution.end(), 0);
  // Forward elimination.
  int current_row = 0;
  for (int current_col = 0; current_col +  1 < N; ++current_col) {
    if (current_row >= matrix.size()) break;
    int selected_row = current_row;
    for (int row = current_row + 1; row < num_rows; ++row) {
      if (matrix[row][current_col] > matrix[selected_row][current_col]) {
        selected_row = row;
      }
    }

    // There is nothing with a '1' left. We will be able to choose whatever we want for this edge.
    if (matrix[selected_row][current_col] == 0) continue;

    // Put selected row in position.
    for (int col = current_col; col <= N; ++col) {
      swap(matrix[current_row][col], matrix[selected_row][col]);
    }

    // Subtract rows from selected row.
    for (int row = current_row + 1; row < num_rows; ++row) {
      const auto first_number_current_row = matrix[current_row][current_col];
      const auto first_number_row = matrix[row][current_col];
      if (first_number_row == 0) continue;  // Speed optimization.
      for (int k = N; k >= current_col; --k) {
        matrix[row][k] *= first_number_current_row;
        matrix[row][k] -= first_number_row * matrix[current_row][k];
      }
    }
    ++current_row;
  }

  // Back substitution.
  for (int row = num_rows - 1; row >= 0; --row) {
    for (int col = 0; col < N; ++col) {
      if (matrix[row][col] != 0) {
        // Found leftmost.
        for (int k = col + 1; k < N; ++k) {
          matrix[row][N] -= solution[k] * matrix[row][k];
        }
        assert(matrix[row][col] != 0);  // Otherwise modular inverse doesn't exist.
        solution[col] = matrix[row][N] / matrix[row][col];
        break;
      }
    }
  }
}

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
      // Note: recently changed this loop. I think it's correct
      // but double check it should you expect a bug.
      const double first_number_current_row = matrix[j][j];
      const double first_number_row = matrix[i][j];
      for (int k = j; k <= N; ++k) {
        matrix[i][k] -= matrix[j][k] * first_number_row / first_number_current_row;
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

template <typename T>
struct Point {
  vector<T> p;
  int S;

  Point(int num_elements) : S(num_elements), p(num_elements, 0) {}  

  T& operator [](int idx) {
    return p[idx];
  }

  T operator [](int idx) const {
    return p[idx];
  }
};

template <typename T>
struct Matrix {
  vector<vector<T>> M;
  int R;
  int C;

  Matrix(int num_rows, int num_cols) : R(num_rows), C(num_cols) {
    M.assign(num_rows, vector<T>(num_cols, 0));
  }

  vector<T>& operator [](int row) {
    return M[row];
  }

  vector<T> operator [](int row) const {
    return M[row];
  }

  // returns this_matrix * B.
  Matrix<T> operator*(const Matrix<T>& B) const {
    assert(C == B.R);
    
    Matrix<T> result(R, B.C);
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < B.C; ++c) {
        T sum = 0;
        for (int i = 0; i < C; ++i) {
          sum += M[r][i] * B[i][c];
        }
        result[r][c] = sum;
      }
    }
    return result;
  }

  // returns this_matrix * p.
  Point<T> operator*(const Point<T>& p) const {
    assert(C == p.S);
    
    Point<T> result(R);
    for (int r = 0; r < R; ++r) {
      T sum = 0;
      for (int i = 0; i < C; ++i) {
        sum += M[r][i] * p[i];
      }
      result[r] = sum;
    }
    return result;
  }
};

template <typename T>
void print(const Point<T>& p, const string& name) {
  cout << name << ":" << endl;
  for (int r = 0; r < p.S; ++r) {
    cout << p[r] << " ";
  }
  cout << endl;
}

template <typename T>
void print(const Matrix<T>& m, const string& name) {
  cout << name << ":" << endl;
  for (int r = 0; r < m.R; ++r) {
    for (int c = 0; c < m.C; ++c) {
      cout << m[r][c] << " ";
    }
    cout << endl;
  }
}

template <typename T>
Matrix<T> identity(int R, int C) {
  assert(R == C);
  Matrix<T> m(R, C);
  for (int i = 0; i < R; ++i) {
    m[i][i] = 1;
  }
  return m;
}
