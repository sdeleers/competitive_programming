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
    if (l_query > r || r_query < l) return -1;

    // If [l, r] is a subsegment of [l_query, r_query].
    if (l_query <= l && r <= r_query) return tree_[index];

    int i1 = rmq(left(index), l, (l + r) / 2, l_query, r_query);
    int i2 = rmq(right(index), (l + r) / 2 + 1, r, l_query, r_query);

    if (i1 == -1 || i2 == -1) {
      // Return the one that is valid.
      return max(i1, i2);
    } else {
      // i1 and i2 are both valid indices.
      return elements_[i1] <= elements_[i2] ? i1 : i2;
    }
  }

 public:
  int rmq(int l_query, int r_query) {
    return rmq(0, 0, N_ - 1, l_query, r_query);
  }

  void update(int index, T value) {
    // Update elements_.
    elements_[index] = value;
    int node = leaf(index); // Start at leaf node and go up to root.
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
