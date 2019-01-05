class Matching {
 public:
  int _m;
  int _n;
  vector<vector<int>> _graph;
  vector<int> _ma;
  vector<int> _mb;
  vector<bool> _visited;
  int _flow;

  Matching(int m, int n) : _m(m), _n(n) {
    _graph.resize(m);
    _ma.assign(n, -1);
    _mb.assign(m, -1);
    _flow = 0;
  }

  void add(int i, int j) {
    _graph[i].push_back(j);
  }

  bool dfs(int left) {
    for (int right : _graph[left]) {
      if (!_visited[right]) {
        _visited[right] = true;
        if (_mb[right] == -1 || dfs(_mb[right])) {
          _ma[left] = right;
          _mb[right] = left;
          return true;
        }
      }
    }
    return false;
  }

  int solve() {
    for (int i = 0; i < _m; ++i) {
      _visited.assign(_m, false);
      if (dfs(i)) {
        ++_flow;
      }
    }
    return _flow;
  }

};
