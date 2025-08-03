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

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> ed(m);
    vector<vector<pair<int, int>>> adj(n);
    map<pair<int, int>, int> cnt;
    F0R(_, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].emplace_back(v, _);
        adj[v].emplace_back(u, _);
        ed[_] = {u, v};
    }
    vector<int> vis(n);
    vector<int> num(n), low(n), bridge(m);
    int timer = 0;
    auto dfs1 = [&] (auto dfs1, int u, int p = -1)-> void {
        vis[u] = 1;
        num[u] = low[u] = ++timer;
        bool mul_ed = false;
        for(auto [v, id] : adj[u])  {
            if(v==p && !mul_ed) {
                mul_ed = true;
                continue;
            }
            if(vis[v]) {
                low[u] = min(low[u], num[v]); 
            }
            else {
                dfs1(dfs1, v, u);
                low[u] = min(low[u], low[v]);
                if(low[v]==num[v]) {
                    bridge[id] = 1;
                    // cout << id << "\n";
                }
            }
        } 
    };
    F0R(i, n) if(!vis[i]) dfs1(dfs1, i);
    vector<int> d2(n);
    int p; cin >> p;
    F0R(i, p) {
        int u, v; cin >> u >> v;
        u--; v--;
        d2[u]++;
        d2[v]--;
    }
    // F0R(i, n) cout << d2[i] << " ";
    // cout << "\n";
    vis = vector<int>(n);
    vector<char> ans(m, 'B');
    auto dfs2 = [&] (auto dfs2, int u) -> void {
        vis[u]=1;
        for(auto [v, id] : adj[u]) if(!vis[v]) {
            dfs2(dfs2, v);
            d2[u] += d2[v];
            if(!bridge[id] || !d2[v]) continue;
            if(d2[v] > 0 && ed[id].f == u || d2[v] < 0 && ed[id].f == v) ans[id] = 'L';
            else ans[id] = 'R';
        }
    };
    F0R(i, n) if(!vis[i]) dfs2(dfs2, i);
    // F0R(i, n) cout << d1[i] << " ";
    // cout << "\n";
    // F0R(i, n) cout << d2[i] << " ";
    // cout << "\n";
    trav(u, ans) cout << u;
    cout << '\n';
    return 0;
}   
