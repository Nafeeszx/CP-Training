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
    vector<int> col(n);
    F0R(i, n) cin >> col[i];
    vector<vector<int>> adj(n);
    vector<pair<int, int>> ed;
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ed.emplace_back(u, v);
    }
    vector<int> ids(n);
    int num = 0;
    auto dfs1 = [&] (auto dfs1, int u, int p, int cur_num) -> void {
        ids[u] = cur_num;
        trav(v, adj[u]) if(v != p) {
            if(col[v] == col[u]) dfs1(dfs1, v, u, cur_num);
        }
    };
    F0R(i, n) if(!ids[i]) {
        ++num;
        dfs1(dfs1, i, -1, num);
    }
    vector<vector<int>> newg(num+1);
    trav(u, ed) {
        if(ids[u.f] != ids[u.s]) {
            newg[ids[u.f]].push_back(ids[u.s]);
            newg[ids[u.s]].push_back(ids[u.f]);
        }
    }
    int dist=-1, nod;
    auto dfs = [&] (auto dfs, int u, int p, int d = 0) -> void {
        if(d > dist) {
            dist=d;
            nod=u;
        }
        trav(v, newg[u]) if(v != p) {
            dfs(dfs, v, u, d+1);
        }
    };
    dfs(dfs, 1, 0);
    dist=-1;
    dfs(dfs, nod, 0);
    cout << (dist+1)/2 << "\n";
    return 0;
}   
