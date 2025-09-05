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

const int N = 200005;
int dp[N][2][2];

int main() 
{          
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    int n; cin >> n;
    vector<string> s(2);
    F0R(i, 2) cin >> s[i];
    F0R(i, n) F0R(j, 2) F0R(f, 2) dp[i][j][f] = -mod;

    // dp[*][j][f] = j-th row te drop kore j^f-th row theke leave nicchi
    dp[0][0][0] = 0;
    if(s[1][0]=='1') dp[0][0][1] = 1;
    F0R(i, n-1) F0R(j, 2) {
        int x0 = (s[j][i+1]=='1'), x1 = (s[j^1][i+1]=='1');
        
        // j te land kore j^1 theke leave nicchi means s[i+1][j] must have no dirt
        dp[i+1][j^1][0] = max(dp[i+1][j^1][0], dp[i][j][1]+x1); 

        // j->j path e leave nicchi means i can for any route in (i+1)
        if(x1) {
            dp[i+1][j][1] = max(dp[i+1][j][1], dp[i][j][0]+x1+x0);
        }
        dp[i+1][j][0] = max(dp[i+1][j][0], dp[i][j][0]+x0);
    }
    int ans = 0;
    F0R(j, 2) F0R(f, 2) ans = max(ans, dp[n-1][j][f]);
    cout << ans << "\n";
    return 0; 
}   
