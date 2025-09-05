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

ll subc(ll k) {
    return k*(k+1)/2;
}
ll cnt (int a, int b, vector<int>&c, int n) {
    if(a > b) {
        int xx = *max_element(all(c)), yy = *min_element(all(c));
        return subc(yy) + subc(xx-yy-1) + subc(n-1-xx);
    }
    int mnl = 0, mxr = n-1;
    trav(u, c) {
        if(a <= u && u <= b) return 0;
        if(u < a) mnl = max(mnl, u+1);
        if(u > b) mxr = min(mxr, u-1);
    }
    return (a-mnl+1) * 1LL * (mxr-b+1);
};

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<vector<int>> adj(2*n);
    F0R(i, 2*n) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll ans = 2*n*subc(n)*subc(n);
    vector<int> used(2*n);
    F0R(i, 2*n) {
        if(used[i]) continue;
        vector<int> cyc;
        auto dfs = [&] (auto dfs, int u) -> void {
            if(used[u]) return;
            used[u] = 1;
            cyc.push_back(u);
            trav(v, adj[u]) dfs(dfs, v);
        };
        dfs(dfs, i);
        int m = cyc.size(), k = m/2;
        ll now = 0;
        F0R(i, m) {
            int z = cyc[i];
            if(z >= n) z -= n;
            now += subc(n) * (subc(z)+subc(n-1-z));
            int l=n-1, r=0, L=n-1, R=0;
            int nl=i, nr=i;
            F0R(j, k) {
                trav(x, vector<int>({cyc[nl], cyc[nr]})) {
                    if(x < n) l = min(l, x), r = max(r, x);
                    else x-=n, L = min(L, x), R = max(R, x);
                }
                --nl; ++nr;
                if(nl < 0) nl += m;
                if(nr >= m) nr -= m;
                vector<int> f, F;
                trav(x, vector<int>({cyc[nl], cyc[nr]})) {
                    if(x < n) f.push_back(x);
                    else F.push_back(x-=n);
                }
                
                now += cnt(l, r, f, n) * cnt(L, R, F, n);
            }
        } 
        ans -= now;
    }
    cout << ans/2 << "\n";
    return 0;
}   
