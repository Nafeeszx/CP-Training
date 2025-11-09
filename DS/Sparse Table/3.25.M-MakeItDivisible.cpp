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

template <typename T>
struct sparse_table{
    vector<vector<T>> ST1;
    sparse_table(vector<T> &A){
        int N = A.size();
        int LOG = 32 - __builtin_clz(N);
        ST1 = vector<vector<T>>(LOG, vector<T>(N));
        for (int i = 0; i < N; i++){
            ST1[0][i] = A[i];
        }
        for (int i = 0; i < LOG - 1; i++){
            for (int j = 0; j < N - (1 << i); j++){
                ST1[i + 1][j] = gcd(ST1[i][j], ST1[i][j + (1 << i)]);
            }
        }
    }
    T range_gcd(int L, int R){
        if(L==R) return 0;
        int d = 31 - __builtin_clz(R - L);
        return gcd(ST1[d][L], ST1[d][R - (1 << d)]);
    }
};

void solve()
{
    int n, k; cin >> n >> k;
    vector<int> a(n), d;
    vector<int> p(n);
    iota(all(p), 0);
    F0R(i, n) {cin >> a[i]; if(i>0) d.push_back(abs(a[i]-a[i-1]));}
    if(n==1) {
        cout << k << " " << k*1LL*(k+1)/2 << "\n";
        return;
    }
    sparse_table<int> ST(d);
    int ax = ST.range_gcd(0, d.size()); 
    if(ax==0) {
        cout << k << " " << k*1LL*(k+1)/2 << "\n";
        return;
    }
    vector<int> cand;
    for(int i = 1; i*i<=ax; ++i) {
        if(ax%i==0) {
            cand.push_back(ax/i);
            if(i*i!=ax) cand.push_back(i);
        }   
    }
    sort(all(p), [&] (auto x, auto y){
        return a[x] > a[y];
    });
    int mn = a[p.back()];
    vector<int> gc(n);
    {
        set<int> s;
        F0R(i, n) s.insert(i);
        s.insert(-1); s.insert(n);
        trav(idx, p) {
            s.erase(idx);
            auto it = s.upper_bound(idx);
            int r = *it;
            r--;
            it = prev(it);
            int l = *it;
            l++;
            gc[idx] = ST.range_gcd(l, r);
        }
    }
    ll cnt = 0, ans = 0;
    trav(g, cand) {
        if(g <= mn) continue;
        int x = g-mn;
        if(x > k) continue;
        bool ok = true;
        trav(idx, p) {
            if(gcd(gc[idx], a[idx]+x)!=a[idx]+x) {
                ok = false;
                break;
            }
        }
        if(ok) cnt++, ans+=x;
    }
    cout << cnt << " " << ans << "\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}