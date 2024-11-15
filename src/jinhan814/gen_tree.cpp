auto gen_tree = [](int n) {
	auto prufer_decode = [](const vector<int>& v) {
		const int n = v.size() + 2;
		vector deg(n + 1, 1);
		for (int i : v) deg[i]++;
		int p = 1, leaf = 1;
		while (deg[p] != 1) p++, leaf++;
		vector res(0, pair(0, 0));
		for (int i : v) {
			res.push_back({ leaf, i });
			if (--deg[i] == 1 && i < p) leaf = i;
			else { do p++; while (deg[p] != 1); leaf = p; }
		}
		res.push_back({ leaf, n });
		return res;
	};
	vector v(n - 2, 0);
	for (int& i : v) i = gen_rand(1, n);
	return prufer_decode(v);
};