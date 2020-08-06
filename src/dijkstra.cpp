struct Edge {
  int to;
  long long w;
};

struct Vertex {
  int v; // Vertex index.
  long long d; // Current shortest path estimate from source to vertex.
  bool done; // Whether we've already computed this vertex's shortest path.

  bool operator <(const Vertex& v) const {
    return d < v.d;
  }

  bool operator >(const Vertex& v) const {
    return d > v.d;
  }
};

vector<Vertex> dijkstra(const vector<vector<Edge>>& graph, int start, int N) {
  // Init.
  vector<Vertex> vertices(N);
  for (int i = 0; i < N; ++i) {
    vertices[i] = { i, LONG_LONG_MAX, false };
  }
  vertices[start].d = 0;

  priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
  pq.push({ start, 0, false });
  while (!pq.empty()) {
    Vertex front = pq.top(); pq.pop();
    int u = front.v;
    if (vertices[u].done) continue;
    for (int i = 0; i < graph[u].size(); ++i) {
      Edge e = graph[u][i];
      int from = u;
      int to = e.to;
      long long w = e.w;
      if (vertices[from].d + w < vertices[to].d) {
        vertices[to].d = vertices[from].d + w;
        pq.push({ to, vertices[to].d, false });
      }
    }
    vertices[u].done = true;
  }
  return vertices;
}
