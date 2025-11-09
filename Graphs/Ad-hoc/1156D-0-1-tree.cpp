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

const int N = 200000;
vector<int> adj[N][2];

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    F0R(i, n-1) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u][w].push_back(v);
        adj[v][w].push_back(u);
    }
    vector<vector<int>> xx(2, vector<int>(n, -1));
    ll res = 0;
    F0R(i, n) {
        vector<vector<int>> comps(2);
        auto dfs = [&] (auto dfs, int u, int p, int col) -> void {
            comps[col].push_back(u);
            xx[col][u] = 0;
            trav(v, adj[u][col]) if(xx[col][v]==-1) {
                dfs(dfs, v, u, col);
            }
        };
        F0R(j, 2) if(xx[j][i]==-1) {dfs(dfs, i, -1, j); res += comps[j].size()*1LL*(comps[j].size()-1);}
        F0R(j, 2) trav(x, comps[j]) {
            xx[j][x] = comps[j].size();
        } 
    }
    // cout << res << "\n";
    F0R(i, n) {
        res += (xx[0][i]-1)*1LL*(xx[1][i]-1);
    }
    cout << res << "\n";
    return 0;
}   
