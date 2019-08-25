struct UnionFind {
  // Root elements have a negative number which is the negative of the
  // size of their connected component.
  vector<int> parent;
  UnionFind (int n) : parent(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -parent[find(x)]; }
  int find(int x) { return parent[x] < 0 ? x : parent[x] = find(parent[x]); }
  int numberOfConnectedComponents() {
    int num_cc = 0;
    for (int i = 0; i < parent.size(); ++i) if (parent[i] < 0) ++num_cc;
    return num_cc;
  }
  void join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (parent[a] > parent[b]) swap(a, b);
    parent[a] += parent[b]; parent[b] = a;
  }
};
