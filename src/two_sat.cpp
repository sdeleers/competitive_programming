struct TwoSat {
  int N;
  vector<vector<int>> gr;
  vector<int> values; // 0 = false, 1 = true

  TwoSat(int n = 0) : N(n), gr(2*n) {}

  int add_var() { // (optional)
    gr.emplace_back();
    gr.emplace_back();
    return N++;
  }

  void add_clause(int aind, bool aval, int bind, bool bval) {
    int a = 2*aind + aval, b = 2*bind + bval;
    gr[a^1].push_back(b);
    gr[b^1].push_back(a);
  }

  void set_value(int index, bool value) {
    add_clause(index, value, index, value);
  }

  void exactly_one(int index1, int index2) {
    add_clause(index1, false, index2, false);
    add_clause(index1, true, index2, true);
  }

  void at_most_one(const vector<int>& li, bool val = 1) {
    if (li.size() <= 1) return;
    int cur = li[0];
    for (int i = 2; i < li.size(); ++i) {
      int next = add_var();
      add_clause(cur, !val, li[i], !val);
      add_clause(cur, !val, next, val);
      add_clause(li[i], !val, next, val);
      cur = next;
    }
    add_clause(cur, !val, li[1], !val);
  }

  vector<int> val, comp, z; int time = 0;
  int dfs(int i) {
    int low = val[i] = ++time, x; z.push_back(i);
    for (int e : gr[i]) {
      if (!comp[e]) {
        low = min(low, val[e] ? val[e] : dfs(e));
      }
    }
    ++time;
    if (low == val[i]) do {
      x = z.back(); z.pop_back();
      comp[x] = time;
      if (values[x>>1] == -1)
        values[x>>1] = x&1;
    } while (x != i);
    return val[i] = low;
  }

  bool solve() {
    values.assign(N, -1);
    val.assign(2*N, 0); comp = val;
    for (int i = 0; i < 2 * N; ++i) {
      if (!comp[i]) {
        dfs(i);
      }
    }
    for (int i = 0; i < N; ++i) {
      if (comp[2*i] == comp[2*i+1]) {
        return 0;
      }
    }
    return 1;
  }
};
