// Array whose prefix sums from 0 to i are equal
// to the value at location i.
// Update range: O(1)
// Query value: O(N)
// getSums returns all values in O(N)
class CyclicRangeArray {
 private:
  vector<int> values_;
  int N_;

 public:
  CyclicRangeArray(const vector<int>& values) :
    values_(values), N_(values.size()) {}

  // Cyclic array, therefore left can be greater than right.
  // Note: increments by 1.
  void updateRange(int left, int right) {
    ++values_[left];

    if (right >= left) {
      if (right + 1 != N_) {
        --values_[right + 1];
      }
    } else if (right < left) {
      if (right + 1 != N_) {
        --values_[right + 1];
        ++values_[0];
      }
    }
  }

  // Convert range array to sums.
  vector<int> getSums() {
    vector<int> sums(N_, 0);
    sums[0] = values_[0];
    for (int i = 1; i < N_; ++i) {
      sums[i] = sums[i - 1] + values_[i];
    }
    return sums;
  }
};
