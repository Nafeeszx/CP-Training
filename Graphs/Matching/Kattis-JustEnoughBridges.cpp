#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for(auto& a : x)
#define FOR(i, a, b) for (int i=(a); i<=(signed)(b); i++)
#define ROF(i, a, b) for (int i=(a); i>=(signed)(b); i--)
#define F0R(i, a) for (int i=0; i<(signed)(a); i++)
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pb push_back
#define rsz resize
#define sz(x) (x).size()
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

template<class T> using V = vector<T>;

const ll mod = 1e9 + 7;

void ckmin(int &x, int y) {
    x = min(x, y);
}

vpi maxMatch(int L, int R, const vpi& edges) {
	V<vi> adj = V<vi>(L);
	vi nxt(L,-1), prv(R,-1), lev, ptr;
	F0R(i,sz(edges)) adj.at(edges[i].f).pb(edges[i].s);
	while (true) {
		lev = ptr = vi(L); int max_lev = 0;
		queue<int> q; F0R(i,L) if (nxt[i]==-1) lev[i]=1, q.push(i);
		while (sz(q)) {
			int x = q.front(); q.pop();
			for (int y: adj[x]) {
				int z = prv[y];
				if (z == -1) max_lev = lev[x];
				else if (!lev[z]) lev[z] = lev[x]+1, q.push(z);
			}
			if (max_lev) break;
		}
		if (!max_lev) break;
		F0R(i,L) if (lev[i] > max_lev) lev[i] = 0;
		auto dfs = [&](auto self, int x) -> bool {
			for (;ptr[x] < sz(adj[x]);++ptr[x]) {
				int y = adj[x][ptr[x]], z = prv[y];
				if (z == -1 || (lev[z] == lev[x]+1 && self(self,z))) 
					return nxt[x]=y, prv[y]=x, ptr[x]=sz(adj[x]), 1;
			}
			return 0;
		};
		F0R(i,L) if (nxt[i] == -1) dfs(dfs,i);
	}
	vpi ans; F0R(i,L) if (nxt[i] != -1) ans.pb({i,nxt[i]});
	return ans;
}

struct SCC {
	int N, ti = 0; V<vi> adj;
	vi disc, comp, stk, comps;
	void init(int _N){ N = _N, adj.rsz(N);
		disc.rsz(N), comp.rsz(N,-1);}
	void ae(int x, int y) { adj[x].pb(y); }
	int dfs(int x) {
		int low = disc[x] = ++ti; stk.pb(x);
		trav(y,adj[x]) if (comp[y] == -1) // comp[y] == -1, 
			ckmin(low,disc[y]?:dfs(y));  // disc[y] != 0 -> in stack
		if (low == disc[x]) { // make new SCC
			// pop off stack until you find x
			comps.pb(x); for (int y = -1; y != x;) 
				comp[y = stk.back()] = x, stk.pop_back();
		}
		return low;
	}
	void gen() {
		F0R(i,N) if (!disc[i]) dfs(i);
		reverse(all(comps));
	}
};

int main()
{
    ios_base::sync_with_stdio(NULL); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> ed;
    multiset<pair<int, int>> mp;
    F0R(_, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        ed.emplace_back(u, v);
        mp.insert({u, v});
    }
    auto pp = maxMatch(n, n, ed);
    SCC s;
    s.init(2*n);
    trav(u, pp) {
        mp.erase(mp.find({u.f, u.s}));
        s.ae(u.s+n, u.f);
    }
    trav(u, mp) {
        s.ae(u.f, u.s+n);
    }
    
    int ans = m-n;
    s.gen();
    trav(u, pp) {
        if(s.comp[u.f]==s.comp[u.s+n]) ans++;
    }
    cout << ans << "\n";
    return 0;
}