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
    vector<vector<int>> adj(n);
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }    

    vector<int> d(n);
    auto dfs = [&] (auto dfs, int u, int p=-1) -> void {
        trav(v, adj[u]) if(v != p) {
            d[v] = d[u]+1;
            dfs(dfs, v, u);
        }
    };
    auto ck_mx = [&] (int par) -> vector<int> {
        vector<int> cch;
        int mx = -1;
        F0R(i, par) {
            if(d[i] > mx) {
                cch.clear();
                cch.push_back(i);
                mx = d[i];
            }
            else if(d[i]==mx) {
                cch.push_back(i);
            }
        }
        return cch;
    };
    int dim;
    vector<int>d1,d2;
    {
        d = vector<int>(n);
        dfs(dfs, 0);
        auto pp = ck_mx(n);
        int nn = pp[0];
        d = vector<int>(n);
        dfs(dfs, nn);
        d1 = d;
        auto pp1 = ck_mx(n);
        int nn1 = pp1[0];
        dim = d[pp1[0]];
        d = vector<int>(n);
        dfs(dfs, nn1);
        d2 = d;
    }
    cout << (dim%3!=1 ? "First" : "Second") << "\n";
    return 0;
}   
