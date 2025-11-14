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

// The function now returns a vector of the nodes in the minimum vertex cover.
// Note: Nodes from the right partition R are returned as 'node_index + L'
// to distinguish them from the left partition's nodes.
vi minVertexCover(int L, int R, const vpi& edges) {
    // --- START of your original Hopcroft-Karp code ---
    V<vi> adj(L);
    vi nxt(L, -1), prv(R, -1), lev, ptr;
    F0R(i, sz(edges)) adj[edges[i].f].pb(edges[i].s);

    while (true) {
        lev = ptr = vi(L);
        int max_lev = 0;
        std::queue<int> q;
        F0R(i, L) if (nxt[i] == -1) lev[i] = 1, q.push(i);
        while (sz(q)) {
            int x = q.front();
            q.pop();
            for (int y : adj[x]) {
                int z = prv[y];
                if (z == -1) max_lev = lev[x];
                else if (!lev[z]) lev[z] = lev[x] + 1, q.push(z);
            }
            if (max_lev) break;
        }
        if (!max_lev) break;
        F0R(i, L) if (lev[i] > max_lev) lev[i] = 0;
        auto dfs = [&](auto self, int x) -> bool {
            for (; ptr[x] < sz(adj[x]); ++ptr[x]) {
                int y = adj[x][ptr[x]], z = prv[y];
                if (z == -1 || (lev[z] == lev[x] + 1 && self(self, z)))
                    return nxt[x] = y, prv[y] = x, ptr[x] = sz(adj[x]), 1;
            }
            return 0;
        };
        F0R(i, L) if (nxt[i] == -1) dfs(dfs, i);
    }
    // --- END of your original Hopcroft-Karp code ---
    // At this point, `nxt` and `prv` hold the maximum matching.


    // --- START of new code to find the vertex cover ---

    // 1. Keep track of visited nodes in both partitions
    V<bool> visitedL(L, false);
    V<bool> visitedR(R, false);

    // 2. Define the alternating DFS traversal
    //    It takes the current node index and a flag indicating which partition it's in.
    std::function<void(int, bool)> find_cover_dfs =
        [&](int u, bool is_in_L) {
        if (is_in_L) {
            visitedL[u] = true;
            // From a node in L, traverse along UNMATCHED edges to R
            for (int v : adj[u]) {
                if (nxt[u] != v && !visitedR[v]) {
                    find_cover_dfs(v, false); // Now we're in partition R
                }
            }
        } else { // is_in_R
            visitedR[u] = true;
            // From a node in R, traverse back along the MATCHED edge to L
            int v = prv[u];
            if (v != -1 && !visitedL[v]) {
                find_cover_dfs(v, true); // Now we're back in partition L
            }
        }
    };

    // 3. Start the traversal from all UNMATCHED nodes in L
    F0R(i, L) {
        if (nxt[i] == -1) { // Unmatched node
            find_cover_dfs(i, true);
        }
    }

    // 4. Collect the minimum vertex cover nodes
    vi cover_nodes;
    // Add all UNVISITED nodes from L (this is your A_T set)
    F0R(i, L) {
        if (!visitedL[i]) {
            cover_nodes.pb(i);
        }
    }
    // Add all VISITED nodes from R (this is your B_S set)
    F0R(i, R) {
        if (visitedR[i]) {
            cover_nodes.pb(i + L); // Add L to distinguish from left-side nodes
        }
    }

    return cover_nodes;
}