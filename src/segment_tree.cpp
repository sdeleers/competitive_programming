const int INFTY = 1000000000;

// Implemented as Range Minimum Query, can be adapted to other queries
template <class T>
class SegmentTree {
 private:
  vector<int> tree_; // In "heap format".
  vector<T> elements_;
  int N_; // Size of elements_.

  int left(int index) { return 2 * index + 1; }
  int right(int index) { return 2 * index + 2; }
  int parent(int index) { return index != 0 ? (index - 1) / 2 : -1; }
  int leaf(int element_index) {
    // Find leaf node which stores segment [element_index, element_index].
    int l = 0;
    int r = N_ - 1;
    int leaf = 0; // Start at root.
    while (l != r) {
      int middle = (l + r) / 2;
      if (element_index > middle) { // Take right branch.
        l = middle + 1;
        leaf = right(leaf);
      } else { // Take left branch.
        r = middle;
        leaf = left(leaf);
      }
    }
    return leaf;
  }

  void build(int index, int l, int r) {
    if (l == r) {
      tree_[index] = l;
    } else {
      build(left(index), l, (l + r) / 2);
      build(right(index), (l + r) / 2 + 1, r);
      int i1 = tree_[left(index)];
      int i2 = tree_[right(index)];
      tree_[index] = elements_[i1] <= elements_[i2] ? i1 : i2;
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
      return (i1 == -INFTY) ? i2 : i1;
    } else {
      // i1 and i2 are both valid indices.
      return elements_[i1] <= elements_[i2] ? i1 : i2;
    }
  }

 public:
  int rmq(int l_query, int r_query) {
    return rmq(0, 0, N_ - 1, l_query, r_query);
  }

  void update(int element_index, T value) {
    // Update elements_.
    elements_[element_index] = value;
    int node = leaf(element_index); // Start at leaf node and go up to root.
    tree_[node] = elements_[element_index];
    while (parent(node) != -1) {
      node = parent(node);
      int i1 = tree_[left(node)];
      int i2 = tree_[right(node)];
      tree_[node] = elements_[i1] <= elements_[i2] ? i1 : i2; 
    }
  }

  SegmentTree(vector<T> elements) {
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
template <class T>
class SegmentTree {
 private:
  vector<int> tree_; // In "heap format".
  vector<T> elements_;
  int N_; // Size of elements_.

  int left(int index) { return 2 * index + 1; }
  int right(int index) { return 2 * index + 2; }
  int parent(int index) { return index != 0 ? (index - 1) / 2 : -1; }
  int leaf(int element_index) {
    // Find leaf node which stores segment [element_index, element_index].
    int l = 0;
    int r = N_ - 1;
    int leaf = 0; // Start at root.
    while (l != r) {
      int middle = (l + r) / 2;
      if (element_index > middle) {
        // Take right branch.
        l = middle + 1;
        leaf = right(leaf);
      } else {
        r = middle;
        leaf = left(leaf);
      }
    }
    return leaf;
  }

  void build(int index, int l, int r) {
    if (l == r) {
      tree_[index] = elements_[l];
    } else {
      build(left(index), l, (l + r) / 2);
      build(right(index), (l + r) / 2 + 1, r);
      tree_[index] = tree_[left(index)] + tree_[right(index)];
    }
  }

  int rangeSum(int index, int l, int r, int l_query, int r_query) {
    // If [l, r] and [l_query, r_query] are disjoint.
    if (l_query > r || r_query < l) return -INFTY;

    // If [l, r] is a subsegment of [l_query, r_query].
    if (l_query <= l && r <= r_query) return tree_[index];

    int v1 = rangeSum(left(index), l, (l + r) / 2, l_query, r_query);
    int v2 = rangeSum(right(index), (l + r) / 2 + 1, r, l_query, r_query);

    if (v1 == -INFTY || v2 == -INFTY) {
      // Return the one that is valid.
      return (v1 == -INFTY) ? v2 : v1;
    } else {
      // v1 and v2 are both valid.
      return v1 + v2;
    }
  }

 public:
  int rangeSum(int l_query, int r_query) {
    return rangeSum(0, 0, N_ - 1, l_query, r_query);
  }

  void add(int element_index, T increment) {
    // Update elements_.
    elements_[element_index] += increment;
    int node = leaf(element_index); // Start at leaf node and go up to root.
    tree_[node] = elements_[element_index];
    while (parent(node) != -1) {
      node = parent(node);
      tree_[node] = tree_[left(node)] + tree_[right(node)];
    }
  }

  SegmentTree(vector<T> elements) {
    elements_ = elements;
    N_ = elements_.size();
    tree_.assign(4 * N_, 0);
    build(0, 0, N_ - 1);
  }
};
