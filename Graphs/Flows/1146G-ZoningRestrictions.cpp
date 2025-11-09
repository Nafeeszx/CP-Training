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

template<class T> using V = vector<T>;

const ll mod = 1e9 + 7;

struct Dinic {
	using F = ll; // flow type
	struct Edge { int to; F flo, cap, id; };
	int N; V<Edge> eds; V<vi> adj;
	void init(int _N) { N = _N; adj.rsz(N), cur.rsz(N); }
	void ae(int u, int v, F cap, F rcap = 0) { assert(min(cap,rcap) >= 0); 
		adj[u].pb(sz(eds)); eds.pb({v,0,cap});
		adj[v].pb(sz(eds)); eds.pb({u,0,rcap});
	}
	vi lev; V<vi::iterator> cur;
	bool bfs(int s, int t) { // level = shortest distance from source
		lev = vi(N,-1); F0R(i,N) cur[i] = begin(adj[i]);
		queue<int> q({s}); lev[s] = 0; 
		while (sz(q)) { int u = q.front(); q.pop();
			trav(e,adj[u]) { const Edge& E = eds[e];
				int v = E.to; if (lev[v] < 0 && E.flo < E.cap) 
					q.push(v), lev[v] = lev[u]+1;
			}
		}
		return lev[t] >= 0;
	}
	F dfs(int v, int t, F flo) {
		if (v == t) return flo;
		for (; cur[v] != end(adj[v]); cur[v]++) {
			Edge& E = eds[*cur[v]];
			if (lev[E.to]!=lev[v]+1||E.flo==E.cap) continue;
			F df = dfs(E.to,t,min(flo,E.cap-E.flo));
			if (df) { E.flo += df; eds[*cur[v]^1].flo -= df;
				return df; } // saturated >=1 one edge
		}
		return 0;
	}
	F maxFlow(int s, int t) {
		F tot = 0; while (bfs(s,t)) while (F df = 
			dfs(s,t,numeric_limits<F>::max())) tot += df;
		return tot;
	}

    vector<pair<int, int>> mc (int s) {
        vector<bool> s_side(N, false);
        queue<int> q;
        q.push(s);
        s_side[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int edge_idx : adj[u]) {
                const Edge& e = eds[edge_idx];
                if (e.flo < e.cap && !s_side[e.to]) {
                    s_side[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        vector<pair<int, int>> cut_edges;
        for (int i = 0; i < eds.size(); i += 2) {
            int u = eds[i^1].to;
            int v = eds[i].to;
            if (s_side[u] && !s_side[v]) {
                cut_edges.push_back({u, v});
            }
        }
        
        return cut_edges;
    }
};

int main() {
    int n, h, m;
    cin >> n >> h >> m;
    Dinic mf;
    mf.init(n*h+m+2);
    const int S = n*h+m, T = n*h+m+1; 
    ll ans = n*h*h;
    F0R(i, n) {
        F0R(j, h) {
            mf.ae(S, i*h+j, 2*j+1);
            // cout << S << " " << i*h+j << " " << 2*j+1 << "\n";
            if(j+1<h) {
                mf.ae(i*h+(j+1), i*h+j, mod*mod);
                // cout << i*h+j+1 << " " << i*h+j << " " << mod*mod << "\n"; 
            }
        }
    }
    F0R(i, m) {
        int l, r, x, c; cin >> l >> r >> x >> c;
        l--; r--; 
        if(x==h) continue;
        FOR(k, l, r) {
            mf.ae(k*h+x, n*h+i, mod*mod);
            // cout << k*h+x << " " << T << " " << c << "\n";
        }
        mf.ae(n*h+i, T, c);
    }
    ans -= mf.maxFlow(S, T);
    cout << ans << " ";
    return 0;
}