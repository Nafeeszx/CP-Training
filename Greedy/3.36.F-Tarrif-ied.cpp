// https://qoj.ac/submission/1046528
//https://gemini.google.com/u/1/app/694e9bcc1ad87421

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define ll long long
#define ull unsigned long long
#define int long long
#define SZ(x) ((int)((x).size()))
#define ALL(x) (x).begin(),(x).end()
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	for(;!isdigit(c);c=getchar())f^=!(c^45);
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return f?-x:x;
}

#define mod 998244353
struct modint{
	unsigned int x;
	modint(int o=0){x=o;}
	modint &operator = (int o){return x=o,*this;}
	modint &operator +=(modint o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
	modint &operator -=(modint o){return x=x<o.x?x-o.x+mod:x-o.x,*this;}
	modint &operator *=(modint o){return x=1ll*x*o.x%mod,*this;}
	modint &operator ^=(int b){
		modint a=*this,c=1;
		for(;b;b>>=1,a*=a)if(b&1)c*=a;
		return x=c.x,*this;
	}
	modint &operator /=(modint o){return *this *=o^=mod-2;}
	friend modint operator +(modint a,modint b){return a+=b;}
	friend modint operator -(modint a,modint b){return a-=b;}
	friend modint operator *(modint a,modint b){return a*=b;}
	friend modint operator /(modint a,modint b){return a/=b;}
	friend modint operator ^(modint a,int b){return a^=b;}
	friend bool operator ==(modint a,modint b){return a.x==b.x;}
	friend bool operator !=(modint a,modint b){return a.x!=b.x;}
	bool operator ! () {return !x;}
	modint operator - () {return x?mod-x:0;}
	bool operator <(const modint&b)const{return x<b.x;}
};
inline modint qpow(modint x,int y){return x^y;}

vector<modint> fac,ifac,iv;
inline void initC(int n)
{
	if(iv.empty())fac=ifac=iv=vector<modint>(2,1);
	int m=iv.size(); ++n;
	if(m>=n)return;
	iv.resize(n),fac.resize(n),ifac.resize(n);
	For(i,m,n-1){
		iv[i]=iv[mod%i]*(mod-mod/i);
		fac[i]=fac[i-1]*i,ifac[i]=ifac[i-1]*iv[i];
	}
}
inline modint C(int n,int m){
	if(m<0||n<m)return 0;
	return initC(n),fac[n]*ifac[m]*ifac[n-m];
}
inline modint sign(int n){return (n&1)?(mod-1):(1);}

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 1000005
#define inf 0x3f3f3f3f

typedef long double db;
int n,k,t[maxn],id[maxn];
db a[maxn],tmp[maxn];

void work(int O)
{
	n=read(),k=read();
	For(i,1,n) id[i]=i,t[i]=0,tmp[i]=1e18;
	
	For(i,1,n)a[i]=read(),a[i]=1.0*a[i]/100.0;
	db l=0,r=1;
	For(_,1,50){
		db mid=(l+r)/2;
		int cnt=0;
	//	cout<<"mid "<<mid<<endl;
		For(i,1,n){
	//		cout<<"a[i] "<<a[i]<<endl;
			if(mid<a[i]){
				db w=1.0l/mid-1.0l/a[i];
				cnt+=floor(w);
	//			cout<<"i: "<<i<<" "<<t[i]<<endl;
			}
		}
		if(cnt>=k)l=mid;
		else r=mid;
	}
	int cnt=0;
//	cout<<"mid "<<l<<endl;
	For(i,1,n){
		t[i]=0;
		if(l<a[i]){
			db w=1.0l/l-1.0l/a[i];
			t[i]=floor(w);
		}
		cnt+=t[i];
	//	cout<<"i: "<<i<<" "<<t[i]<<endl;
	}
	
	assert(cnt>=k);
	cnt-=k;
	assert(cnt<=n);

	For(i,1,n)id[i]=i;
	For(i,1,n){
		if(t[i]){
			db t1=1.0+a[i]*(t[i]-1);
			db t2=1.0+a[i]*t[i];
			tmp[i]=t2/t1;
		}
	}
	sort(id+1,id+n+1,[&](int u,int v){
		return tmp[u]<tmp[v];
	});
	For(i,1,cnt) --t[id[i]];
	
	db res=1;
	For(i,1,n)res*=(1.0l+a[i]*t[i]);
	printf("%.12Lf\n",res);
	//cout<<res<<"\n";
}

signed main()
{
//	freopen("in.in","r",stdin);
//	freopen("my.out","w",stdout);
	int T=read();
	For(_,1,T)work(_);
	return 0;
}
/*
*/