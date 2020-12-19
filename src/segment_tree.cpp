// XOR
template <class T>
struct SegTree {
  const T BAD_VALUE = -1;
  int leftmost;
  int rightmost;
  SegTree* left_child = nullptr;
  SegTree* right_child = nullptr;
  T sum;

  SegTree(int leftmost, int rightmost, const vector<T>& elements) {
    this->leftmost = leftmost;
    this->rightmost = rightmost;
    if (leftmost == rightmost) {
      sum = elements[leftmost];
    } else {
      const int mid = (leftmost + rightmost) / 2;
      left_child = new SegTree(leftmost, mid, elements);
      right_child = new SegTree(mid + 1, rightmost, elements);
      sum = left_child->sum ^ right_child->sum;
    }
  }

  T rangeXOR(int left, int right) {
    if (left > rightmost || right < leftmost) {
      // Disjoint.
      return BAD_VALUE;
    } else if (leftmost >= left && rightmost <= right) {
      // Completely contained within.
      return sum;
    } else {
      int left_child_value = (left_child != nullptr) ? left_child->rangeXOR(left, right) : BAD_VALUE;
      int right_child_value = (right_child != nullptr) ? right_child->rangeXOR(left, right) : BAD_VALUE;
      if (left_child_value != BAD_VALUE && right_child_value != BAD_VALUE) {
        return left_child_value ^ right_child_value;
      } else if (left_child_value != BAD_VALUE) {
        return left_child_value;
      } else {
        return right_child_value;
      }
    }
  }

  void pointUpdate(int index, T value) {
    if (leftmost == rightmost) {
      assert(leftmost == index);
      sum ^= value;
    } else {
      assert(left_child != nullptr);
      assert(right_child != nullptr);
      if (index <= left_child->rightmost) {
        left_child->pointUpdate(index, value);
      } else {
        right_child->pointUpdate(index, value);
      }
      sum = left_child->sum ^ right_child->sum;
    }
  }
};

// Implemented as Range Minimum Query, can be adapted to other queries.
class SegmentTree {
 private:
  vector<long long> elements_;
  vector<long long> tree_; // In "heap format".
  int N_; // Size of elements_.

  long long INFTY = 1000000000000000;  // 1e15.

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
  int rmq_index(int l_query, int r_query) {
    if (l_query > r_query) {
      return -1;
    }
    return rmq(0, 0, N_ - 1, l_query, r_query);
  }

  long long rmq(int l_query, int r_query) {
    int rmq_idx = rmq_index(l_query, r_query);
    if (rmq_idx == -1) {
      return INFTY;
    } else {
      return elements_[rmq_idx];
    }
  }

  void update(int element_index, long long value) {
    elements_[element_index] = value;
    update(0, 0, N_ - 1, element_index, value);
  }

  SegmentTree(int number_of_elements) {
    N_ = number_of_elements;
    elements_.resize(N_, INFTY);
    tree_.assign(4 * N_, 0);
    build(0, 0, N_ - 1);
  }
};

template <class T>
struct SegTree {
  int leftmost;
  int rightmost;
  SegTree* left_child;
  SegTree* right_child;
  T sum;

  SegTree(int leftmost, int rightmost, const vector<T>& elements) {
    this->leftmost = leftmost;
    this->rightmost = rightmost;
    if (leftmost == rightmost) {
      sum = elements[leftmost];
    } else {
      const int mid = (leftmost + rightmost) / 2;
      left_child = new SegTree(leftmost, mid, elements);
      right_child = new SegTree(mid + 1, rightmost, elements);
      sum = left_child->sum + right_child->sum;
    }
  }

  T query(int left, int right) {
    if (left > rightmost || right < leftmost) {
      // Disjoint.
      return 0;
    } else if (leftmost >= left && rightmost <= right) {
      // Completely contained within.
      return sum;
    } else {
      // Partially overlapping.
      return left_child->query(left, right) + right_child->query(left, right);
    }
  }

  void set(int index, T value) {
    if (leftmost == rightmost) {
      if (leftmost == index) {
        sum = value;
      }
    } else {
      if (index <= left_child->rightmost) {
        left_child->set(index, value);
      } else {
        right_child->set(index, value);
      }
      sum = left_child->sum + right_child->sum;
    }
  }
};
