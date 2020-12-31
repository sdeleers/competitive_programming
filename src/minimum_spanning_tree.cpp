struct Edge {
  int from;
  int to;
  long long dist;
};

// Prim's algorithm
template <typename T>
class MinimumSpanningTree {
 private:
  T weight_;
  int N_;
  vector<vector<Edge>> g_; // Adjacency list.

 public:
  MinimumSpanningTree(const vector<vector<Edge>> g) :
    weight_(-1), g_(g), N_(g.size()) {}

  T getWeight() {
    return weight_;
  }

  // Uses lazy deletion instead of decrease-key operations.
  void solve() {
    weight_ = 0;
    // The priority queue contains vertices in V - S, and for each of
    // these vertices it has weight equal to the minimum distance of
    // that vertex to (a node in) S.
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
    q.push({ 0, 0 });  // { weight, index }
    // Distance contains the distance of every vertex to S (distance is 0 if in S).
    vector<T> dist(N_, numeric_limits<T>::max());
    while (!q.empty()) {
      const auto p = q.top();
      q.pop();
      if (p.first < dist[p.second]) {
        dist[p.second] = 0;
        weight_ += p.first;
        for (int i = 0; i < g_[p.second].size(); ++i) {
          const T d = g_[p.second][i].dist;
          const int to = g_[p.second][i].to;
          if (d < dist[to]) {
            q.push({ d, to });
          }
        }
      }
    }
  }
};
