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
    int n, k; cin >> n >> k;
    vector<ll> a(n), b(n);    
    F0R(i, n) cin >> a[i];
    F0R(i, n) cin >> b[i];
    auto chk = [&] (ll x) -> bool {
        vector<vector<int>> box(k+1);
        vector<ll> last_chrg(n);
        F0R(i, n) {
            last_chrg[i] = a[i] % b[i]; 
            ll c = a[i]/b[i]; 
            if(c < k) box[c].push_back(i);
        }
        int last = 0;
        F0R(i, k) { 
            while(last < k && box[last].empty()) last++;
            if(last < i) return false;
            if(last==k) break;
            int xd = box[last].back();
            if(last_chrg[xd] + x < b[xd]) {
                last_chrg[xd] += x;
                continue;
            }
            box[last].pop_back();
            ll new_time = (last_chrg[xd] + x) / b[xd];
            last_chrg[xd] = (last_chrg[xd] + x) % b[xd];
            if(last+new_time<k) box[last+new_time].push_back(xd);
        }
        return true;

    }; 
    const ll MX = 1e13;
    ll lo = -1, hi = MX;
    while(hi-lo>1) {
        ll m = (hi+lo)>>1; (chk(m) ? hi : lo) = m;
    }
    if(hi==MX) cout << -1 << "\n";
    else cout << hi << "\n";
    return 0;
}   
