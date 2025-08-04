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
    int t; cin >> t;
    while(t--) {
        ll n, l, r, k; cin >> n >> l >> r >> k;
        if(n&1) {
            cout << l << "\n";
            continue;
        }
        if(n==2) {
            cout << -1 << "\n";
            continue;
        }
        ll p = __lg(l)+1;
        p = (1LL<<p);
        if(p > r) {
            cout << -1 << "\n";
            continue;
        }
        if(k >= n-1) {
            cout << p << "\n";
        }
        else {
            cout << l << "\n";
        }
    }
    return 0;
}   
