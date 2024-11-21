template<class S = string , class T = typename S::value_type>
struct eertree {
  struct node { int len, link;map<T, int> child; };
  S s; vector<node> data; int max_suf;
  eertree() : max_suf(1) {
    data.push_back({ -1, 0 }); data.push_back({ 0, 0 });
  }
  void add(T c) {
    s.push_back(c); int i = max_suf;
    while (data[i].len + 2 > s.size() || s[s.size() - data[i].len - 2] != c) i = data[i].link;
    if (data[i].child.count(c) == 0) {
      if (i == 0) data[i].child[c] = data.size(), data.push_back({ data[i].len + 2, 1 });
      else {
        int j = data[i].link; while (s[s.size() - data[j].len - 2] != c) j = data[j].link;
        data[i].child[c] = data.size(); data.push_back({ data[i].len + 2, data[j].child[c] });
      }
    }
    i = data[i].child[c];
    max_suf = i;
  }
};