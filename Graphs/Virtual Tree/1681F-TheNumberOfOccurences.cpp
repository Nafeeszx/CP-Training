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

struct E {
    int u, w; 
    E(int u, int w) : u(u), w(w) {}
};

ll dp[500100][2];

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<vector<E>> g(n);
    F0R(i, n-1) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--; w--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<int> tin(n), tout(n), siz(n), ord, pw(n);
    auto dfs1 = [&] (auto dfs1, int u, int p=-1) -> void {
        tin[u] = ord.size();
        ord.push_back(u);
        siz[u] = 1;
        trav(v, g[u]) if(v.u != p) {
            pw[v.u] = v.w;
            dfs1(dfs1, v.u, u);
            siz[u] += siz[v.u];
        }
        tout[u] = ord.size();
    };
    dfs1(dfs1, 0);
    vector<vector<int>> sv(n, vector<int>(1));
    trav(u, ord) {
        trav(v, g[u]) {
            sv[v.w].push_back(u);
        }
    }

    ll ans = 0;

    vector<vector<int>> ng(n);
    F0R(i, n) {
        sv[i].erase(unique(sv[i].begin(), sv[i].end()), sv[i].end());
        stack<int> st;
        trav(u, sv[i]) {
            while(!st.empty() && !(tin[st.top()] <= tin[u] && tout[u] <= tout[st.top()])) st.pop();
            if(!st.empty()) ng[st.top()].push_back(u);
            st.push(u);
        }
        auto dfs2 = [&] (auto dfs2, int u) -> ll {
            ll res = 0;
            dp[u][0] = siz[u];
            dp[u][1] = 0;
            trav(v, ng[u]) res += dfs2(dfs2, v), dp[u][0] -= siz[v];
            trav(v, ng[u]) {
                if(pw[v] == i) {
                    res += dp[u][0] * dp[v][0];
                    dp[u][1] += dp[v][0];
                }
                else {
                    res += dp[u][0] * dp[v][1];
                    res += dp[u][1] * dp[v][0];
                    dp[u][0] += dp[v][0];
                    dp[u][1] += dp[v][1];
                }
            }
            return res;
        };
        ans += dfs2(dfs2, 0);
        for (int v : sv[i]) ng[v].clear();
    }
    cout << ans << "\n";
    return 0;
}   