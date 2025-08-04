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
        int a, b, x, y; cin >> a >> b >> x >> y;
        if(a > b+1) {
            cout << -1 << "\n";
        }
        else if(a==b+1) {
            if(a&1) cout << y << "\n";
            else cout << -1 << "\n";
        }
        else {
            int ans = 0;
            FOR(i, a, b-1) {
                int k = x;
                if(!(i&1)) k = min(k, y);
                ans += k;
            }
            cout << ans << "\n";
        }
    }    
    return 0;
}   
