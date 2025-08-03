#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for(auto& a : x)
#define FOR(i, a, b) for (int i=(a); i<=(signed)(b); i++)
#define ROF(i, a, b) for (int i=(a); i>=(signed)(b); i--)
#define F0R(i, a) for (int i=0; i<(signed)(a); i++)
#define vi vector<int>
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

const ll mod = 1e9 + 7;

const int N = 100005;
int id[N], low[N], timer;
vector<int> adj[N];
vector<int> x, y;

void dfs(int node, int parent = -1) {
	id[node] = low[node] = ++timer;
	bool multiple_edges = false;

	for (int child : adj[node]) {
		if (child == parent && !multiple_edges) {
			multiple_edges = true;
			continue;
		}
		if (!id[child]) {
			dfs(child, node);
			low[node] = min(low[node], low[child]);
		} else {
			low[node] = min(low[node], id[child]);
		}
	}

	if (low[node] == id[node]) {
		if(parent!=-1) {
            x.push_back(node+1);
            y.push_back(parent+1);
        }
	}
}

struct DSU {
    vi e; 
    void init(int N) { e = vi(N,-1); }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
    bool sameSet(int a, int b) { return get(a) == get(b); }
    int size(int x) { return -e[get(x)]; }
    bool unite(int x, int y) { 
        x = get(x), y = get(y); if (x == y) return 0;
        if (e[x] > e[y]) swap(x,y);
        e[x] += e[y]; e[y] = x; return 1;
    }
};

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    DSU d1, d2;
    d1.init(n);
    d2.init(n);
    F0R(_, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        if(d1.unite(u, v) || d2.unite(u, v)) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    F0R(i, n) if(!id[i]) dfs(i);
    F0R(i, x.size()) cout << x[i] << " " << y[i] << "\n";
    return 0;
}   
