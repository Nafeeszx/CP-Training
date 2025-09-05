#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+5,T=20;

namespace IO{
	inline char nc(){
		static char buf[500001],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,500000,stdin),p1==p2)?EOF:*p1++;
	}
	char out[500001],*pout=out,*eout=out+500000;
	template<typename T> inline T read(){
		char ch=nc(); T sum=0; bool f=false;
		for(;ch<'0'||ch>'9';ch=nc()) if(ch=='-') f=1;
		while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
		return f?-sum:sum;
	}
}
#define read IO::read<int>

int L,R,len,root,mu[N],omega[N],prod[N],prm[N>>3],anc[N]; bitset<N> not_p;
vector<int> buc[N],E_in[T],E_to[T]; vector<pair<int,int>> E_btw[T];

int Find(int x){return (anc[x]==x)?x:(anc[x]=Find(anc[x]));}
void init(int n){
	mu[1]=prod[1]=1;
	for (int i=2;i<=n;i++){
		if (!not_p[i])  prm[++len]=i,mu[i]=-1,omega[i]=1,prod[i]=i;
		for (int j=1;j<=len;j++){
			int p=prm[j],x=i*p;
			if (x>n)  break;
			not_p.set(x);
			if (i%p)  mu[x]=-mu[i],prod[x]=prod[i]*p,omega[x]=omega[i]+1;
			else {prod[x]=prod[i],omega[x]=omega[i];break;}
		}
	}
}
void solve(){
	L=read(),R=read();
	auto exist_prime=[&](){
		for (int i=L;i<=R;i++){
			if (!not_p[i])  return root=i,true;
		}
		return false;
	};
	auto init_edges=[&](){
		for (int i=L;i<=R;i++)  buc[prod[i]].emplace_back(i);
		for (int i=1;i<=R;i++)if(!buc[i].empty()){
			E_in[omega[i]].emplace_back(i);
			E_to[omega[i]+1].emplace_back(i);
			for (int j=(i<<1);j<=R;j+=i){
				if (!buc[j].empty())  E_btw[omega[j]].emplace_back(i,j);
			}
		}
	};
	auto brute_force=[&](){
		auto omega_lcm=[&](int x,int y){return omega[x]+omega[y]-omega[__gcd(x,y)];};
		for (int x=L;x<=R;x++){
			for (int y=L;y<x;y++)  E_btw[omega_lcm(x,y)].emplace_back(x,y);
		}
	};
	auto kruskal=[&](){
		ll ans=0; iota(anc,anc+R+1,0);
		auto Merge=[&](int u,int v){
			int fu=Find(u),fv=Find(v);
			if (fu^fv)  return anc[fu]=fv,true;
			return false;
		};
		for (int x=1;x<T;x++){
			int cnt=0;
			for (int u:E_in[x])  cnt+=(buc[u].size()-1);
			for (int u:E_to[x])  cnt+=Merge(u,root);
			for (auto &[u,v]:E_btw[x])  cnt+=Merge(u,v);
			ans+=(ll)cnt*x;
		}
		printf("%lld\n",ans);
	};
	auto clear_all=[&](){
		for (int i=1;i<=R;i++)  buc[i].clear();
		for (int x=1;x<T;x++)  E_in[x].clear(),E_to[x].clear(),E_btw[x].clear();
	};
	if (exist_prime())  init_edges();
	else brute_force();
	kruskal(),clear_all();
}
int main(){
	int T=read(); init(N-5);
	while (T--)  solve();
	return 0;
}