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

const int MX = 5e5+5, K = __lg(MX)+1;
int dp[MX][K];


int main()
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<pair<int, int>> v(n);
    F0R(i, n) {
        cin >> v[i].f >> v[i].s;
        // v[i].f--;
    }
    sort(all(v));
    vector<int> pref(MX, 0);
    iota(all(pref), 0);
    trav(u, v) {
        pref[u.f] = max(pref[u.f], u.s);
    }
    FOR(i, 1, MX-1) {
        pref[i] = max(pref[i-1], pref[i]);
    }
    // FOR(i, 0, 5) cout << pref[i] << " ";
    // cout << "\n"; 
    FOR(i, 0, MX-1) dp[i][0] = pref[i];
    FOR(lg, 1, K-1) {
        FOR(i, 0, MX-1) dp[i][lg] = dp[dp[i][lg-1]][lg-1];
    }
    // FOR(k, 0, 4) {
    //     FOR(i, 0, 6) cout << dp[i][k] << " ";
    //     cout << "\n"; 
    // }
    while(q--) {
        int x, y; cin >> x >> y;
        // x--;
        int u = x, ans = 0;
        ROF(k, K-1, 0) {
            if(dp[u][k] >= y) continue;
            ans += (1<<k);
            u = dp[u][k];
        } 
        cout << (ans+1==524288 ? -1 : ans+1) << "\n";
    }
    return 0;
}   
