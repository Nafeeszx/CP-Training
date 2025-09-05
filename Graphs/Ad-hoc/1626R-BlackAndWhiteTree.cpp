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
    int n, m; cin >> n;
    vector<vector<int>> adj1(n);
    vector<int> c(n);
    F0R(i, n) cin >> c[i];
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }
    vector<int> par(n, -1);
    vector<int> sub_bl(n);
    auto dfs = [&] (auto dfs, int u, int p=-1) -> void {
        par[u] = p;
        sub_bl[u] += c[u];
        trav(v, adj1[u]) if(v != p) {
            dfs(dfs, v, u);
            sub_bl[u] += sub_bl[v];
        }
    };
    dfs(dfs, 0);
    vector<vector<int>> adj2(n);
    F0R(i, n) trav(u, adj1[i]) {
        if(u==par[i]) {
            if(c[u] || sub_bl[0]-sub_bl[i] > 1) adj2[u].push_back(i);
        }
        else {
            if(c[u] || sub_bl[u] > 1) adj2[u].push_back(i);
        }
    }
    queue<int> q;
    vector<int> ans(n);
    F0R(i, n) if(c[i]) {q.push(i); ans[i]=1;}
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        trav(v, adj2[u]) if(!ans[v]) {
            ans[v] = 1;
            q.push(v);
        } 
    }
    trav(v,ans) cout << v << " ";
    return 0;
}   
