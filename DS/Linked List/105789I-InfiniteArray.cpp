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
    const int mxn = 1e6+5;
    vector<int> l(mxn, -1), r(mxn, -1);
    int n; cin >> n;
    vector<int> p(n);
    F0R(i, n) cin >> p[i];
    F0R(i, n-1) {
        r[p[i]] = p[i+1];
        l[p[i+1]] = p[i];
    }
    r[p[n-1]] = p[0];
    l[p[0]] = p[n-1];
    int q; cin >> q;
    while(q--) {
        char c; int x; cin >> c >> x;
        if (c == '+') {
            int y;
            cin >> y;
            int z = l[y];
            l[x] = z, r[x] = y;
            l[y] = x, r[z] = x;
        }
        else if (c == '-') {
            int y = l[x], z = r[x];
            r[y] = z, l[z] = y;
            l[x] = r[x] = -1;
        }
        else {
            vector<int> a(x);
            F0R(i, x) cin >> a[i];
            int ans = 0, cur = 0;
            F0R(i, 2*x) {
                int y = a[i%x];
                int prevy = a[(i-1+x)%x];
                if(l[y]==-1) cur = 0;
                else if(l[y]!=prevy) cur=1;
                else cur++;
                ans = max(ans, cur);
            }
            if(ans <= x) cout << ans << "\n";
            else cout << "*\n";
        }
    }
    return 0;
}   
