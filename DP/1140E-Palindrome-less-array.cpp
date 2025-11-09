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
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<vector<ll>> dp(2,vector<ll>(2));
    vector<int> a(n), nxt(n, -1);
    F0R(i, n) {
        cin >> a[i];
    }
    bool ok = true;
    ROF(i, n-1, 0) {
        if(i+2 < n) {
            if(a[i]!=-1&&a[i]==a[i+2]) ok = false;
            nxt[i] = nxt[i+2];
            if(a[i+2] != -1) nxt[i] = a[i+2];
        }
    }
    if(!ok) {
        cout << "0\n";
        return 0;
    }
    F0R(i, n) {
        if(i<=1) {
            if(a[i]==-1) {
                if(nxt[i] == -1) {
                    dp[i&1][0] = k;
                    dp[i&1][1] = 0;
                }
                else {
                    dp[i&1][0] = k-1;
                    dp[i&1][1] = 1;
                }
            }
            else {
                if(nxt[i]==-1) {
                    dp[i&1][0] = 1;
                }
                else {
                    if(a[i] != nxt[i]) dp[i&1][0] = 1;
                    else dp[i&1][1] = 1;
                }
            }
        }
        else {
            vector<ll> nw(2);
            if(a[i]==-1) {
                if(nxt[i] == -1) {
                    nw[0] = (k-1)*dp[i&1][0]%mod;
                    nw[1] = 0;
                }
                else {
                    nw[0] = ((k-1)*dp[i&1][1] + (k-2)*dp[i&1][0])%mod;
                    nw[1] = dp[i&1][0];
                }
            }
            else {
                if(nxt[i]==-1) {
                    nw[0] = dp[i&1][0];  
                }
                else {
                    if(a[i] != nxt[i]) nw[0] = dp[i&1][0];
                    else nw[1] = dp[i&1][0];
                }
            }
            dp[i&1] = nw;
        }
    }
    ll nx = (dp[0][0]+dp[0][1])*(dp[1][0]+dp[1][1])%mod;
    cout << nx << "\n";
    return 0;
}   
