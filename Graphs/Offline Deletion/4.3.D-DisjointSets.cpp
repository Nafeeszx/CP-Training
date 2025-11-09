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

#include <bits/stdc++.h>
 
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

struct DSU {
    std::vector<std::pair<int &, int>> his;
    
    int n;
    std::vector<int> f;
    
    DSU(int n_) : n(n_), f(n, -1) {}
    
    int find(int x) {
        if (f[x] < 0) {
            return x;
        }
        auto u = find(f[x]);
        return u;
    }
    
    void set(int &a, int b) {
        his.emplace_back(a, a);
        a = b;
    }
    
    void merge(int a, int b, int &conn) {
        auto u = find(a);
        auto v = find(b);
        if (u == v) {
            return;
        }
        if (f[u] > f[v]) {
            std::swap(u, v);
        }
        set(f[u], f[u] + f[v]);
        set(f[v], u);
        conn--;
    }
    
    int timeStamp() {
        return his.size();
    }
    
    void rollback(int t) {
        while (his.size() > t) {
            auto [x, y] = his.back();
            x = y;
            his.pop_back();
        }
    }
};

int task(int n, vector<pair<int, int>> &edges, vector<int> &lyf, int c, bool print) {
    
    const int N = (1<<(__lg(c)+2));
    vector<vector<pair<int, int>>> ed(N);
    auto add = [&] (auto add, int p, int l, int r, int x, int y, pair<int, int>e) -> void {
        if(l >= y || r <= x) return;
        if(l >= x && r <= y) {
            ed[p].emplace_back(e);
            return;
        }
        int m = (l+r)>>1;
        add(add, (p<<1), l, m, x, y, e);
        add(add, (p<<1)^1, m, r, x, y, e);
    };
    F0R(i, edges.size()) {
        auto u = edges[i];
        add(add, 1, 0, c, 0, lyf[i], u);
    }
    DSU d(n);
    vector<int> ans(c);
    auto dfs = [&] (auto dfs, int p, int l, int r, int comp) -> void {
        if(l >= c) return;
        int t = d.timeStamp();
        trav(u, ed[p]) {
            d.merge(u.f, u.s, comp);
        }
        if(r-l==1) {
            ans[l] = (comp==1);
        }
        else {
            int m = (l+r)>>1;
            dfs(dfs, (p<<1), l, m, comp);
            dfs(dfs, (p<<1)^1, m, r, comp);
        }
        d.rollback(t);
    };
    dfs(dfs, 1, 0, c, n);
    if(print) {
        FOR(i, 1, c-1) cout << ans[i] << "\n";
    }
    FOR(i, 0, c-1) {
        if(!ans[i]) return i;
    }
    return c;
}
 

void solve()
{
    int n, m, q; cin >> n >> m >> q;
    vector<pair<int, int>> ed;
    F0R(i, m) {
        int u, v; cin >> u >> v;
        ed.push_back(minmax({u, v}));
    }
    sort(all(ed));
    vector<pair<int, int>> vvs(q);
    F0R(i, q) {
        cin >> vvs[i].f >> vvs[i].s;
    }
    int con = -1, discon = q+1;
    vector<int> tpow(q+1), thpow(q+1);
    tpow[0] = thpow[0] = 1;
    FOR(i, 1, q) {
        tpow[i] = 2*tpow[i-1]%n;
        thpow[i] = 3*thpow[i-1]%n;
    }
    {
        int m = q;
        vector<int> lyf(m, m+1);
        int aa = 0, bb = 0;
        F0R(i, m) {
            if(i != 0) {
                aa += tpow[i-1], bb += thpow[i-1]; 
                aa %= n; bb %= n;
            }
            auto uu = vvs[i];
            uu.f += aa; uu.f %= n;
            uu.s += bb; uu.s %= n;
            auto u = minmax({uu.f, uu.s});
            auto idx = lower_bound(all(ed), u) - ed.begin();
            if(idx < lyf.size() && idx < ed.size() && ed[idx] == u) {
                lyf[idx] = min(lyf[idx], i+1);
            }
        }
        discon = task(n, ed, lyf, m+1, false);
    }   
    // cout << discon << " asd\n";
    vector<int> lyf(m, q+1);
    int aa = 0, bb = 0;
    F0R(i, q) {
        if(i != 0) {
            if(i < discon) {
                aa += tpow[i-1], bb += thpow[i-1]; 
                aa %= n; bb %= n;
            }
            else {
                aa *= 2, bb *= 3;
                aa %= n; bb %= n;
            }
        }
        auto uu = vvs[i];
        uu.f += aa; uu.f %= n;
        uu.s += bb; uu.s %= n;
        auto u = minmax({uu.f, uu.s});
        auto idx = lower_bound(all(ed), u) - ed.begin();
        if(idx < lyf.size() && idx < ed.size() && ed[idx] == u) {
            lyf[idx] = min(lyf[idx], i+1);
        }
    }
    task(n, ed, lyf, q+1, true);
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}   
