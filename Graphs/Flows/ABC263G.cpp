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
	struct Edge { int to; F flo, cap; };
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
};

int main() {
    const int mxn=2e7;
    int n;
    cin >> n;
    vector<int> composite(mxn+1), prime;
    FOR(i, 2, mxn) {
        if(!composite[i]) {
            prime.push_back(i);
            int p = 2*i;
            while(p <= mxn) {
                composite[p] = 1;
                p += i;
            }
        }
    } 
    vector<pair<int, int>> od, ev;
    ll c = 0;
    F0R(i, n) {
        int u, v; cin >> u >> v;
        if(u==1) c = v;
        if(u&1) od.emplace_back(u, v);
        else ev.emplace_back(u, v);
    } 
    if(od.empty()) {
        cout << 0 << "\n";
        return 0;
    }
    if(ev.empty()) {
        cout << (c/2) << "\n";
        return 0;
    }
    const ll inf = 1e18;
    ll fc, f0;
    {
        // finds fc
        Dinic D;
        D.init(n+2);
        F0R(i, od.size()) {
            D.ae(n, i, od[i].s);
        }
        F0R(j, ev.size()) {
            D.ae(j+od.size(), n+1, ev[j].s);
        }
        F0R(i, od.size()) F0R(j, ev.size()) {
            int x = od[i].f+ev[j].f;
            int idx = lower_bound(all(prime), x) - prime.begin();
            if(prime[idx]==x) D.ae(i, j+od.size(), inf);
        }
        fc = D.maxFlow(n, n+1);
    }
    
    {
        // finds f0
        if(od.size()==1) {
            if(od[0].f==1) f0 = 0;
            else f0 = fc;
        }
        else {
            Dinic D;
            D.init(n+2);
            FOR(i, 0, od.size()-1) {
                if(od[i].f==1) continue;
                D.ae(n, i, od[i].s);
            }
            F0R(j, ev.size()) {
                D.ae(j+od.size(), n+1, ev[j].s);
            }
            F0R(i, od.size()) F0R(j, ev.size()) {
                int x = od[i].f+ev[j].f;
                int idx = lower_bound(all(prime), x) - prime.begin();
                if(prime[idx]==x) D.ae(i, j+od.size(), inf);
            }
            f0 = D.maxFlow(n, n+1);
        }
    }
    cout << fc + (c-(fc-f0))/2;
    return 0;
}