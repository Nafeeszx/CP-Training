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

mt19937_64 rnd(time(NULL));
using pll = pair<ll, ll>;

int main()
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    F0R(i, n) {
        cin >> a[i];
        a[i]--;
    }
    vector<pll> hsh(n), sumhsh(n);
    auto upd = [&] (pll &x, pll y) -> void {
        x.f ^= y.f;
        x.s ^= y.s;
    };
    F0R(i, n) {
        hsh[i].f = rnd();
        hsh[i].s = rnd();
        sumhsh[i] = hsh[i];
        if(i>0)  upd(sumhsh[i], sumhsh[i-1]);
    }
    auto calc = [&] (int pos) -> ll {
        ll res = 0;
        set<int> sl, sr;
        set<pll> s;
        pll curr = hsh[0], curl = {0,0};
        s.insert(curl);
        sr.insert(0); sl.insert(0);
        int r = pos+1, l = pos-1;
        while(r < n && !sr.count(a[r])) {
            sr.insert(a[r]);
            upd(curr, hsh[a[r]]);
		    ++r;
            while(l >= 0 && !sl.count(a[l]) && a[l] < *sr.rbegin()){
                sl.insert(a[l]);
                upd(curl, hsh[a[l]]);
                s.insert(curl);
                --l;	
            }
            pll need = sumhsh[*sr.rbegin()];
            upd(need, curr);
            if(s.count(need)) res++;
        }
        return res;
    };
    ll res = 0;
    F0R(_, 2) {
        F0R(i, n) if(a[i]==0) {
            if(_==0) res++;
            res += calc(i);
        }
        reverse(all(a));
    }
    cout << res << "\n";
    return 0;
}   
