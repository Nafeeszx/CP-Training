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
    int n; cin >> n;
    vector<int> v(n), id(2*n, -1);
    DSU d; d.init(4*n);
    F0R(i, n) {
        cin >> v[i];
        F0R(k, 4) {
            int u; cin >> u;
            u--; 
            if(k&1) d.unite(4*i+k, 4*i+k-1);
            if(id[u]==-1) id[u] = 4*i+k;
            else d.unite(4*i+k, id[u]);
        }
    }
    vector<tuple<int, int, int>> ed;
    F0R(i, n) {
        ed.emplace_back(v[i], 4*i+1, 4*i+2);
    }
    sort(all(ed));
    int ans = 0;
    trav(u, ed) {
        auto [w, x, y] = u;
        x = d.get(x);
        y = d.get(y);
        if(x!=y) {
            ans += w;
            d.unite(x, y);
        }
    }
    cout << ans << "\n";
    return 0;
}   
