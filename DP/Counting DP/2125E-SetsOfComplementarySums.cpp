// https://codeforces.com/blog/entry/144923?#comment-1296794
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <climits>
#include <unordered_map>
#include <queue>
#include <deque>
#include <math.h>
#include <limits.h>
#include <set>
#include <stack>
#include <map>
#define ll long long
#define double long double
using namespace std;
 
const ll N=1e6+10,M=5e5+10,MOD=998244353;
 
const double EPS=1e-12;
 
typedef pair<ll,ll> pii;
typedef pair<ll,pair<ll,ll> > piii;
typedef pair<ll,piii> piiii;
 
ll n,m;


void reset()
{
    
}
 
void solve()
{
    cin>>n>>m;
    if(n==1){ cout<<m; return; }
    vector<ll> dp(m+1,0);

    ll t=(n+1)*n/2-1;
    if(t>m) {cout<<0; return ;}

    t=m-t;
    dp[0]=1;
    for(ll i=2;i<=n;i++)
    {
        for(ll j=n-i+1;j<=t;j++)
        {
            dp[j]+=dp[j-(n-i+1)];
            dp[j]%=MOD;
        }
    }

    ll ans=0;
    for(ll i=0;i<=t;i++) ans+=(dp[i]*(t+1-i))%MOD,ans%=MOD;
    cout<<ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);


 
    ll t; cin>>t;
    while(t--)
    {
        solve();
        reset();
        cout<<'\n';
    }
     
     
    return 0;
}