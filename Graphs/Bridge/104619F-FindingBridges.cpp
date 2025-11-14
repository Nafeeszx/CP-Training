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
typedef unsigned long long ll;

const ll mod = 998244353;

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

using pii = pair<int, int>;

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    vector<pii> ed, ed_serial;
    int n, m, q; cin >> n >> m >> q;
    F0R(i, m) {
        int u, v; cin >> u >> v; u--; v--;
        ed.emplace_back(minmax(u, v));
    }  
    map<pii, int> ed_id;
    int cnt = m;
    F0R(i, q) {
        int u, v; cin >> u >> v; u--; v--;
        auto x = minmax(u, v);
        ed_serial.push_back(x);
        ed_id[x] = cnt--;
    }
    trav(u, ed) {
        if(ed_id.find(u)==ed_id.end()) {
            ed_id[u] = cnt--;
            ed_serial.push_back(u);
        }
    }
    reverse(all(ed_serial));
    DSU d; d.init(n);
    vector<vector<int>> adj(n);
    map<pii, int> tree_edge;
    trav(u, ed_serial) {
        auto [x, y] = u;
        if(d.unite(x, y)) {
            tree_edge[u] = 1;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }
    vector<int> depth(n), par(n);
    auto dfs = [&] (auto dfs, int u, int p=-1, int d=0) -> void {
        depth[u]=d;
        par[u] = p;
        trav(v, adj[u]) if(v != p) {
            dfs(dfs, v, u, d+1);
        }
    };
    F0R(i, n) if(d.get(i)==i) dfs(dfs, i);
    vector<int> p(n);
    iota(all(p), 0);
    auto find = [&] (auto find, int x) -> int {
        return(p[x]==x ? x : p[x] = find(find, p[x]));
    };
    auto unite = [&] (int u, int v) {
        u = find(find, u), v = find(find, v);
        if(depth[u] < depth[v]) {
            p[v] = u;
        }
        else {
            p[u] = v;
        }
    };

    vector<int> ans = {0};
    int curr_ans = 0;
    trav(x, ed_serial) {
        auto [u, v] = x;
        // cout << u << " " << v << "\n";
        if(tree_edge.find(x) != tree_edge.end()) {
            curr_ans++;
        } 
        else {
            u = find(find, u), v = find(find, v);
            while(u != v) {
                if(depth[u] < depth[v]) {
                    unite(v, par[v]);
                    v = find(find, v);
                }
                else {
                    unite(u, par[u]);
                    u = find(find, u);
                }
                curr_ans--;
            }
        }
        ans.push_back(curr_ans);
    }
    reverse(all(ans));
    FOR(i, 1, q) cout << ans[i] << "\n";
    cout << "\n";
    return 0;
}   
