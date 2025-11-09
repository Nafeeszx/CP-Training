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

const ll mod = 998244353;

ll fac[3005];

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    F0R(i, n-1) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll ans = 1;
    vector<ll> cnt(n+1);
    auto dfs = [&] (auto dfs, int u, int dep=1, int p=-1) -> void {
        cnt[dep]++;
        trav(v, adj[u]) if(v != p) {
            dfs(dfs, v, dep+1, u);
        }
    };
    F0R(i, n) dfs(dfs, i);
    FOR(i, 2, n) {
        ans += (cnt[i]/2)%mod*((fac[i] +2*mod- 2*fac[i-1] + fac[i-2])%mod)%mod;
        ans %= mod;
    }
    cout << ans << "\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    fac[0] = 1;
    FOR(i, 1, 3000) fac[i] = i*fac[i-1]%mod;
    while(t--) solve();
    return 0;
}   
