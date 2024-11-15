auto dlas = [](const auto& state, int iter) {
	vector s(3, state);
	vector buc(5, s[0].score());
	auto cur_score = buc[0], min_score = cur_score;
	int cur_pos = 0, min_pos = 0, k = 0;
	for (int i = 0; i < iter; i++) {
		auto prv_score = cur_score;
		int nxt_pos = cur_pos + 1 < 3 ? cur_pos + 1 : 0;
		if (nxt_pos == min_pos) nxt_pos = nxt_pos + 1 < 3 ? nxt_pos + 1 : 0;
		auto& cur_state = s[cur_pos];
		auto& nxt_state = s[nxt_pos];
		nxt_state = cur_state;
		nxt_state.mutate();
		auto nxt_score = nxt_state.score();
		if (min_score > nxt_score) {
			i = 0;
			min_pos = nxt_pos;
			min_score = nxt_score;
		}
		if (nxt_score == cur_score || nxt_score < ranges::max(buc)) {
			cur_pos = nxt_pos;
			cur_score = nxt_score;
		}
		auto& fit = buc[k];
		if (cur_score > fit || cur_score < min(fit, prv_score)) {
			fit = cur_score;
		}
		k = k + 1 < 5 ? k + 1 : 0;
	}
	return pair(s[min_pos], min_score);
};