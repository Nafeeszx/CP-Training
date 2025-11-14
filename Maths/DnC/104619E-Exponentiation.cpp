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
typedef unsigned long long ll;

const ll mod = 998244353;

void print(__int128_t s) {
    vector<int> g;
    while(s != 0) {
        g.push_back(s%10);
        s /= 10;
    }
    reverse(all(g));
    trav(u, g) cout << u;
    cout << "\n";
}

__int128_t mul_mod(__int128_t a, __int128_t b, __int128_t m) {
    __int128_t res = 0;
    a %= m;
    while (b > 0) {
        if (b & 1) { 
            res += a;
            res %= m;
        }
        a += a;
        a %= m; 
        b >>= 1;         
    }
    return res;
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll a, b, m; cin >> a >> b >> m;
    map<ll, __int128_t> mp;
    __int128_t aa = a, mm = m;
    auto dnc = [&] (auto dnc, ll bi) -> __int128_t {
        if(mp.find(bi)!=mp.end()) return mp[bi];
        if(bi==1) return mp[1]=aa%m;
        if(bi&1) {
            auto x = dnc(dnc, bi/2);
            auto y = dnc(dnc, bi/2+1);
            return mp[bi] = (mul_mod(x, y, mm) + mm - aa%mm) % mm; 
        }
        auto x = dnc(dnc, bi/2);
        return mp[bi] = (mul_mod(x, x, mm) + mm-2%mm) % mm;
    };
    print(dnc(dnc, b));
    return 0;
}   
