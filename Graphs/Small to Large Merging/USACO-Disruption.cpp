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

const ll mod = int(1e9)+7;;


int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);
    int n, m;  cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }   
    vector<set<int>> label(n);
    vector<set<int>> pq(n);
    vector<int> w(m);
    F0R(_, m) {
        int u, v, p; cin >> u >> v >> p;
        w[_] = p;
        u--; v--;
        label[u].insert(_);
        pq[u].insert(p);
        label[v].insert(_);
        pq[v].insert(p);
    }

    vector<int> ans(n-1, mod);
    auto dfs = [&] (auto dfs, int u, int p=-1, int pid=-1) -> void {
        for(auto [v, id]: adj[u]) if(v != p) {  
            dfs(dfs, v, u, id);
            if(label[v].size() > label[u].size()) {swap(label[u], label[v]); swap(pq[u], pq[v]);}
            trav(x, label[v]) {
                if(!label[u].count(x)) {
                    label[u].insert(x);
                    pq[u].insert(w[x]);
                }
                else {
                    // cout << x << " " << id << " " << v << " " << u << "\n";
                    label[u].erase(x);
                    pq[u].erase(w[x]);
                }
            }
        }
        if(!pq[u].empty()) ans[pid] = min(ans[pid], *pq[u].begin());
    };
    dfs(dfs, 0);
    trav(u, ans) cout << (u==mod?-1:u) << "\n";
    return 0;
}   
