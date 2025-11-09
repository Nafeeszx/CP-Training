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
    int n, m, k; cin >> n >> m >> k;
    vector<int> cur(m), gol(m);
    vector<int> taken(m);
    vector<map<int, int>> cologol(n);
    vector<int> vis(n);
    vector<vector<pair<int, int>>> adj(n);
    F0R(i, m) {
        int u, v; cin >> u >> v >> cur[i] >> gol[i];
        u--; v--;
        cologol[u][gol[i]]++;
        cologol[v][gol[i]]++;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }
    queue<int> q;
    vector<pair<int, int>> res;
    F0R(i, n) {
        if(cologol[i].size()==1) {
            q.push(i);
            vis[i] = 1;
            res.emplace_back(i, (*cologol[i].begin()).first);
            // cout << i << " ";
        }
    }
    // cout << q.size() << "\n";
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        trav(x, adj[u]) if(!taken[x.s]) {
            cologol[x.f][gol[x.s]]--;
            if(cologol[x.f][gol[x.s]] == 0) cologol[x.f].erase(gol[x.s]);
            taken[x.s] = 1;
            // cout << " howwoow\n";
            if(cologol[x.f].size()==1 && !vis[x.f]) {
                q.push(x.f);
                vis[x.f] = 1; 
                res.emplace_back(x.f, (*cologol[x.f].begin()).first);
            }
        }
    }
    bool ok = true;
    F0R(i, m) if(!taken[i]) {
        // cout << i << " ";
        ok &= (cur[i]==gol[i]);
    }
    if(!ok) {
        cout << -1 << "\n";
        return 0;
    }
    reverse(all(res));
    cout << res.size() << "\n";
    trav(u, res) {
        cout << u.f+1 << " " << u.s << "\n";
    }
    return 0;
}   
