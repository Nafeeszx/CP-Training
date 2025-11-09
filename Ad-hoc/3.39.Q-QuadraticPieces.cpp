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

void solve()
{
    int n; cin >> n;
    vector<ll> a(n);
    F0R(i, n) cin >> a[i];
    int ans = 1;
    int j = 3;
    while(j < n) {
        ll x1 = a[j]-a[j-1], x2 = a[j-1]-a[j-2], x3 = a[j-2]-a[j-3];
        ll y1 = x3-x2, y2 = x2-x1;
        if(y1==y2) {
            j++;
        }
        else {
            ans++;
            j += 3;
        }
    }
    cout << ans << "\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}   
