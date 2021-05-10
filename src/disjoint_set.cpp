class DisjointSet {
 private:
  vector<int> parent;
 public:
  DisjointSet(int n) : parent(n, -1) {}
  
  int find(int x) {
    int root = x;
    while (parent[root] >= 0) {
      root = parent[root];
    }
    // Path compression.
    int current = x;
    while (parent[current] >= 0) {
      int tmp = parent[current];
      parent[current] = root;
      current = tmp;
    }
    return root;
  }
  
  bool join(int a, int b) {
    const int root_a = find(a);
    const int root_b = find(b);
    if (root_a == root_b) return false;
    
    if (parent[root_a] > parent[root_b]) {
      parent[root_a] += parent[root_b];  // Increment size of tree rooted at a.
      parent[root_b] = root_a;  // Attach root_b to root_a.
    } else {
      // Attach root_a to root_b
      parent[root_b] += parent[root_a];  // Increment size of tree rooted at b.
      parent[root_a] = root_b;  // Attach root_a to root_b.
    }
    return true;
  }

  bool sameSet(int i, int j) {
    return find(i) == find(j);
  }
};
