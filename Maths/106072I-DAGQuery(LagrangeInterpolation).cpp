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

int dp[1000005][2];

long long exp(long long x, long long y, long long p) {
    long long res = 1; x %= p;
    while (y) {
        if (y & 1) {
            res *= x; res %= p; 
        }
        x *= x; x %= p;
        y >>= 1;
    }
    return res;
}
 

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    F0R(i, m) {
        int x, y; cin >> x >> y;
    }
    if(n==1) {
        cout << "!" << endl;
        int k; cin >> k;
        cout << 1 << endl;
        return 0;
    }
    vector<ll> y(n);
    FOR(i, 1, n-1) {
        cout << "? " << 1 << " " << n << " " << i << endl;
        cin >> y[i];
    }
    ll ans = 0;
    cout << "!" << endl;
    int k ;cin >> k;
    F0R(i, n) {
        ll c = y[i];
        F0R(j, n) if(j != i) {
            c *= (k-j+mod)%mod*exp(i-j+mod, mod-2, mod)%mod;
            c %= mod;
        }
        ans += c;
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}   
