// O(n lg n) for centroid decomposition
auto cent_decom = [](const auto& adj) {
  const int n = adj.size() - 1;
  vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0);
  auto dfs = [&](const auto& self, int cur, int prv) -> void {
    for (auto [nxt, cost] : adj[cur]) {
      if (nxt == prv) continue;
      self(self, nxt, cur);
      sz[cur] += sz[nxt];
    }
  };
  auto adjust = [&](int cur) {
    while (1) {
      int f = 0;
      for (auto [nxt, cost] : adj[cur]) {
        if (dep[nxt] || sz[cur] >= 2 * sz[nxt]) continue;
        sz[cur] -= sz[nxt], sz[nxt] += sz[cur];
        cur = nxt, f = 1;
        break;
      }
      if (!f) return cur;
    }
  };
  auto rec = [&](const auto& self, int cur, int prv) -> void {
    cur = adjust(cur);
    par[cur] = prv;
    dep[cur] = dep[prv] + 1;
    for (auto [nxt, cost] : adj[cur]) {
      if (dep[nxt]) continue;
      self(self, nxt, cur);
    }
  };
  dfs(dfs, 1, 0);
  rec(rec, 1, 0);
  return pair(dep, par);
};