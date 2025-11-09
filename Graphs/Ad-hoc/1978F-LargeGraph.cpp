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
    const int N = 1000000;
    vector<int> composite(N+1), prime;
    FOR(i, 2, N) {
        if(!composite[i]) {
            prime.push_back(i);
            int p = i;
            while(p <= N) {
                composite[p] = i;
                p += i;
            }
        }
    } 
    vector<vector<int>> facs(N+1);
    FOR(i, 2, N) {
        int x = i;
        while(x != 1) {
            int g = composite[x];
            facs[i].push_back(g);
            while(x%g==0) x/=g;
        }
    }
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        ll ans = 0;
        vector<int> a(n);
        F0R(i, n) {
            cin >> a[i]; 
            if(a[i]==1) ans += (i==0?n-1:n-2);
        }
        ans += 2*n-1;
        vector<int> xd;
        FOR(i, 1, n-1) {
            xd.push_back(a[i]);
        } 
        F0R(i, n) xd.push_back(a[i]);
        DSU d; d.init(xd.size());
        n = xd.size();
        map<int, vector<int>> mp;
        F0R(i, n) {
            int u = xd[i];
            trav(x, facs[u]) {
                mp[x].push_back(i);
            }
        }
        trav(u, mp) {
            auto &vv = u.s;
            F0R(i, vv.size()-1) {
                if(vv[i+1]-vv[i] <= k && d.unite(vv[i+1], vv[i])) ans--;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}   
