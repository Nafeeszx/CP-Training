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
    int n; cin >> n;
    vector<int> a(n), ca;
    vector<set<int>> vs(n);
    vector<vector<int>> adj(n);
    F0R(i, n) cin >> a[i];
    ca = a;
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto dfs1 = [&] (auto dfs1, int u=0, int xo=0, int p=-1) -> void {
        a[u] = (a[u]^xo);
        trav(v, adj[u]) if(v != p) dfs1(dfs1, v, a[u], u);
    };
    dfs1(dfs1);
    // trav(u, a) cerr << u << " ";
    // cerr << "\n";
    int ans = 0;

    auto dfs = [&] (auto dfs, int u=0, int p=-1) -> void {
        bool ghapla = false;
        vs[u].insert(a[u]);
        trav(v, adj[u]) if(v != p) {
            dfs(dfs, v, u);
            if(vs[v].size() > vs[u].size()) {
                swap(vs[v], vs[u]);
            }
            trav(x, vs[v]) {
                if(vs[u].count(x^ca[u])) {ghapla = true; break;}
            }
            trav(x, vs[v]) vs[u].insert(x);
        } 
        if(ghapla) {
            vs[u].clear();
            ans++;
        }
    };
    dfs(dfs);
    cout << ans << "\n";
    return 0;
}   
