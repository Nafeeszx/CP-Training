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

const int N = 500005, K = __lg(N)+1;

int jmp[K][N];
ll sm[K][N];

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
    vector<vector<tuple<int, int, int>>> adj(n);
    vector<tuple<int, int, int>> ed;
    F0R(i, m) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(v, w, i);
        adj[v].emplace_back(u, w, i);
        ed.emplace_back(u, v, w);
    }    
    DSU d; d.init(n);
    vector<int> p(m);
    iota(all(p), 0);
    sort(all(p), [&] (int u, int v){
        return get<2>(ed[u]) < get<2>(ed[v]); 
    });
    vector<int> taken(m);
    F0R(i, m) {
        auto [u, v, w] = ed[p[i]];
        if(d.unite(u, v)) taken[p[i]] = 1;
    }
    vector<int> depth(n);
    auto dfs = [&] (auto dfs, int u, int p=0, int dep=0) -> void {
        trav(xx, adj[u]) {
            auto [v, w, i] = xx;
            if(!taken[i] || v==p) continue;
            jmp[0][v] = u;
            sm[0][v] = w;
            depth[v] = depth[u]+1;
            dfs(dfs, v, u, dep+1);
        }
    };
    dfs(dfs, 0);
    FOR(lg, 1, K-1) {
        F0R(i, n) sm[lg][i] = sm[lg-1][i] + sm[lg-1][jmp[lg-1][i]]; 
        F0R(i, n) jmp[lg][i] = jmp[lg-1][jmp[lg-1][i]];
    }
    auto jump = [&] (int u, int k) -> pair<ll, int> {
        int x = u;
        ll dd = 0;
        F0R(i, K) {
            if(k>>i&1) { dd += sm[i][x]; x = jmp[i][x]; }
        }
        // cout << dd << "\n";
        return pair<ll, int>(dd, x);
    };
    bool ok = true;
    F0R(i, m) {
        if(taken[i]) continue;
        auto [u0, v0, w] = ed[i];
        // cout << u0 << " " << v0 << ": ";
        int u = u0, v = v0;
        if(depth[u] > depth[v]) swap(u, v);
        ll d_curr = 0;
        if(depth[u] != depth[v]) {
            auto pp = jump(v, depth[v]-depth[u]);
            d_curr += pp.f;
            v = pp.s;
        }
        if(u != v) {
            ROF(lg, K-1, 0) {
                if(jmp[lg][u] == jmp[lg][v]) continue;
                d_curr += sm[lg][u] + sm[lg][v];
                u = jmp[lg][u], v = jmp[lg][v];
            }
            // cout << u << " " << v << " ";
            d_curr += sm[0][u] + sm[0][v];
        }
        // cout << d_curr << "\n";
        if(d_curr > w) ok = false;
    }
    cout << (ok ? "Yes" : "No");
    return 0;
}   
