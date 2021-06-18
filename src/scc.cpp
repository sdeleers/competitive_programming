class SCC {
 public:
  int N;
  vector<vector<int>> graph;
  vector<vector<int>> reverse_graph;

  SCC(const vector<vector<int>>& g) : graph(g), N(g.size()), reverse_graph(g.size()) {
    for (int i = 0; i < g.size(); ++i) {
      for (int j : g[i]) {
        reverse_graph[j].push_back(i);
      }
    }
  }

  void dfsForwardStep(int u, vector<bool>& visited, vector<int>& order) {
    visited[u] = true;
    for (int v : graph[u]) {
      if (!visited[v]) {
        dfsForwardStep(v, visited, order);
      }
    }
    order.push_back(u);
  }

  void dfsBackwardStep(int u, vector<bool>& visited, vector<int>& scc_index) {
    visited[u] = true;
    for (int v : reverse_graph[u]) {
      if (!visited[v]) {
        scc_index[v] = scc_index[u];
        dfsBackwardStep(v, visited, scc_index);
      }
    }
  }

  // Kosaraju's SCC algorithm.
  vector<int> findSCC() {
    // Forward step: find SCC order.
    vector<int> order;
    vector<bool> visited(N, false);
    for (int i = 0; i < N; ++i) {
      if (!visited[i]) {
        dfsForwardStep(i, visited, order);
      }
    }
    reverse(order.begin(), order.end());

    // Backward step: find SCCs.
    int current_scc = 0;
    vector<int> scc_index(N);
    visited.assign(N, false);
    for (int u : order) {
      if (!visited[u]) {
        scc_index[u] = current_scc;
        dfsBackwardStep(u, visited, scc_index);
        ++current_scc;
      }
    }
    return scc_index;
  }
};
