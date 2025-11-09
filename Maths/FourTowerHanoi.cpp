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

ll binexp(ll a, ll b) {
    ll res = 1;
    ll x = a;
    while(b) {
        if(b&1) res *= x, res %= mod;
        x *= x;
        x %= mod;
        b >>=1;
    }
    return res;
}

ll g(ll a) {
    if(a==1) return 1;
    if(a==2) return 3;
    if(a==3) return 5;
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll n; cin >> n;
    if(n <= 4) {
        cout << g(n) << "\n";
        return 0;
    }
    ll b = 5, diff = 4, x = 3, ser_diff = 3;
    while(true) {
        if(n <= x + ser_diff) {
            ll cont = (n-x);
            b += cont * (diff % mod) % mod;
            b %= mod;
            break;
        }
        b += ser_diff * diff % mod;
        x += ser_diff;
        diff *= 2;
        diff %= mod;
        b %= mod;
        ser_diff++;
    }
    cout << b << "\n";
    return 0;
}   
