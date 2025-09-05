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
#define rsz(x) resize(x)
#define sz(x) (x).size()
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

template<class T> using V = vector<T>;

const ll mod = 1e9 + 7;

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

int main() {
    // SPOJ : Fast Maximum Matching
    int n1, n2, m;
    cin >> n1 >> n2 >> m;
    vector<pair<int, int>> ed;
    F0R(i, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        ed.emplace_back(u, v);
    }
    auto tt = maxMatch(n1, n2, ed);
    cout << tt.size() << "\n";
    return 0;
}