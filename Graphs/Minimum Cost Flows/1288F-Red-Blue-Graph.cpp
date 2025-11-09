#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for(auto& a : x)
#define FOR(i, a, b) for (int i=(a); i<=(signed)(b); i++)
#define ROF(i, a, b) for (int i=(a); i>=(signed)(b); i--)
#define F0R(i, a) for (int i=0; i<(signed)(a); i++)
#define vi vector<int>
#define pb push_back
#define rsz(x) resize(x)
#define sz(x) (x).size()
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;


template<class T> bool ckmin(T& a, const T& b) { return a > b ? ((a = b), true) : false; }

template<class T> using V = vector<T>;

const ll mod = 1e9 + 7;

struct MCMF { 
	using F = ll; using C = ll; // flow type, cost type
	struct Edge { int to; F flo, cap; C cost; };
	int N; V<C> p, dist; vi pre; V<Edge> eds; V<vi> adj;
    void init(int _N) { N = _N;
		p.rsz(N), dist.rsz(N), pre.rsz(N), adj.rsz(N); }
	void ae(int u, int v, F cap, C cost) { assert(cap >= 0); 
		adj[u].pb(sz(eds)); eds.pb({v,0,cap,cost}); 
		adj[v].pb(sz(eds)); eds.pb({u,0,0,-cost});
	} // use asserts, don't try smth dumb
	bool path(int s, int t) { // find lowest cost path to send flow through
		const C inf = numeric_limits<C>::max(); F0R(i,N) dist[i] = inf;
		using T = pair<C,int>; priority_queue<T,vector<T>,greater<T>> todo; 
		todo.push({dist[s] = 0,s}); 
		while (sz(todo)) { // Dijkstra
			T x = todo.top(); todo.pop(); if (x.f > dist[x.s]) continue;
			trav(e,adj[x.s]) { const Edge& E = eds[e]; // all weights should be non-negative
				if (E.flo < E.cap && ckmin(dist[E.to],x.f+E.cost+p[x.s]-p[E.to]))
					pre[E.to] = e, todo.push({dist[E.to],E.to});
			}
		} // if costs are doubles, add some EPS so you 
		// don't traverse ~0-weight cycle repeatedly
		return dist[t] != inf; // return flow
	}
	pair<F,C> calc(int s, int t) { assert(s != t);
		F0R(_,N) F0R(e,sz(eds)) { const Edge& E = eds[e]; // Bellman-Ford
			if (E.cap) ckmin(p[E.to],p[eds[e^1].to]+E.cost); }
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { // p -> potentials for Dijkstra
			F0R(i,N) p[i] += dist[i]; // don't matter for unreachable nodes
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = eds[pre[x]^1].to) {
				const Edge& E = eds[pre[x]]; ckmin(df,E.cap-E.flo); }
            if(p[t]-p[s] >= 0) break; 
            totFlow += df; totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = eds[pre[x]^1].to)
				eds[pre[x]].flo += df, eds[pre[x]^1].flo -= df;
		} // get max flow you can send along path
		return {totFlow,totCost};
	}
};

const int INF = 1e9;

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n1, n2, m;
	ll c1, c2;
	cin >> n1 >> n2 >> m >> c1 >> c2;
 
	MCMF mcc;
    mcc.init(n1+n2+2);
    int sauce = n1+n2, sinc = n1+n2+1;
    string le, ri;
	cin >> le >> ri;
 
	for (int j = 0; j < m; ++j) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		mcc.ae(a, n1 + b, 1, c2); // BLUE
		mcc.ae(n1 + b, a, 1, c1); // RED
	}
 
	ll cc = 0;
	for (int i = 0; i < n1; ++i) {
		if (le[i] == 'R') {
			// Left red <- inflow at least outflow + 1
			mcc.ae(i, sinc, 1, -INF);
			mcc.ae(i, sinc, INF, 0);
			++cc;
		} else if (le[i] == 'B') {
			// Left blue <- outflow at least inflow + 1
			mcc.ae(sauce, i, 1, -INF);
			mcc.ae(sauce, i, INF, 0);
			++cc;
		} else {
			// No conditions, unlimited flow both in and out
			mcc.ae(i, sinc, INF, 0);
			mcc.ae(sauce, i, INF, 0);
		}
	}
	for (int i = 0; i < n2; ++i) {
		if (ri[i] == 'B') {
			// Right blue <- inflow at least outflow + 1
			mcc.ae(n1 + i, sinc, 1, -INF);
			mcc.ae(n1 + i, sinc, INF, 0);
			++cc;
		} else if (ri[i] == 'R') {
			// Right red <- outflow at least inflow + 1
			mcc.ae(sauce, n1 + i, 1, -INF);
			mcc.ae(sauce, n1 + i, INF, 0);
			++cc;
		} else {
			// No conditions, unlimited flow both in and out
			mcc.ae(n1 + i, sinc, INF, 0);
			mcc.ae(sauce, n1 + i, INF, 0);
		}
	}
 
	ll cost = cc * INF + mcc.calc(sauce, sinc).s;
	if (cost >= INF) {
		cout << -1 << '\n';
	} else {
		cout << cost << '\n';
		for (int i = 0; i < m; ++i) {
			int d = mcc.eds[4*i].flo - mcc.eds[4*i+2].flo;
			if (d == 1) cout << 'B';
			else if (d == 0) cout << 'U';
			else cout << 'R';
		}
		cout << '\n';
	}

    return 0;
}   
