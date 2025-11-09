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

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int c, n; cin >> c >> n;
    vector<int> pp(n);
    F0R(i, n) cin >> pp[i];
    sort(all(pp));
    vector<pair<int, int>> coins;
    F0R(i, n) {
        if(coins.empty() || coins.back().first!=pp[i]) coins.emplace_back(pp[i], 1);
        else coins.back().s++;
    }
    // trav(u, coins) cout << u.f << " " << u.s << "\n";
    int ans = c;
    map<pair<int, int>, int> mp;
    FOR(add, 0, c-1) {
        int curr = 0;
        int j = coins.size()-1;
        bool add_taken = false;
        bool ok = true;
        while(j >= 0 && curr < c) {
            int xxf = coins[j].f, xxs = coins[j].s;
            if(xxf==add) {xxs++; add_taken=true;}
            if(xxf < add && !add_taken) {xxf = add, xxs = 1, j++; add_taken = true;}
            int vals = (c-curr)/(xxf);
            int to_cnt = min(vals, xxs);
            curr += to_cnt*xxf;
            if(curr==c) {
                ok = false;
                break;
            }
            if(mp.find({c-curr, j})==mp.end()) {
                int lo = -1, hi = j;
                while(hi-lo>1) {
                    int m = (hi+lo)>>1;
                    if(coins[m].f<=c-curr)lo=m;
                    else hi = m;
                }
                mp[{c-curr, j}] = lo;
                j=lo;
            }
            else j = mp[{c-curr, j}];
        }
        if(!add_taken) {
            int xxf = add, xxs = 1;
            int vals = (c-curr)/(xxf);
            int to_cnt = min(vals, xxs);
            curr += to_cnt*xxf;
            if(curr==c) {
                ok = false;
            }
        }
        if(ok) {
            ans = add;
            break;
        }
    }
    if(ans==c) {    
        cout << "Greed is good\n";
    }
    else cout << ans << "\n";
    return 0;
}   
