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

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    F0R(i, n) {cin >> a[i]; }
    ll base = 0;
    while(!a.empty() && a.back()==1) base += a.back(), a.pop_back();
    reverse(all(a));
    while(!a.empty() && a.back()==1) base += a.back(), a.pop_back();
    reverse(all(a));
    ll ans = 1; double ansd = 1;
    n = a.size();
    if(n==0) {
        cout << base << "\n";
        return;   
    }
    trav(u, a) {
        ans *= u;
        ans %= mod;
        if(ansd < 1e12) {
            ansd *= u;
        }
    }
    if(ansd >= 1e12) {
        ans += base;
        ans %= mod;
        cout << ans << "\n";
        return;
    }
    vector<ll> pops, cops;
    F0R(i, n) {
        if(i==0 || a[i-1] == 1 && a[i] > 1 || a[i-1] > 1 && a[i]==1) {
            pops.push_back(a[i]);
            if(a[i]==1) cops.push_back(1);
            else cops.push_back(2);
        }
        else {
            if(a[i-1]==1) pops.back()++;
            else pops.back() *= a[i];
        }
    }
    // trav(u, pops) cout << u << "\n";
    vector<ll> dp(pops.size(), 0);
    F0R(i, pops.size()) {
        ll curr = 1;
        if(i > 0 && cops[i] == 1) dp[i] = dp[i-1]+pops[i];
        ROF(j, i, 0) {
            if(cops[j]==2) curr *= pops[j];
            if(j==0) dp[i] = max(dp[i], curr);
            else dp[i] = max(dp[i], curr + dp[j-1]); 
        }
    }
    cout << (base+dp.back())%mod << "\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}   
