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
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n+1);
    vector<ll> a(n+1);
    ll ans = 0;
    FOR(i, 1, n) {
        cin >> a[i];
        if(a[i]!=-1) ans += a[i];
    }
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    adj[0].push_back(1);
    n++;
    vector<ll> rem(n);
    auto dfs = [&] (auto dfs, int u, int p=-1) -> void {
        bool leaf = true;
        trav(x, adj[u]) if(x != p) {
            dfs(dfs, x, u);
            leaf = false;
        }
        if(leaf) {
            if(a[u]==-1) rem[u] = k;
            return;
        }
        ll sm = 0;
        if(a[u] != -1) sm += a[u];
        trav(v, adj[u]) if(v != p) {
            if(a[v] != -1) sm += a[v];
        }
        if(sm > k) {
            cout << -1 << "\n";
            exit(0);
        }
        // cout << u << ": " << sm << "\n";
        trav(v, adj[u]) if(v != p) {
            if(sm <= k) {
                int need = min(k-sm, rem[v]);
                sm += need;
                ans += need;
                // cout << ans << "\n";
            }
        }
        if(a[u] == -1) rem[u] = k-sm;
    };
    dfs(dfs, 0);
    cout << ans << "\n";
    return 0;
}   