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

const ll inf = 1e18;

const int N = 1000000, K = __lg(N)+1; 
int vis[N];
vector<int> out[N];
int mxlen[N];

void dfs(int u) {
    trav(x, out[u]) if(!vis[x]) {
        vis[x] = 1;
        mxlen[x] = mxlen[u]+1;
        dfs(x);
    }
}



int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, ori_k; cin >> n >> ori_k;
    ori_k--;
    vector<int> cnt(n);
    for(int i = 1; i < n; ++i) {
        for(int j = i; j < n; j += i) {
            cnt[j]++;
        }
    }
    vector<int> p(n);
    vector<ll> sm(n);
    vector<int> jmp(n);
    F0R(i, n) {
        p[i] = i+cnt[i];
        if(p[i] >= n) p[i] -= n;
        out[p[i]].push_back(i);
        sm[i] = p[i];
        jmp[i] = p[i];
        // cout << i << " --> " << p[i] << "\n";
    }

    F0R(i, n) if(!vis[i]) {
        int u = p[i], v = p[p[i]];
        while(u != v) {
            u = p[u];
            v = p[p[v]];
        }
        // cout << u << "\n";
        vector<int> cyc;
        cyc.push_back(u);
        vis[u] = 1;
        u = p[u];
        while(u != cyc[0]) {
            cyc.push_back(u);
            vis[u] = 1;
            u = p[u];
        }
        // cout << cyc.size() << "\n";
        trav(u, cyc) {
            mxlen[u] = cyc.size();
            dfs(u);
        }
    }
    F0R(i, n) {
        --mxlen[i];
    }
    vector<ll> actual(n, -1);
    F0R(i, n) if (mxlen[i] >= ori_k) {
        actual[i] = 0;
    }
    vector<int> dmp(n);
    iota(all(dmp), 0);
    FOR(k, 0, K-1) {
        F0R(i, n) if (actual[i]>=0) {
            if(ori_k>>k&1) {
                actual[i] += sm[dmp[i]];
                dmp[i] = jmp[dmp[i]];
            }
        }
        vector<int> prejmp(n);
        swap(prejmp, jmp);
        vector<ll> presm(n);
        swap(presm, sm);
        F0R(i, n) {
            jmp[i] = prejmp[prejmp[i]];
        }
        F0R(i, n) {
            sm[i] = presm[i] + presm[prejmp[i]]; 
        }
    }
    ll ans = inf;
    int nd = -1;
    F0R(i, n) {
        if((actual[i]>=0) && ans > i+actual[i]) {
            // cout << i << "\n";
            ans = i+actual[i];
            nd = i;
        }
    }
    if(nd==-1) {
        cout << -1 << "\n";
        return 0;
    }
    cout << nd << " ";
    nd = p[nd];
    while(ori_k--) {
        cout << nd << " ";
        nd = p[nd];
    }
    return 0;
}   
