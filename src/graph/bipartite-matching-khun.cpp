auto bipartite_matching = [](const auto& adj) { // O(VE)
  const int n = adj.size() - 1;
  vector par(n + 1, 0), c(n + 1, 0);
  auto dfs = [&](const auto& self, int cur) -> bool {
    if (c[cur]++) return 0;
    for (int nxt : adj[cur])
      if (!par[nxt] || self(self, par[nxt]))
        return par[nxt] = cur, 1;
    return 0;
  };
  int res = 0;
  for (int i = 1; i <= n; i++) {
    fill(c.begin(), c.end(), 0);
    if (dfs(dfs, i)) res++;
  }
  return res;
};