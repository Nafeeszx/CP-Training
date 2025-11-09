#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for (auto &a : x)
#define FOR(i, a, b) for (int i = (a); i <= (signed)(b); i++)
#define ROF(i, a, b) for (int i = (a); i >= (signed)(b); i--)
#define F0R(i, a) for (int i = 0; i < (signed)(a); i++)
#define vi vector<int>
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

const ll inf = 1e18;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // Rolle's Theorem ROFL
    int n; ll k; cin >> n >> k;
    vector<int> a(n);
    ll sm = 0;
    F0R(i, n) { cin >> a[i]; sm += a[i];}
    ll ans = 0;
    F0R(i, n) {
        vector<int> b = a;
        vector<int> cnt(n);
        ROF(i, n-1, 0) {
            if(b[i]==0) cnt[i] = 1;
            if(i+1 < n) cnt[i] += cnt[i+1];
        }
        bool ok = true;
        ll s = sm;
        F0R(i, n) {
            if(b[i] == 0) {
                int x = 0;
                if(i+1 < n) x = cnt[i+1];
                ll need = min(k, k*x - s);
                if(need < -k) {
                    ok = false;
                }
                b[i] = need;
                s += b[i];
            }
        }
        if(ok) {
            ll sm = 0;
            ll curr = 0;
            F0R(i, n) {
                sm += b[i];
                curr = max(curr, sm);
            }
            ans = max(curr, ans);
        }
        rotate(a.begin(), a.begin()+1, a.end());
    }
    if(ans == 0) {
        cout << -1 << "\n";
    }
    else {
        cout << ans+1 << "\n";
    }
    return 0;
}
