auto get_scc = [](const auto& adj) { // 1-indexed
	const int n = adj.size() - 1;
	int dfs_cnt = 0, scc_cnt = 0;
	vector scc(n + 1, 0), dfn(n + 1, 0), s(0, 0);
	auto dfs = [&](const auto& self, int cur) -> int {
		int ret = dfn[cur] = ++dfs_cnt;
		s.push_back(cur);
		for (int nxt : adj[cur]) {
			if (!dfn[nxt]) ret = min(ret, self(self, nxt));
			else if (!scc[nxt]) ret = min(ret, dfn[nxt]);
		}
		if (ret == dfn[cur]) {
			scc_cnt++;
			while (s.size()) {
				int x = s.back(); s.pop_back();
				scc[x] = scc_cnt;
				if (x == cur) break;
			}
		}
		return ret;
	};
	for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(dfs, i);
	return pair(scc_cnt, scc);
};
struct two_sat { // 1-indexed
	two_sat(int n) : n(n), adj(n + 1 << 1), scc(n + 1 << 1) {}
	void add_clause(int a, bool na, int b, bool nb) {
		assert(1 <= a && a <= n && 1 <= b && b <= n);
		a = a << 1 | na;
		b = b << 1 | nb;
		adj[a ^ 1].push_back(b);
		adj[b ^ 1].push_back(a);
	}
	bool satisfiable() {
		tie(scc_cnt, scc) = get_scc(adj);
		for (int i = 1; i <= n; i++) if (scc[i << 1] == scc[i << 1 | 1]) return 0;
		return 1;
	}
	bool get(int i) const {
		assert(1 <= i && i <= n);
		return scc[i << 1] < scc[i << 1 | 1];
	}
private:
	int n, scc_cnt;
	vector<vector<int>> adj;
	vector<int> scc;
};