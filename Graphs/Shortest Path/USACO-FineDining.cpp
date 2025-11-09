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

void setIO(string name = "") { 
    ios_base::sync_with_stdio(0); cin.tie(0);
    if(name.size()){
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}

int main() 
{	
    setIO("dining");
    int n, m, k; cin >> n >> m >>k;
    vector<vector<pair<int, ll>>> adj(n);
    F0R(i, m) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<int> mp(n);
    F0R(_, k) {
        int u, p; cin >> u >> p;
        u--;
        mp[u] = p;
    }
    vector<vector<ll>> d(n, vector<ll>(2, mod));
    using TT = pair<ll, pair<int, int>>;
    priority_queue<TT, vector<TT>, greater<TT>> pq;
    d[n-1][0] = 0;
    pq.emplace(d[n-1][0], make_pair(n-1, 0));
    if(mp[n-1]) {
        d[n-1][1] = -mp[n-1];
        pq.emplace(d[n-1][1], make_pair(n-1, 1));
    }
    while(!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();
        auto [x, y] = u;
        if(dist != d[x][y]) continue;
        if(mp[x] && y != 1) {d[x][1] = d[x][y] - mp[x]; pq.emplace(d[x][1], make_pair(x, 1));}
        trav(v, adj[x]) {
            auto [nv, w] = v;
            if(d[nv][y] > d[x][y] + w) {
                d[nv][y] = d[x][y]+w;
                pq.emplace(d[nv][y], make_pair(nv, y));
            }   
        }
    }   

    F0R(i, n-1) {
        if(d[i][1] <= d[i][0]) {
            cout << 1 << "\n";
        }
        else {
            cout << 0 << "\n";
        }
    }
    return 0;
}   
