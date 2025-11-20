// find SCCs in given directed graph
// O(V+E)
// the order of scc_idx constitutes a reverse topological sort
auto get_scc = [](const auto& adj) { // 1-indexed
  const int n = adj.size() - 1; int dfs_cnt = 0, scc_cnt = 0;
  vector scc(n + 1, 0), dfn(n + 1, 0), s(0, 0);
  auto dfs = [&](const auto& self, int cur) -> int {
    int ret = dfn[cur] = ++dfs_cnt; s.push_back(cur);
    for (int nxt : adj[cur]) {
      if (!dfn[nxt]) ret = min(ret, self(self, nxt));
      else if (!scc[nxt]) ret = min(ret, dfn[nxt]);
    }
    if (ret == dfn[cur]) {
      scc_cnt++;
      while (s.size()) {
        int x = s.back(); s.pop_back(); scc[x] = scc_cnt;
        if (x == cur) break;
      }
    }
    return ret;
  };
  for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(dfs, i);
  return pair(scc_cnt, scc);
};
