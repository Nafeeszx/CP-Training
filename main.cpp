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

const ll mod = 1e9 + 7, B = 1000033;

void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    F0R(i, n) cin >> a[i];
    vector<vector<int>> adj(n);
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto dfs = [&] (auto dfs, int u, int p=-1) -> vector<int> {
        bool leaf = true;
        int both0=0, one01=0, one00=0, no0 = 0;
        int both1=0, one10=0, one11=0, no1 = 0;
        trav(v, adj[u]) if(v != p) {
            leaf = false;
            auto x = dfs(dfs, v, u);
            if(x[0]&&x[1]) both0++;
            else if(x[0]) one00++;
            else if(x[1]) one01++;
            else no0++;
            if(x[2]&&x[3]) both1++;
            else if(x[2]) one10++;
            else if(x[3]) one11++;
            else no1++;
        }
        if(leaf) {
            vector<int> c;
            if(a[u]==0) {
                c = {1, 0, 0, 1};
            }
            else {
                c = {0, 1, 1, 0};
            }
            return c;
        }
        vector<int> c(4);
        if(a[u]==1) {
            c[0] = (!no0&&((one01&1)||both0>0));
            c[2] = (!no0&&((~one01&1)||both0>0));
            c[1] = (!no1&&((~one11&1)||both1>0));
            c[3] = (!no1&&((one11&1)||both1>0));
        }
        else {
            c[0] = (!no0&&((~one01&1)||both0>0));
            c[2] = (!no0&&((one01&1)||both0>0));
            c[1] = (!no1&&((one11&1)||both1>0));
            c[3] = (!no1&&((~one11&1)||both1>0));
        }
        return c;

    };
    auto g = dfs(dfs, 0);
    if(g[0] || g[1]) cout << "YES\n";
    else cout << "NO\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}   
