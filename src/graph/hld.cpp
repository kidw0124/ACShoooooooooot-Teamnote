// heavy-light decomposition in O(n)
auto get_hld = [](auto adj) {
  const int n = adj.size() - 1;
  int ord = 0;
  vector sz(n + 1, 1), dep(n + 1, 0), par(n + 1, 0);
  vector in(n + 1, 0), out(n + 1, 0), top(n + 1, 0);
  auto dfs1 = [&](const auto& self, int cur, int prv) -> void {
    if (prv) adj[cur].erase(ranges::find(adj[cur], prv));
    for (int& nxt : adj[cur]) {
      dep[nxt] = dep[cur] + 1;
      par[nxt] = cur;
      self(self, nxt, cur);
      sz[cur] += sz[nxt];
      if (sz[adj[cur][0]] < sz[nxt]) swap(adj[cur][0], nxt);
    }
  };
  auto dfs2 = [&](const auto& self, int cur) -> void {
    in[cur] = ++ord;
    for (int nxt : adj[cur]) {
      top[nxt] = adj[cur][0] == nxt ? top[cur] : nxt;
      self(self, nxt);
    }
    out[cur] = ord;
  };
  dfs1(dfs1, 1, 0);
  dfs2(dfs2, top[1] = 1);
  return tuple(sz, dep, par, in, out, top);
};
