#include "bits/stdc++.h"
using namespace std;
using ui = unsigned; using db = long double; using ll = long long; using ull = unsigned long long;
template<class T1, class T2> istream &operator>>(istream &cin, pair<T1, T2> &a) { return cin >> a.first >> a.second; }
template <std::size_t Index = 0, typename... Ts> typename std::enable_if<Index == sizeof...(Ts), void>::type tuple_read(std::istream &is, std::tuple<Ts...> &t) { }
template <std::size_t Index = 0, typename... Ts> typename std::enable_if < Index < sizeof...(Ts), void>::type tuple_read(std::istream &is, std::tuple<Ts...> &t) { is >> std::get<Index>(t); tuple_read<Index + 1>(is, t); }
template <typename... Ts>std::istream &operator>>(std::istream &is, std::tuple<Ts...> &t) { tuple_read(is, t); return is; }
template<class T1> istream &operator>>(istream &cin, valarray<T1> &a);
template<class T1> istream &operator>>(istream &cin, vector<T1> &a) { for (auto &x : a) cin >> x; return cin; }
template<class T1> istream &operator>>(istream &cin, valarray<T1> &a) { for (auto &x : a) cin >> x; return cin; }
template<class T1, class T2> bool cmin(T1 &x, const T2 &y) { if (y < x) { x = y; return 1; } return 0; }
template<class T1, class T2> bool cmax(T1 &x, const T2 &y) { if (x < y) { x = y; return 1; } return 0; }
template<class T1> vector<T1> range(T1 l, T1 r, T1 step = 1) { assert(step > 0); int n = (r - l + step - 1) / step, i; vector<T1> res(n); for (i = 0; i < n; i++) res[i] = l + step * i; return res; }
template<class T1> basic_string<T1> operator*(const basic_string<T1> &s, int m) { auto r = s; m *= s.size(); r.resize(m); for (int i = s.size(); i < m; i++) r[i] = r[i - s.size()]; return r; }
using lll = __int128;
istream &operator>>(istream &cin, lll &x) { bool flg = 0; x = 0; static string s; cin >> s; if (s[0] == '-') flg = 1, s = s.substr(1); for (char c : s) x = x * 10 + (c - '0'); if (flg) x = -x; return cin; }
ostream &operator<<(ostream &cout, lll x) { static char s[60]; if (x < 0) cout << '-', x = -x; int tp = 1; s[0] = '0' + (x % 10); while (x /= 10) s[tp++] = '0' + (x % 10); while (tp--) cout << s[tp]; return cout; }
#if !defined(ONLINE_JUDGE)&&defined(LOCAL)
#include "my_header/debug.h"
#else
#define dbg(...) ;
#endif
template<class T1, class T2> ostream &operator<<(ostream &cout, const pair<T1, T2> &a) { return cout << a.first << ' ' << a.second; }
template<class T1, class T2> ostream &operator<<(ostream &cout, const vector<pair<T1, T2>> &a) { for (auto &x : a) cout << x << '\n'; return cout; }
template<class T1> ostream &operator<<(ostream &cout, vector<T1> a) { int n = a.size(); if (!n) return cout; cout << a[0]; for (int i = 1; i < n; i++) cout << ' ' << a[i]; return cout; }
template<class T1> ostream &operator<<(ostream &cout, const valarray<T1> &a) { int n = a.size(); if (!n) return cout; cout << a[0]; for (int i = 1; i < n; i++) cout << ' ' << a[i]; return cout; }
template<class T1> ostream &operator<<(ostream &cout, const vector<valarray<T1>> &a) { int n = a.size(); if (!n) return cout; cout << a[0]; for (int i = 1; i < n; i++) cout << '\n' << a[i]; return cout; }
template<class T1> ostream &operator<<(ostream &cout, const vector<vector<T1>> &a) { int n = a.size(); if (!n) return cout; cout << a[0]; for (int i = 1; i < n; i++) cout << '\n' << a[i]; return cout; }
#define all(x) (x).begin(),(x).end()
#define print(...) cout<<format(__VA_ARGS__)
#define println(...) cout<<format(__VA_ARGS__)<<'\n'
#define err(...) cerr<<format(__VA_ARGS__)
#define errln(...) cerr<<format(__VA_ARGS__)<<'\n'
const ll inf = 1e18;
ll steiner(int n, const vector<tuple<int, int, ll>> &eg, vector<int> id)//[0,n)
{
	using pa = pair<ll, int>;
	int m = id.size(), i;
	vector f(1 << m, vector<ll>(n, inf));
	for (i = 0; i < m; i++) f[1 << i][id[i]] = 0;
	vector<vector<pair<int, ll>>> e(n);
	for (auto [u, v, w] : eg) e[u].push_back({v, w}), e[v].push_back({u, w});
	for (int S = 1; S < 1 << m; S++)
	{
		auto &d = f[S];
		priority_queue<pa, vector<pa>, greater<pa>> q;
		for (i = 0; i < n; i++)
		{
			for (int T = S - 1 & S; T; T = T - 1 & S) cmin(d[i], f[T][i] + f[S ^ T][i]);
			if (d[i] != inf) q.push({d[i], i});
		}
		while (q.size())
		{
			auto [_, u] = q.top(); q.pop();
			if (_ != d[u]) continue;
			for (auto [v, w] : e[u]) if (cmin(d[v], d[u] + w)) q.push({d[v], v});
		}
	}
	return *min_element(all(f.back()));
}
pair<ll, vector<int>> steiner_construct(int n, const vector<tuple<int, int, ll>> &eg, vector<int> id)//[0,n)
{
	using pa = pair<ll, int>;
	int m = id.size(), i;
	vector f(1 << m, vector<ll>(n, inf));
	vector pre(1 << m, vector(n, pair{-1, -1}));
	for (i = 0; i < m; i++) f[1 << i][id[i]] = 0;
	vector<vector<tuple<int, ll, int>>> e(n);
	i = 0;
	for (auto [u, v, w] : eg) e[u].push_back({v, w, i}), e[v].push_back({u, w, i++});
	for (int S = 1; S < 1 << m; S++)
	{
		auto &d = f[S];
		priority_queue<pa, vector<pa>, greater<pa>> q;
		for (i = 0; i < n; i++)
		{
			for (int T = S - 1 & S; T; T = T - 1 & S)
				if (cmin(d[i], f[T][i] + f[S ^ T][i]))
					pre[S][i] = {-2, T};

			if (d[i] != inf) q.push({d[i], i});
		}
		while (q.size())
		{
			auto [_, u] = q.top(); q.pop();
			if (_ != d[u]) continue;
			for (auto [v, w, id] : e[u]) if (cmin(d[v], d[u] + w))
			{
				q.push({d[v], v});
				pre[S][v] = {u, id};
			}
		}
	}
	vector<int> chosen;
	int S = (1 << m) - 1, u = min_element(all(f[S])) - f[S].begin();
	auto dfs = [&](auto &&dfs, int S, int u) {
		auto [x, y] = pre[S][u];
		while (x >= 0)
		{
			u = x;
			chosen.push_back(y);
			tie(x, y) = pre[S][u];
		}
		if (x == -1) return;
		dfs(dfs, y, u); dfs(dfs, S ^ y, u);
	};
	dfs(dfs, S, u);
	sort(all(chosen));
	return {f[S][u], chosen};
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(15);
	int n, m, q, i;
	cin >> n >> m;
	vector<tuple<int, int, ll>> eg(m);
	cin >> eg >> q;
	vector<int> id(q);
	cin >> id;
	auto [ans, eid] = steiner_construct(n, eg, id);
	cout << ans << ' ' << eid.size() << '\n' << eid << endl;
}
