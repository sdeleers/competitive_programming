template <typename T>
class GridSum {
private:
  int R_;
  int C_;
  vector<vector<T>> grid_;
  // Indexed w.r.t. bottom right corner of rectangle.
  vector<vector<T>> prefix_sums_;

  bool withinBounds(const pair<int, int>& p) const {
    int row = p.first;
    int col = p.second;
    return (row >= 0 && row < R_ && col >= 0 && col < C_);
  }

  void computePrefixSums() {
    prefix_sums_ = vector<vector<T>>(R_, vector<T>(C_));
    for (int r = 0; r < R_; ++r) {
      for (int c = 0; c < C_; ++c) {
        pair<int, int> left = { r, c - 1 };
        pair<int, int> up = { r - 1, c };
        pair<int, int> up_left = { r - 1, c - 1 };
        T sum = grid_[r][c];
        if (withinBounds(left)) sum += prefix_sums_[left.first][left.second];
        if (withinBounds(up)) sum += prefix_sums_[up.first][up.second];
        if (withinBounds(up_left)) sum -= prefix_sums_[up_left.first][up_left.second];
        prefix_sums_[r][c] = sum;
      }
    }
  }

public:
  GridSum(const vector<vector<T>>& grid) : grid_(grid) {
    R_ = grid.size();
    C_ = grid[0].size();
    computePrefixSums();
  }

  T sum(int row1, int row2, int col1, int col2) const {
    T S = prefix_sums_[row2][col2];
    pair<int, int> left = { row2, col1 - 1 };
    pair<int, int> up = { row1 - 1, col2 };
    pair<int, int> up_left = { row1 - 1, col1 - 1 };
    if (withinBounds(left)) S -= prefix_sums_[left.first][left.second];
    if (withinBounds(up)) S -= prefix_sums_[up.first][up.second];
    if (withinBounds(up_left)) S += prefix_sums_[up_left.first][up_left.second];
    return S;
  }
};
