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


const int N = 85, ALPHA = 26;

int msk[N];
 
struct AC {
struct state {
  int to[ALPHA],depth,sLink,par,parLet,cnt,nxt[ALPHA];
}states[N];
vector<int> suff_tree[N]; int tot_nodes;
void init() {
  for(int i = 0; i < N; i++) suff_tree[i].clear();
  tot_nodes = 1; 
}
int add_string(string &str) {
  int cur = 1;
  for(int i = 0; i < str.size(); i++) {
    int c = str[i]-'a';
    if(!states[cur].to[c]) {
      states[cur].to[c] = ++tot_nodes;
      states[tot_nodes].par = cur;
      states[tot_nodes].depth=states[cur].depth+1;
      states[tot_nodes].parLet = c;
    }
    cur = states[cur].to[c];
  }
  return cur;
}
void push_links() {
  queue <int> qq;
  qq.push(1);
  while (!qq.empty()) {
    int node = qq.front();
    qq.pop();
    if (states[node].depth <= 1)
      states[node].sLink = 1;
    else {
      int cur = states[states[node].par].sLink;
      int parLet = states[node].parLet;
      while (cur > 1 and !states[cur].to[parLet]){
        cur = states[cur].sLink;
      }
      if (states[cur].to[parLet]) {
        cur = states[cur].to[parLet];
      }
      states[node].sLink = cur;
    }
    if(node!=1)
      suff_tree[states[node].sLink].push_back(node);
    for (int i = 0 ; i < ALPHA; i++) {
      if(states[node].to[i])
        qq.push(states[node].to[i]);
    }
  }
}
int next_state(int from, int c) {
  if(states[from].nxt[c])
    return states[from].nxt[c];
  int cur = from;
  while(cur>1&&!states[cur].to[c])
    cur=states[cur].sLink;
  if(states[cur].to[c]) cur = states[cur].to[c];
  return states[from].nxt[c] = cur;
}
void dfs(int u, int mk) {
    msk[u] = mk;
    for(int v : suff_tree[u]) {
        dfs(v, mk | msk[v]); 
    }
}
}aho;


struct mint {
  ll x; // typedef long long ll;
  mint(ll x=0):x((x%mod+mod)%mod){}
  mint operator-() const { return mint(-x);}
  mint& operator+=(const mint a) {
    if ((x += a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator-=(const mint a) {
    if ((x += mod-a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
  mint operator+(const mint a) const { return mint(*this) += a;}
  mint operator-(const mint a) const { return mint(*this) -= a;}
  mint operator*(const mint a) const { return mint(*this) *= a;}
  mint pow(ll t) const {
    if (!t) return 1;
    mint a = pow(t>>1);
    a *= a;
    if (t&1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const { return pow(mod-2);}
  mint& operator/=(const mint a) { return *this *= a.inv();}
  mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, const mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

mint dp[105][1<<8][N];

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, l; cin >> n >> l;
    aho.init();
    F0R(_, n) {
        string p; cin >> p;
        int x = aho.add_string(p);
        msk[x] |= (1<<_);
    }
    aho.push_links();
    aho.dfs(1, 0);
    int tots = aho.tot_nodes;
    dp[0][0][1] = 1;
    F0R(i, l) F0R(mk, 1<<n) {
        FOR(state, 1, tots) F0R(j, 26) {
            int ns = aho.next_state(state, j);
            int nmk = mk|msk[ns];
            dp[i+1][nmk][ns] += dp[i][mk][state];
        }
    }
    mint ans;
    FOR(i, 1, tots) {
        ans += dp[l][(1<<n)-1][i];
    }
    cout << ans << "\n";
    return 0;
}   
