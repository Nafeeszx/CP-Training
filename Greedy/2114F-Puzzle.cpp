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

#define int ll
signed main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int p, s; cin >> p >> s;
        int g = gcd(p, s);
        p /= g;
        s /= g;
        if(p%2) {
            p*=2, s*=2;
        }

        int found = 0;
        vector<pair<int, int>> res;
        for(int a=s; a <= 50000; a += s) {
            int P = p * (a/s);
            int w = (P/2)/2, h = P/2-w; // w and h is chosen as close as possible to maximize the area inside h x w block
            if(a > h * w) continue;
            if(a < h+w-1) continue;
            int x = a;
            F0R(i, h) {
                res.emplace_back(i, 0);
                x--;
            }
            FOR(i, 1, w-1) {
                res.emplace_back(0, i);
                x--;
            }
            FOR(i, 1, h-1) FOR(j, 1, w-1) {
                if(x) {
                    x--;
                    res.emplace_back(i, j);
                }
            }
            found = 1;
            break;
        }
        if(found) {
            cout << res.size() << "\n";
            trav(u, res) cout << u.f << " " << u.s << "\n";
        }
        else cout << -1 << "\n";
    }
    return 0;
}   
