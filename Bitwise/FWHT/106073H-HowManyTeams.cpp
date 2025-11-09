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

vector<ll> or_conv(vector<ll> A, vector<ll> B) {
    int n = __lg(A.size());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if ((j >> i) & 1) {
                A[j] += A[j - (1 << i)];
                B[j] += B[j - (1 << i)];
            }
        }
    }
    vector<ll> C(1<<n);
    for (int i = 0; i < (1 << n); i++) {
        C[i] = A[i] * B[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = (1 << n) - 1; j >= 0; j--) {
            if ((j >> i) & 1) {
                C[j] -= C[j - (1 << i)];
            }
        }
    }

    return C;
}

void solve()
{
    int n, k; cin >> n >> k;
    vector<ll> a(1<<k);
    F0R(i, n) {
        string s; cin >> s;
        int cur=0;
        F0R(x, k) {
            if(s[x]=='1') cur |= (1<<x);
        }
        a[cur]++;
    }   
    auto db = or_conv(a, a);
    F0R(i, 1<<k) {
        db[i] -= a[i];
    }
    auto cb = or_conv(db, a);
    F0R(i, 1<<k) {
        cb[i] -= 2*db[i];
        cb[i] /= 6;
    }
    int q; cin >> q;
    while(q--) {
        string s; cin >> s;
        int cur=0;
        F0R(x, k) {
            if(s[x]=='1') cur |= (1<<x);
        }
        cout << cb[cur] << "\n";
    }
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1;// cin  >> t;
    while(t--) solve();
    return 0;
}   
