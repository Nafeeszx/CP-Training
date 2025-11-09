// awesome solution, a simple necessary condition turns out to be sufficient
// construct answer by fixing two phases 0 degree, and 180 degree
// credit: https://contest.ucup.ac/submission/1634474

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return true; } return false; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return true; } return false; }
#define vi vector<int>
#define vl vector<ll>
#define vii vector<pair<int,int>>
#define vll vector<pair<ll,ll>>
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>
#define vvii vector<vector<pair<int,int>>>
#define vvll vector<vector<pair<ll,ll>>>
#define vst vector<string>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define mkunique(x) sort(all(x));(x).erase(unique(all(x)),(x).end())
#define fi first
#define se second
#define mp make_pair
#define si(x) int(x.size())
const int mod=998244353,MAX=300005;
const ll INF=15LL<<58;

int main(){
    
    std::ifstream in("text.txt");
    std::cin.rdbuf(in.rdbuf());
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    int Q=1;
    while(Q--){
        ll N,M,K;cin>>N>>M>>K;
        vll A(N),B(M);
        for(int i=0;i<N;i++){
            cin>>A[i].fi;
            A[i].se=i;
        }
        for(int i=0;i<M;i++){
            cin>>B[i].fi;
            B[i].se=i;
        }
        sort(all(A));
        sort(all(B));
        for(int i=1;i<N;i++) chmax(A[i].fi,A[i-1].fi+K+K);
        for(int i=1;i<M;i++) chmax(B[i].fi,B[i-1].fi+K+K);
        
        ll x=A.back().fi,y=B.back().fi;
        
        if(x>=y){
            if(x-y>=K){
                y=x-K;
            }else{
                x=y+K;
            }
        }else{
            if(y-x>=K){
                x=y-K;
            }else{
                y=x+K;
            }
        }
        
        for(int i=0;i<N;i++){
            ll a=A[i].fi%(2*K),b=x%(2*K);
            ll need=(b+2*K-a)%(2*K);
            A[i].fi+=need;
        }
        for(int i=0;i<M;i++){
            ll a=B[i].fi%(2*K),b=y%(2*K);
            if(a!=b){
                ll need=(b+2*K-a)%(2*K);
                B[i].fi+=need;
            }
        }
        
        cout<<max(x,y)+K<<"\n";
        int i=0,j=0;
        while(i<N||j<M){
            ll a,b;
            if(i<N) a=A[i].fi;
            else a=INF;
            if(j<M) b=B[j].fi;
            else b=INF;
            if(a<b){
                cout<<a<<" "<<0<<" "<<A[i].se+1<<"\n";
                i++;
            }else{
                cout<<b<<" "<<1<<" "<<B[j].se+1<<"\n";
                j++;
            }
        }
    }
    
}

