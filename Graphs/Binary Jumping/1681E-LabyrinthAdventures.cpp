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

const ll mod = 998244353;

const int N = 100005, K = __lg(N)+1;
ll dp[K][N][2][2];
int X[N][2], Y[N][2];

int main()
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    F0R(k, K)  F0R(i, N) F0R(xx, 2) F0R(yy, 2) dp[k][i][xx][yy] = mod*mod;
    int n; cin >> n;
    FOR(i, 1, n-1) cin >> X[i][0] >> Y[i][0] >> X[i][1] >> Y[i][1];
    FOR(i, 1, n-1-(1<<0)) {
        F0R(k, 4) dp[0][i][k>>1][k&1] = abs(X[i][k>>1]+((k>>1)==0)-X[i+1][k&1])+abs(Y[i][k>>1]+((k>>1)==1)-Y[i+1][k&1])+1;
    }
    // F0R(k, 4) cout << dp[2][k>>1][0][k&1] << " dsadsa\n";
    FOR(lg, 1, K-1) {
        FOR(i, 1, n-1-(1<<lg)) {
            F0R(k, 4) F0R(x, 2) dp[lg][i][k>>1][k&1] = min(dp[lg][i][k>>1][k&1], dp[lg-1][i][k>>1][x] + dp[lg-1][i+(1<<(lg-1))][x][k&1]);
        }
    }
    int q; cin >> q;
    while(q--) {
        pair<int, int> st, ff;
        cin >> st.f >> st.s >> ff.f >> ff.s;
        int lvl_s = max(st.f, st.s), lvl_f = max(ff.f, ff.s);
        if(lvl_s == lvl_f) {
            cout << abs(st.f-ff.f)+abs(st.s-ff.s) << "\n";
            continue;
        }
        if(lvl_s > lvl_f) {swap(st, ff); swap(lvl_s, lvl_f);}
        vector<int> xx = {lvl_s};
        ROF(lg, K-1, 0) {
            if(xx.back()+(1<<lg) >= lvl_f) continue;
            xx.push_back(xx.back()+(1<<lg));
        }
        // trav(u, xx) cout << u << " ";
        // cout << "\n";
        vector<vector<ll>> app(2, vector<ll>(2, mod*mod));
        app[0][0] = 0, app[1][1] = 0;
        F0R(i, xx.size()-1) {
            vector<vector<ll>> pre(xx.size(), vector<ll>(2, mod*mod));
            swap(pre, app);
            F0R(k, 4) F0R(x, 2) {app[k>>1][k&1] = min(app[k>>1][k&1], pre[k>>1][x]+dp[__lg(xx[i+1]-xx[i])][xx[i]][x][k&1]); }
        }
        // F0R(k, 4) cout << app[k>>1][k&1] << "\n";
        ll ans = mod*mod;
        // cout << lvl_s << " " << lvl_f << " heher\n";
        F0R(k, 4) ans = min(ans, app[k>>1][k&1] + abs(X[lvl_s][k>>1]-st.f)+abs(Y[lvl_s][k>>1]-st.s)+abs(X[lvl_f-1][k&1]+((k&1)==0)-ff.f)+abs(Y[lvl_f-1][k&1]+((k&1)==1)-ff.s)+1);
        cout << ans << "\n";
    }
    return 0;
}   
