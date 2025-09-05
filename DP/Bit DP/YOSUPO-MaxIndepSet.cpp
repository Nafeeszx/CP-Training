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

int adj[40][40];

int bpc(ll x) {
    int ans = 0;
    F0R(j, 40) if(x>>j&1) ans++;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    F0R(i, m) {
        int u, v; cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }
    int n1 = min(n, 20);
    int n2 = n-n1;
    vector<int> dp1(1<<n1);
    ll res = 0;
    F0R(i, 1<<n1) {
        vector<int> nodes;
        F0R(j, n1) {
            if(i>>j&1) nodes.push_back(j);
        } 
        int x = nodes.size();
        bool ok = true;
        F0R(mm, x) F0R(nn, mm) {
            ok&=!adj[nodes[mm]][nodes[nn]];
        }
        dp1[i] = ok;
        if(ok && bpc(i) > bpc(res)) {
            res = i;
        }
    }
    if(!n2) {
        cout << bpc(res) << "\n";
        F0R(j, n1) {
            if(res>>j&1) {
                cout << j << " ";
            }
        }
        return 0;
    }
    vector<vector<int>> adj_list(n1);
    F0R(i, n1) {
        FOR(j, n1, n1+n2-1) {
            if(adj[i][j]) adj_list[i].push_back(j-n1);
        }
    }
    vector<int> dp2(1<<n2);
    F0R(i, 1<<n2) {
        vector<int> nodes;
        F0R(j, n2) {
            if(i>>j&1) nodes.push_back(j+n1);
            if(bpc(dp2[i^(1<<j)]) > bpc(dp2[i])) {
                dp2[i] = dp2[i^(1<<j)];
            }
        } 
        int x = nodes.size();
        bool ok = true;
        F0R(mm, x) F0R(nn, mm) {
            ok&=!adj[nodes[mm]][nodes[nn]];
        }
        if(ok && bpc(i) > bpc(dp2[i])) dp2[i] = i;
    }
    F0R(i, 1<<n1) {
        int bits = (1<<(n2))-1;
        F0R(j, n1) {
            if(i>>j&1) {
                trav(u, adj_list[j]) bits &= (~(1<<u));
            }
        } 
        if(dp1[i] && bpc(i) + bpc(dp2[bits]) > bpc(res)) {
            res = (i | ((dp2[bits]*1LL)<<n1));
        }
    }
    cout << bpc(res) << "\n";
    F0R(j, 40) {
        if(res>>j&1) {
            cout << j << " ";
        }
    }
    return 0;
}