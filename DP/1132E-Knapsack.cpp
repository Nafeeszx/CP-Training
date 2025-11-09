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
    ll w; cin >> w;
    vector<ll> cnt(9);
    ll sm = 0;
    F0R(i, 8) {
        cin >> cnt[i+1];
        sm += cnt[i+1]*(i+1);
    }
    if(sm <= w) {
        cout << sm << "\n";
        return 0;
    }
    vector<ll> dp(840*8, -1);
    dp[0] = 0;
    FOR(it, 1, 8)  {
        vector<ll> pre(840*8, -1);
        swap(pre, dp);
        FOR(j, 0, min(840/it-1LL, cnt[it])) {
            F0R(x, 840*8) if(pre[x] != -1 && x+j*it < 840*8) dp[x+j*it] = max(pre[x]+(cnt[it]-j)/(840/it), dp[x+j*it]);
        }
    }
    ll ans = 0;
    F0R(x, 840*8) if(dp[x] != -1 && x <= w) ans = max(ans, x+840*min(dp[x], (w-x)/840));
    cout << ans << "\n";  
    return 0;
}   
