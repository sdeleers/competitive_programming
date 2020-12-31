struct DisjointSet {
  // Root elements have a negative number which is the negative of the
  // size of their connected component.
  vector<int> parent;
  DisjointSet (int n) : parent(n, -1) {}

  int findComponent(int x) { 
    return parent[x] < 0 ? x : parent[x] = findComponent(parent[x]);
  }

  bool sameSet(int a, int b) {
    return findComponent(a) == findComponent(b);
  }
  
  vector<vector<int>> getConnectedComponents() {
    unordered_map<int, vector<int>> components_map;
    for (int i = 0; i < parent.size(); ++i) {
      int component = findComponent(i);
      if (components_map.find(component) == components_map.end()) {
        components_map[component] = { i };
      } else {
        components_map[component].push_back(i);
      }
    }
    vector<vector<int>> components;
    for (auto p : components_map) {
      components.push_back(p.second);
    }
    return components;
  }
  
  void join(int a, int b) {
    a = findComponent(a), b = findComponent(b);
    if (a == b) return;
    if (parent[a] > parent[b]) swap(a, b);
    parent[a] += parent[b]; parent[b] = a;
  }
};
