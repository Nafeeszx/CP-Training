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
    int n; cin >> n;
    ll ans = 0, open = 0;
    F0R(i, n) {
        int u;
        cin >> u;

        int mn = (u+1)/2, mx = u;
        if(open > mx) {
            open = mx;
        }
        else if(open < mn) {
            ans += mn-open;
            open = mn;
        }
    }    
    cout << ans;
    return 0;
}   
