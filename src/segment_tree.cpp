// Implemented as Range Minimum Query, can be adapted to other queries.
class SegmentTree {
 private:
  vector<long long> tree_; // In "heap format".
  vector<long long> elements_;
  int N_; // Size of elements_.
  long long INFTY = numeric_limits<long long>::max();

  int left(int index) { return 2 * index + 1; }
  int right(int index) { return 2 * index + 2; }

  void build(int index, int l, int r) {
    if (l == r) {
      tree_[index] = l;
    } else {
      build(left(index), l, (l + r) / 2);
      build(right(index), (l + r) / 2 + 1, r);
      int i1 = tree_[left(index)];
      int i2 = tree_[right(index)];
      tree_[index] = (elements_[i1] <= elements_[i2]) ? i1 : i2;
    }
  }

  int rmq(int index, int l, int r, int l_query, int r_query) {
    // If [l, r] and [l_query, r_query] are disjoint.
    if (l_query > r || r_query < l) return -INFTY;

    // If [l, r] is a subsegment of [l_query, r_query].
    if (l_query <= l && r <= r_query) return tree_[index];

    int i1 = rmq(left(index), l, (l + r) / 2, l_query, r_query);
    int i2 = rmq(right(index), (l + r) / 2 + 1, r, l_query, r_query);

    if (i1 == -INFTY || i2 == -INFTY) {
      // Return the one that is valid.
      return max(i1, i2);
    } else {
      // i1 and i2 are both valid indices.
      return elements_[i1] <= elements_[i2] ? i1 : i2;
    }
  }

  void update(int node_index, int l, int r, int element_index, long long value) {
    if (l == r) {
      // Leaf index.
      tree_[node_index] = element_index;
    } else {
      int mid = (l + r) / 2;
      if (element_index <= mid) {
        // Recurse on left child.
        update(left(node_index), l, mid, element_index, value);
      } else {
        // Recurse on right child.
        update(right(node_index), mid + 1, r, element_index, value);
      }
      int i1 = tree_[left(node_index)];
      int i2 = tree_[right(node_index)];
      tree_[node_index] = (elements_[i1] <= elements_[i2]) ? i1 : i2;
    }
  }

 public:
  int rmq(int l_query, int r_query) {
    return rmq(0, 0, N_ - 1, l_query, r_query);
  }

  void update(int element_index, long long value) {
    elements_[element_index] = value;
    update(0, 0, N_ - 1, element_index, value);
  }

  SegmentTree(vector<long long> elements) {
    elements_ = elements;
    N_ = elements_.size();
    tree_.assign(4 * N_, 0);
    build(0, 0, N_ - 1);
  }
};

// Implemented as range sum query. Every node stores the sum of
// the values in its range.
// This has the same complexity as the FenwickTree but
// might be a bit slower due to larger constant factor.
// Every node stores the sum of the values in its range.
class SegmentTree {
 private:
  vector<long long> tree_; // In "heap format".
  vector<long long> elements_;
  int N_; // Size of elements_.
  long long INFTY = numeric_limits<long long>::max();

  int left(int index) { return 2 * index + 1; }
  int right(int index) { return 2 * index + 2; }

  void build(int index, int l, int r) {
    if (l == r) {
      tree_[index] = elements_[l];
    } else {
      build(left(index), l, (l + r) / 2);
      build(right(index), (l + r) / 2 + 1, r);
      tree_[index] = tree_[left(index)] + tree_[right(index)];
    }
  }

  long long rangeSum(int index, int l, int r, int l_query, int r_query) {
    // If [l, r] and [l_query, r_query] are disjoint.
    if (l_query > r || r_query < l) return -INFTY;

    // If [l, r] is a subsegment of [l_query, r_query].
    if (l_query <= l && r <= r_query) return tree_[index];

    long long v1 = rangeSum(left(index), l, (l + r) / 2, l_query, r_query);
    long long v2 = rangeSum(right(index), (l + r) / 2 + 1, r, l_query, r_query);

    if (v1 == -INFTY || v2 == -INFTY) {
      // Return the one that is valid.
      return max(v1, v2);
    } else {
      // v1 and v2 are both valid.
      return v1 + v2;
    }
  }

  void add(int node_index, int l, int r, int element_index, long long increment) {
    if (l == r) {
      // Leaf node.
      tree_[node_index] += increment;
    } else {
      int mid = (l + r) / 2;
      if (element_index <= mid) {
        // Recurse on left child.
        add(left(node_index), l, mid, element_index, increment);
      } else {
        // Recurse on right child.
        add(right(node_index), mid + 1, r, element_index, increment);
      }
      tree_[node_index] = tree_[left(node_index)] + tree_[right(node_index)];
    }
  }

 public:
  long long rangeSum(int l_query, int r_query) {
    return rangeSum(0, 0, N_ - 1, l_query, r_query);
  }

  void add(int element_index, long long increment) {
    elements_[element_index] += increment;
    add(0, 0, N_ - 1, element_index, increment);
  }

  SegmentTree(const vector<long long>& elements) {
    elements_ = elements;
    N_ = elements_.size();
    tree_.assign(4 * N_, 0);
    build(0, 0, N_ - 1);
  }
};
