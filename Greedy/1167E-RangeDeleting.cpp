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

int main() {    
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    // int t; cin >> t;
    // while(t--) {
    int n, x; cin >> n >> x;
    int tx = x;
    vector<int> mx(x+1, -1), mn(x+1, n);
    vector<int> a(n);
    F0R(i, n) {
        int u; cin >> u;
        a[i] = u;
        mx[u] = max(mx[u], i);
        mn[u] = min(mn[u], i);
    }
    int tp = 0;
    while(mx[x]==-1) {x--; tp++;}
    vector<pair<int, int>> catray;
    // F0R(i, x) cout << mn[i] << " " << mx[i] << " dads\n";;
    ROF(i, x, 1) {
        if(mx[i]==-1) {
            catray.emplace_back(catray.back());
            catray.back().s--;
        }
        else {
            if(!catray.empty() && mx[i] > catray.back().first) break;
            catray.emplace_back(mn[i], i);
        }
    } 
    reverse(all(catray));
    // cout << catray.size() << "\n";
    // trav(u, catray) cout << u.f << " " << u.s << "\n";
    ll ans = 0;
    // int tres
    int currmax = -1;
    FOR(h_allowed, 0, x-1) {
        if(h_allowed >= 2) {
            if(currmax > mn[h_allowed]) break;
        }
        currmax = max(currmax, mx[h_allowed]);
        pair<int, int> bunny = {currmax-1, mod};
        auto idx = upper_bound(all(catray), bunny) - catray.begin();
        if(idx==catray.size()) ans += (tx-x+1);
        else ans += (tx-catray[idx].s+1+(catray[idx].s!=h_allowed+1));
        // cout << idx << " :";
        // cout << h_allowed << ": " << ans << "\n";
    }
    bool ok = true;
    F0R(i, n-1) if(a[i] > a[i+1]) {
        ok = false;
        break;
    }
    if(ok) ans = tx*1LL*(tx+1)/2;
    cout << ans << "\n";
    // }
    return 0;
}


