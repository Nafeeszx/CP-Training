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

const ll mod = 1000003;


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

using S = pair<int, int>;

S op (S a, S b) {
    return max(a, b);
}
S e() {
    return {0, -1};
}


int main() {    
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> p(n);
    F0R(i, n) cin >> p[i];
    segtree<S, op, e>ST(n);
    F0R(i, n) {
        ST.set(i,{p[i], i});
    }
    ll ans = 0;
    vector<set<int>> ap;
    auto dnc = [&] (auto dnc, int x, int l, int r) -> void {
        if(r-l<1) return;
        // cout << x << " [" << l << " " << r << "]\n"; 
        ap.push_back({});        
        auto [val, m] = ST.prod(l, r);
        int c1 = ap.size();
        dnc(dnc, ap.size(), l, m);
        int c2 = ap.size();
        dnc(dnc, ap.size(), m+1, r);  
        int c3 = ap.size();
        if(c1==c2 && c2==c3) {
            ap[x].insert(p[l]);
        }
        else if(c1==c2) {
            swap(ap[x], ap[c2]);
            // ans += gs[x].cnt(p[m], val);
            ap[x].insert(p[m]);
        }
        else if(c2==c3) {
            swap(ap[x], ap[c1]);
            // ans += gs[x].cnt(p[m], val);
            ap[x].insert(p[m]);
        }
        else {
            // cout << x << "\n";
            swap(ap[x], ap[c2]);
            pair<int, int> to_src = {l, m};
            if(m-l > r-(m+1)) {
                swap(ap[x], ap[c1]);
                to_src = {m+1, r};
            }
            // trav(ggg, gs[x].nums) {
            //     cout << ggg << " ";
            // }
            // cout << "\n";
            // ans += gs[x].cnt(p[m], val);
            FOR(i, to_src.f, to_src.s-1) {
                ans += ap[x].count(p[m]-p[i]);
            }
            FOR(i, to_src.f, to_src.s-1) {
                ap[x].insert(p[i]);
            }
            ap[x].insert(p[m]);
        }
        // cout << x << " [" << l << " " << r << "]\n"; 
    };
    dnc(dnc, 0, 0, n);
    cout << ans << "\n";
    return 0;
}


