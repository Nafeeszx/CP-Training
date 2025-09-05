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

const int N = 200005, K = 33;
int dp[N][K];

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<int> A(n);
    F0R(i, n) cin >> A[i];
    sort(all(A));
    vector<int> b(n);
    int cur = 0;
    F0R(i, n) {
        while(A[cur] <= A[i]/2) cur++;
        b[i] = cur;
    }

    F0R(i, N) dp[i][0] = i;
    F0R(j, K) dp[0][j] = 0;
    FOR(i, 1, n) FOR(j, 1, K-1) {
        dp[i][j] = min(dp[i-1][j]+1, dp[b[i-1]][j-1]);
    }
    F0R(j, K) {
        if(dp[n][j] <= k) {
            cout << j << " " << dp[n][j] << "\n";
            return 0;
        } 
    }
    return 0;
}   
