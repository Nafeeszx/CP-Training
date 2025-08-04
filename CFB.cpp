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
        int n; cin >> n;
        ll px, py, qx, qy;
        cin >> px >> py >> qx >> qy;
        ll dist = (px-qx)*1LL*(px-qx) + (py-qy)*1LL*(py-qy);
        ll sm = 0, mx = 0;
        F0R(i, n) {
            ll k; cin >> k;
            sm += k;
            mx = max(mx, k);
        }
        ll maxx = sm, minn = max(0LL, 2*mx-sm);
        maxx *= maxx;
        minn *= minn;
        cout << (minn <= dist && dist <= maxx ? "Yes" : "No") << "\n";
    }    
    return 0;
}   
