#define debug(...) __dbg(#__VA_ARGS__, __VA_ARGS__)
template<typename T>
ostream& operator<<(ostream& out, vector<T> v) {
	string _;
	out << '(';
	for (T x : v) cout << _ << x, _ = " ";
	out << ')';
	return out;
}
void __dbg(string s, auto... x) {
	string _;
	cout << '(' << s << ") : ";
	(..., (cout << _ << x, _ = ", "));
	cout << '\n';
}