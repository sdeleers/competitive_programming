struct UnionFind {
  // Root elements have a negative number which is the negative of the
  // size of their connected component.
  vector<int> parent;
  UnionFind (int n) : parent(n, -1) {}

  int findComponent(int x) { 
    return parent[x] < 0 ? x : parent[x] = findComponent(parent[x]);
  }

  void join(int a, int b) {
    a = findComponent(a), b = findComponent(b);
    if (a == b) return;
    if (parent[a] > parent[b]) swap(a, b);
    parent[a] += parent[b]; parent[b] = a;
  }
};
