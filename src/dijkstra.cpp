struct Dijkstra {

  struct Edge {
    int to;
    int64_t w;
  };

  struct Vertex {
    int v; // Vertex index.
    int64_t d; // Current shortest path estimate from source to vertex.
    bool done; // Whether we've already computed this vertex's shortest path.

    bool operator <(const Vertex& v) const {
      return d > v.d;
    }
  };

  vector<vector<Edge>> graph;

  Dijkstra(int num_vertices) : graph(num_vertices) {}

  void addEdge(int from, int to, int64_t w) {
    graph[from].push_back({ to, w });
  }

  vector<int64_t> solve(int start) {
    // Init.
    vector<Vertex> vertices(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
      vertices[i] = { i, numeric_limits<int64_t>::max(), false };
    }
    vertices[start].d = 0;

    priority_queue<Vertex> pq;
    pq.push({ start, 0, false });
    while (!pq.empty()) {
      Vertex front = pq.top(); pq.pop();
      int u = front.v;
      if (vertices[u].done) continue;
      for (int i = 0; i < graph[u].size(); ++i) {
        Edge e = graph[u][i];
        int from = u;
        int to = e.to;
        int64_t w = e.w;
        if (vertices[from].d + w < vertices[to].d) {
          vertices[to].d = vertices[from].d + w;
          pq.push({ to, vertices[to].d, false });
        }
      }
      vertices[u].done = true;
    }
    vector<int64_t> dist;
    dist.reserve(vertices.size());
    for (const auto& vertex : vertices) {
      dist.push_back(vertex.d);
    }
    return dist;
  }

};
