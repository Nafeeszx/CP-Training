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

const ll mod = 1e9 + 7, MOD = 998244353, inf = 1001001001;

int giv[105][105];
ll dp[105][105];

bool chk(int j, int i) {
  bool ok = true;
  FOR(k, 1, i) {
    if(giv[k][i] == 0) continue;
    if(k >= j && giv[k][i] == 2) return false;
    if(k < j && giv[k][i] == 1) return false;
  } 
  return true;
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    F0R(i, n) {
      F0R(j, n-i) {
        int u; cin >> u;
        giv[i+1][i+j+1] = u;
      }
    }
    if(giv[1][1] != 2) dp[1][0] = 2; 
    FOR(i, 1, n-1) {
      F0R(j, i) {
        if(chk(j+1, i+1)) (dp[i+1][j] += dp[i][j]) %= MOD;
        if(chk(i+1, i+1)) (dp[i+1][i] += dp[i][j]) %= MOD;
      }
    }
    ll res = 0;
    F0R(i, n) {
      (res += dp[n][i]) %= MOD;
    }
    cout << res;
    return 0;
}   