// Implementation using adjacency list.
template <typename T>
class MaxFlow {
 public:
  struct Edge {
    int from, to;
    T cap, flow;
    Edge() {}
    Edge(int u, int v, T cap): from(u), to(v), cap(cap), flow(0) {}
  };

  // Residual graph in adjacency list format. Contains indices into edges vector.
  vector<vector<T>> g_;
  vector<Edge> edges_;
  int source_;
  int sink_;
  int N_;

  MaxFlow(int N, int source, int sink) :
    g_(N), edges_(0), source_(source), sink_(sink), N_(N) {}

  void addEdge(int from, int to, T cap) {
    if (from != to) {
      edges_.push_back(Edge(from, to, cap));
      g_[from].push_back(edges_.size() - 1);
      // The inverse edge has 0 capacity.
      edges_.push_back(Edge(to, from, 0));
      g_[to].push_back(edges_.size() - 1);
    }
  }

  // Path contains indices to edges.
  T findAugmentingPath(vector<int>& path) {
    path.clear();
    T flow = 0;
    // BFS.
    queue<int> q;
    q.push(source_);
    vector<bool> visited(N_, false);
    vector<int> parent(N_); // Edge index that leads to this vertex.
    while(!q.empty()) {
      int u = q.front(); q.pop();
      visited[u] = true;
      for (int edge_idx : g_[u]) {
        Edge e = edges_[edge_idx];
        int v = e.to;
        if (!visited[v] && e.cap > 0) {
          q.push(v);
          parent[v] = edge_idx;
          if (v == sink_) {
            // Path found.
            flow = e.cap;
            while (v != source_) {
              path.push_back(edge_idx);
              flow = min(flow, e.cap);
              v = e.from;
              edge_idx = parent[v];
              e = edges_[edge_idx];
            }
            reverse(path.begin(), path.end());
            return flow;
          }
        }
      }
    }
    return 0;
  }

  T solve() {
    T flow = 0;
    vector<int> path;
    while (T path_flow = findAugmentingPath(path)) {
      flow += path_flow;
      for (int edge_idx : path) {
        edges_[edge_idx].cap -= path_flow;
        edges_[edge_idx].flow += path_flow;
        // Reverse edges. The regular and reverse edges
        // appear in pairs of 2. Therefore if we have one
        // we have to flip the last bit to find the other.
        edges_[edge_idx ^ 1].cap += path_flow;
        edges_[edge_idx ^ 1].flow -= path_flow;
      }
    }
    return flow;
  }
};


