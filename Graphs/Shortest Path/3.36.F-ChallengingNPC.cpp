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

const ll mod = 1e9+7;

void solve(){
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> col(50);
    vector<vector<int>> adj(n);
    vector<int> c(n);
    F0R(i, n) {
        int u; cin >> u; 
        u--;
        c[i] = u;
        col[u].push_back(i);
    }        
    F0R(i, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }
    F0R(i, 50) {
        queue<tuple<int, int, int>> q;
        vector<int>  vis(n, -1);
        trav(x, col[i]) {q.emplace(x, x, 1); vis[x]=x;}
        while(!q.empty()) {
            auto [u, src, d] = q.front();
            q.pop();
            trav(v, adj[u]) {
                if(v != src && c[v] == i && d+1 <= k) {
                    cout << "NO\n";
                    return;
                }
                if(vis[v]==-1) vis[v] = src, q.emplace(v, src, d+1);
                else if(vis[v] != -2 && vis[v] != src) vis[v] = -2, q.emplace(v, src, d+1); 
            }
        }
    }
    cout << "YES\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();

    return 0;
}   
