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

void solve()
{
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<int> a(n), b(n);
    F0R(i, n) cin >> a[i];
    F0R(i, n) cin >> b[i];
    vector<map<int, int>> mp(n);
    vector<int> neg(n), pos(n), az(n), bz(n);
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<char> ans(n, '0');
    auto dfs = [&] (auto dfs, int u, int p = -1) -> void {
        if(a[u]==0) az[u]++;
        else {
            mp[u][a[u]]--;
            neg[u]++;
        }
        if(b[u]==0) bz[u]++;
        else {
            int old = mp[u][b[u]];
            int nw = old+1;
            mp[u][b[u]] = nw;
            if(old < 0) {
                neg[u] -= -old;
            }
            else if(old > 0) {
                pos[u] -= old;
            }
            if(nw < 0) {
                neg[u] += -nw;
            }
            else if(nw > 0) {
                pos[u] += nw;
            }
        }

        trav(v, adj[u]) if(v != p) {
            dfs(dfs, v, u);
            if(mp[v].size() > mp[u].size()) {
                swap(mp[v], mp[u]);
                swap(pos[v], pos[u]);
                swap(neg[v], neg[u]);
                swap(az[v], az[u]);
                swap(bz[v], bz[u]);
            }
            az[u] += az[v];
            bz[u] += bz[v];
            trav(x, mp[v]) {
                auto [key, val]  = x;
                int old = mp[u][key];
                int nw = old+val;
                mp[u][key] = nw;
                if(old < 0) {
                    neg[u] -= -old;
                }
                else if(old > 0) {
                    pos[u] -= old;
                }
                if(nw < 0) {
                    neg[u] += -nw;
                }
                else if(nw > 0) {
                    pos[u] += nw;
                }
            }
        }
        if((neg[u]==0 || neg[u] <= bz[u]) && (pos[u]==0 || pos[u] <= az[u])) {
            ans[u] = '1';
        }
    };
    dfs(dfs, 0);
    trav(u, ans) cout << u;
    cout << "\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}   
