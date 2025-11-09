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

const ll mod = 1e9+7;

const int N = 1e5+10;

int dp[2][N];
vector<int> out[N];
int vis[N];

void dfs(int u) {
    int sm0 = 0, sm01 = 0;
    trav(x, out[u]) if(!vis[x]) {
        vis[x] = 1;
        dfs(x);
        sm01 += max(dp[1][x], dp[0][x]);
        sm0 += dp[0][x];
    }
    dp[1][u] = 1+sm0;
    dp[0][u] = sm01;
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> p(n);
    F0R(i, n) {cin >> p[i]; p[i]--; out[p[i]].push_back(i);}

    int ans = 0;
    F0R(i, n) if(!vis[i]) {
        int u = p[i], v = p[p[i]];
        while(u != v) {
            u = p[u];
            v = p[p[v]];
        }
        // cout << u << "\n";
        vector<int> cyc;
        cyc.push_back(u);
        vis[u] = 1;
        u = p[u];
        while(u != cyc[0]) {
            cyc.push_back(u);
            vis[u] = 1;
            u = p[u];
        }
        // cout << cyc.size() << "\n";
        trav(u, cyc) {
            dfs(u);
        }
        // cout << dp[0][0] << " " << dp[1][0] << "\n";
        vector<int> dp0(2, -mod), dp1(2, -mod);
        dp0[1] = dp[1][cyc[0]];
        dp0[0] = dp[0][cyc[0]];
        dp1[0] = dp[0][cyc[0]];
        FOR(i, 1, cyc.size()-1) {
            vector<int> pre(2, -mod);
            swap(pre, dp0);
            dp0[1] = pre[0]+dp[1][cyc[i]];
            dp0[0] = max(pre[0], pre[1])+dp[0][cyc[i]];
        }
        FOR(i, 1, cyc.size()-1) {
            vector<int> pre(2, -mod);
            swap(pre, dp1);
            dp1[1] = pre[0]+dp[1][cyc[i]];
            dp1[0] = max(pre[0], pre[1])+dp[0][cyc[i]];
        }
        ans += max(dp1[1], dp0[0]);
    }
    cout << ans << "\n";
    return 0;
}   
