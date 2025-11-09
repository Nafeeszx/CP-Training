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


template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
    segtree() : segtree(0) {}
    segtree(int n) : segtree(std::vector<S>(n, e())) {}
    segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

struct S {
    ll ans, sufc, prefc, prefln, sufln, len;
    S(ll ans=0, ll sufc=0, ll prefc=0, ll prefln=0, ll sufln=0, ll len = 0) : ans(ans), sufc(sufc), prefc(prefc), prefln(prefln), sufln(sufln), len(len) {}
};

S op (S a, S b) {
    S res;
    if(a.len==0) return b;
    if(b.len==0) return a;
    res.prefc = a.prefc;
    res.sufc = b.sufc;
    res.ans = a.ans + b.ans;
    if(a.sufc == b.prefc) res.ans += a.sufln * b.prefln;
    if(a.sufc == b.sufc) res.sufln = a.sufln + b.len;
    else res.sufln = b.sufln;
    if(a.prefc == b.prefc) res.prefln = a.len + b.prefln;
    else res.prefln = a.prefln;
    res.len = a.len+b.len;
    return res;
}
S e() {
    return S();
}

    
void solve(int tc) {

    int n, k, q; cin >> n >> k >> q;
    vector<vector<int>> adj(n), adj_rev(n);
    vector<vector<int>> p;
    F0R(i, k) {
        vector<int> cur(n);
        F0R(j, n) {cin >> cur[j]; cur[j]--; 
            if(j > 0) {
                adj[cur[j-1]].push_back(cur[j]);
                adj_rev[cur[j]].push_back(cur[j-1]);                
            }
        }
        p.emplace_back(cur);
    }    
    vector<int> tops;
    vector<int> vis(n);
    auto dfs = [&] (auto dfs, int u) -> void {
        vis[u] = 1;
        trav(v, adj[u]) if(!vis[v]) {
            dfs(dfs, v);
        }
        tops.push_back(u);
    };
    F0R(i, n) if(!vis[i]) dfs(dfs, i);
    vector<int> col(n);
    vis = vector<int>(n);
    auto rdfs = [&] (auto rdfs, int u, int cc) -> void {
        col[u] = cc;
        vis[u] = 1;
        trav(v, adj_rev[u]) if(!vis[v]) {
            rdfs(rdfs, v, cc);
        }
    };
    int cnt = 1;
    reverse(all(tops));
    trav(u, tops) if(!vis[u]) rdfs(rdfs, u, cnt++);
    vector<segtree<S, op, e>> pst(k, segtree<S, op, e>(n));
    F0R(i, k) {
        auto &c = p[i];
        F0R(j, n) {
            pst[i].set(j, S(0, col[c[j]], col[c[j]], 1, 1, 1));
        }
    }

    ll ans = 0;
    while(q--) {
        int l, r, id; cin >> id >> l >> r;
        id = (id+ans)%k;
        l = (l+ans)%n;
        r = (r+ans)%n + 1;
        auto gg = pst[id].prod(l, r);
        ans = gg.ans;
        cout << ans << "\n";
    }
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    F0R(i, t) solve(i+1);
    return 0;
}   
