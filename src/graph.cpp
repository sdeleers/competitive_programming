// If graph is not connected, call this function
// for every vertex, i.e.
// for (int i = 0; i < N; ++i) dfsFindCycles(i, ...);
// Find cycles in undirected graph
// If graph is directed, then remove the line with the NOTE below.
void dfsFindCycles(int u, const vector<vector<int>>& g,
                   vector<string>& color,
                   vector<int>& parent,
                   vector<vector<int>>& cycles) {
  if (color[u] == "BLACK") {
    return;
  } else if (color[u] == "WHITE") {
    color[u] = "GREY";
    for (int neighbor : g[u]) {
      if (parent[u] == neighbor) continue;  // NOTE: If the graph is directed, then remove this line.
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

// ------------------------------
bool hasCycleDFS(int u, const vector<vector<int>>& g,
                 vector<string>& color) {
  if (color[u] == "BLACK") {
    return false;
  } else if (color[u] == "WHITE") {
    color[u] = "GREY";
    for (int neighbor : g[u]) {
      if (hasCycleDFS(neighbor, g, color)) return true;
    }
    color[u] = "BLACK";
    return false;
  } else if (color[u] == "GREY") {
    // Cycle detected.
    return true;
  } else {
    assert(false);
  }
}

vector<string> color(N, "WHITE");
bool has_cycle = false;
for (int i = 0; i < N; ++i) {
  has_cycle |= hasCycleDFS(i, graph, color);
}

// ------------------------------

void findTopologicalOrder(int u, const vector<vector<int>>& g, vector<bool>& visited, vector<int>& order) {
  if (visited[u]) {
    return;
  }

  visited[u] = true;
  for (int v : g[u]) {
    findTopologicalOrder(v, g, visited, order);    
  }
  order.push_back(u);
}

vector<int> order;
vector<bool> visited(N, false);
for (int i = 0; i < N; ++i) {
  if (!visited[i]) {
    findTopologicalOrder(i, graph, visited, order);
  }
}

// ------------------------------


