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
	F k;
    void init(int _N, int _K) { N = _N; k = _K;
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
	C calc(int s, int t) { assert(s != t);
		// F0R(_,N) F0R(e,sz(eds)) { const Edge& E = eds[e]; // Bellman-Ford
		// 	if (E.cap) ckmin(p[E.to],p[eds[e^1].to]+E.cost); }
        FOR(i, 0, N-1) {
            trav(e, adj[i]) {
                const Edge& E = eds[e];
			    if (E.cap) ckmin(p[E.to],p[eds[e^1].to]+E.cost);
            }
        }
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { // p -> potentials for Dijkstra
			F0R(i,N) p[i] += dist[i]; // don't matter for unreachable nodes
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = eds[pre[x]^1].to) {
				const Edge& E = eds[pre[x]]; ckmin(df,E.cap-E.flo); }
            

            F tt = k-totFlow; 
            totFlow += min(df, tt); totCost += (p[t]-p[s])*min(df, tt);
			for (int x = t; x != s; x = eds[pre[x]^1].to)
				eds[pre[x]].flo += df, eds[pre[x]^1].flo -= df;
            if(totFlow==k) break;
		} // get max flow you can send along path
		return totCost;
	}
};

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n); F0R(i, n) cin >> a[i];
    MCMF mf; mf.init(2*n+2, 4);
    F0R(i, n) {
        mf.ae(0, 2*i+1, 1, 0);
    }
    F0R(i, n) {
        mf.ae(2*i+2, 2*n+1, 1, 0);
    }
    F0R(i, n) {
        mf.ae(2*i+1, 2*i+2, 1, -1);
    }
    F0R(i, n) {
        FOR(j, i+1, n-1) {
            if(a[i] % 7 == a[j] % 7 || abs(a[i]-a[j])==1)
                mf.ae(2*i+2, 2*j+1, 1, 0);
        }
    }
    auto xx = mf.calc(0, 2*n+1);
    cout << -xx << "\n";
    
    return 0;
}   
