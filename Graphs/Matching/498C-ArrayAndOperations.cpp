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
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> ps(n);
    int cntL = 0, cntR = 0;
    F0R(i, n) {
        int u; cin >> u;
        for(int j = 2; j * j <= u; ++j) {
            while(u % j == 0) {
                int id;
                if(i%2) id=cntR++;
                else id=cntL++;
                ps[i].push_back({j,id});
                u /= j;
            }
        }
        if(u > 1) {
            int id;
            if(i%2) id=cntR++;
            else id=cntL++;
            ps[i].push_back({u,id});
        }
    }
    vector<pair<int, int>> ed;
    while(m--) {
        int u, v; cin >> u >> v;
        u--; v--;
        if(u%2) swap(u, v);
        trav(i, ps[u]) trav(j, ps[v]) {
            if(i.f==j.f) {
                ed.emplace_back(i.s, j.s);
            }
        }
    }

    auto tt = maxMatch(cntL, cntR, ed);
    cout << tt.size() << "\n";
    return 0;
}