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

struct DSU {
    vi e; 
    void init(int N) { e = vi(N,-1); }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
    bool sameSet(int a, int b) { return get(a) == get(b); }
    int size(int x) { return -e[get(x)]; }
    bool unite(int x, int y) { 
        x = get(x), y = get(y); if (x == y) return 0;
        if (e[x] > e[y]) swap(x,y);
        e[x] += e[y]; e[y] = x; return 1;
    }
};

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    DSU red, blue, all;
    red.init(n); blue.init(n); all.init(n);
    int cc = n, cr = n, cb = n, r = 0, b = 0;
    while(q--) {
        int t, u, v; cin >> t >> u >> v;
        u--; v--;
        if(t==1) (++r && red.unite(u, v) ? cr-- : 0);
        if(t==2) (++b && blue.unite(u, v) ? cb-- : 0);
        (all.unite(u, v) ? cc-- : 0);
        int tot = r+b;
        int rmin = cb-cc, bmin = cr-cc, amin = n-cc;
        int ans = min(r-rmin, b-bmin)*2;
        ans = min(ans, (tot-amin)/2*2);
        cout << ans << "\n";
    }  
    return 0;
}   
