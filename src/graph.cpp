void dfsFindCycles(int u, const vector<vector<int>>& g,
                   vector<string>& color,
                   vector<int>& parent,
                   vector<vector<int>>& cycles) {
  if (color[u] == "BLACK") {
    return;
  } else if (color[u] == "WHITE") {
    color[u] = "GREY";
    for (int neighbor : g[u]) {
      if (parent[u] == neighbor) continue;
      parent[neighbor] = u;
      dfsFindCycles(neighbor, g, color, parent, cycles);
    }
    color[u] = "BLACK";
  } else if (color[u] == "GREY") {
    // Cycle detected.
    cycles.push_back({});
    int v = parent[u];
    while (v != u) {
      cycles.back().push_back(v);
      v = parent[v];
    }
    cycles.back().push_back(v);
  } else {
    assert(false);
  }
}
