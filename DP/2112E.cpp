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

const int N = 500005;

ll dp[N];

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    F0R(i, N) dp[i] = mod;
    dp[1] = 1;
    dp[3] = 2;
    FOR(i, 5, N-5) {
        for(int j = 1; j*j <= i; ++j) {
            if(i % j) continue;
            int x = i/j;
            if(x>2) dp[i] = min(dp[i], dp[i/x]+dp[x-2]);
            if(j>2) dp[i] = min(dp[i], dp[i/j]+dp[j-2]);
        }
    }
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        cout << (dp[n]==mod ? -1 : dp[n]) << "\n";
    }
    return 0;
}   
