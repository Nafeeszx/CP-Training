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
    vector<ll> ts(2), ps(2);
    F0R(i, 2) cin >> ps[i] >> ts[i];
    ll h, s; cin >> h >> s;
    vector<ll> dp(h+1, mod*mod);
    dp[0] = 0;
    ll ans = mod*mod;
    F0R(i, h) FOR(j, 1, h-i) F0R(k, 2) {
        // single attack
        ll x = min(h, i + j*(ps[k]-s) + (j*ts[k]/ts[1^k])*(ps[1^k]-s));
        if(x==h) {
            ans = min(ans, dp[i] + j * ts[k]);
        }
        // double attack
        if(j * ts[k] >= ts[1^k]) { // check if double attack is possible
            ll ni = i + (j-1)*(ps[k]-s) + ((j*ts[k])/ts[1^k]-1)*(ps[1^k]-s) + (ps[k]+ps[1^k]-s);
            dp[min(ni,h)] = min(dp[min(ni, h)], dp[i]+j*ts[k]);
        }
    }
    ans = min(ans, dp[h]);
    cout << ans;
    return 0;
}   
