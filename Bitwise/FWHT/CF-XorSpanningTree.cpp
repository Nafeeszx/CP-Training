// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
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

const ll mod = 1e9 + 7, mod1=998244353;

void fwht(vector<ll> &data, ll p, int dim=1<<17) {
    for (int len = 1; 2 * len <= dim; len <<= 1) {
        for (int i = 0; i < dim; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int a = data[i + j];
                int b = data[i + j + len];
                
                data[i + j] = (a + b) % p;
                data[i + j + len] = (p + a - b) % p;
            }   
        }
    }
}

long long exp(long long x, long long y, long long p) {
    long long res = 1; x %= p;
    while (y) {
        if (y & 1) {
            res *= x; res %= p; 
        }
        x *= x; x %= p;
        y >>= 1;
    }
    return res;
}

long long inv(ll u, ll p) {
    return exp(u, p-2, p);
}
 
void inverse_fwht(vector<ll> &data, ll p, int dim = 1 << 17) {
    fwht(data, p, dim);
    ll inv_dim = inv(dim, p);
    for (int i = 0; i < dim; i++) {
        data[i] = (data[i] * inv_dim) % p;
    }
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    int xo = 0;
    vector<vector<pair<int, int>>> adj(n);
    F0R(i, m) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        xo ^= w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<int> vis(n, 0); 
    vector<pair<int, int>> st;
    vector<vector<ll>> pols;

    auto dfs = [&] (auto dfs, int u, int p, int wv) -> void {
        vis[u] = 1;
        st.push_back({u, wv}); 
        for(auto &[v, w] : adj[u]) {
            if (v == p) continue;
            if (vis[v] == 1) {
                vector<ll> npol(1<<17);
                npol[w]++;
                int idx = st.size() - 1;
                while(st[idx].first != v) {
                    npol[st[idx].second]++;
                    idx--;
                }
                pols.push_back(npol);

            } else if (vis[v] == 0) { 
                dfs(dfs, v, u, w);
            }
        }

        vis[u] = 2;
        st.pop_back();
    };
    dfs(dfs, 0, -1, -1);
    vector<ll> ans(1<<17, 0), ans1(1<<17, 0);
    if(!pols.empty()) {
        ans = pols[0];
        ans1 = pols[0];
        fwht(ans, mod);
        fwht(ans1, mod1);
        FOR(k, 1, pols.size()-1) {
            auto cur_pol = pols[k];
            auto cur_pol1 = pols[k];
            fwht(cur_pol, mod);
            fwht(cur_pol1, mod1);
            F0R(i, 1<<17)  {
                ans[i] *= cur_pol[i];
                ans[i] %= mod;
                ans1[i] *= cur_pol1[i];
                ans1[i] %= mod1;
            }
        }
        inverse_fwht(ans, mod);
        inverse_fwht(ans1, mod1);
    }
    vector<ll> res(1<<17), res1(1<<17);
    F0R(i, 1<<17) {
        res[i^xo] = ans[i];
        res1[i^xo] = ans1[i];
    }
    F0R(i, 1<<17) {
        if(res[i] || res1[i]) {
            cout << i <<  " " << res[i] << "\n";
            return 0;
        }
    }
    return 0;
}   
