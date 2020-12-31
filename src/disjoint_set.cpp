struct DisjointSet {
  vector<int> parent;

  DisjointSet(int N) : parent(N, -1) {}

  void join(int a, int b) {
    const int root1 = find(a);
    const int root2 = find(b);
    if (root1 != root2) {
      // Attach smaller tree to larger tree.
      if (size(a) < size(b)) {
        // Order matters.
        parent[root2] += parent[root1];  // Increase size of root2
        parent[root1] = root2;  // Attach root1 to root2
      } else {
        parent[root1] += parent[root2];  // Increase size of root1
        parent[root2] = root1;  // Attach root2 to root1
      }
    }
  }

  // Returns which node is at the root of the component
  // that contains x.
  int find(int x) {
    if (parent[x] < 0) {
      return x;
    } else {
      return find(parent[x]);
    }
  }

  // Size of component containing x.
  int size(int x) {
    return -parent[find(x)];
  }

  bool sameSet(int a, int b) {
    return find(a) == find(b);
  }
  
  vector<vector<int>> getConnectedComponents() {
    unordered_map<int, vector<int>> components_map;
    for (int i = 0; i < parent.size(); ++i) {
      int component = find(i);
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
};
