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

int main() 
{          
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    int n; cin >> n;
    vector<ll> cnt(1<<17), A(1<<17);
    F0R(i, n) {
        int u; cin >> u;
        A[u]++;
        cnt[u]++;
    }
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < (1 << 17); j++) {
            if ((j >> i) & 1) {
                A[j] += A[j - (1 << i)];
            }
        }
    }
    vector<ll> C(1<<17);
    for (int i = 0; i < (1 << 17); i++) {
        C[i] = A[i] * 1LL * A[i];
    }
    for (int i = 17 - 1; i >= 0; i--) {
        for (int j = (1 << 17) - 1; j >= 0; j--) {
            if ((j >> i) & 1) {
                C[j] -= C[j - (1 << i)];
            }
        }
    }
    int best;
    ll cn;
    ROF(j, (1<<17)-1, 0) {
        if(C[j] - cnt[j]) {
            best = j;
            cn = (C[j] - cnt[j])>>1;
            break;
        }
    }
    cout << best << " " << cn << "\n";
    return 0;
}   
