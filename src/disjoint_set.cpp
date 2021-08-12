class DisjointSet {
 private:
  vector<int> parent;
  vector<int> size;
 public:
  DisjointSet(int n) : parent(n, -1), size(n, 1) {}
  
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
    int root_a = find(a);
    int root_b = find(b);
    if (root_a == root_b) return false;
    
    if (size[root_a] < size[root_b]) {
      swap(root_a, root_b);
    }
   
    parent[root_b] = root_a;
    size[root_a] += size[root_b];

    return true;
  }

  bool sameSet(int i, int j) {
    return find(i) == find(j);
  }
};
