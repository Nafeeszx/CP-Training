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

const int mod = 1e9+7;

const int N = 4005, ALPHA = 12;
 
struct AC {
struct state {
  int to[ALPHA],depth,sLink,par,parLet,cnt,nxt[ALPHA],cost,tcost;
}states[N];
vector<int> suff_tree[N]; int tot_nodes;
void init() {
  for(int i = 0; i < N; i++) suff_tree[i].clear();
  tot_nodes = 1; 
}
int add_string(string &str, int p) {
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
  states[cur].cost += p;
  states[cur].tcost += p;
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
void dfs(int u) {
  for(int v : suff_tree[u]) {
    states[v].tcost += states[u].tcost;
    dfs(v); 
  }
}
}aho;


int dp[1<<ALPHA][N];
int par1[1<<ALPHA][N];
int par2[1<<ALPHA][N];
vector<int> adj[12];

int main() 
{          
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    int n; cin >> n;
    aho.init();
    F0R(i, n) {
        int x; string s; cin >> x >> s;
        int ss = s.size();
        F0R(i, 12) adj[i].clear();
        F0R(i, ss-1) {
            adj[s[i]-'a'].push_back(s[i+1]-'a');
            adj[s[i+1]-'a'].push_back(s[i]-'a');
        }
        int od=0;
        char odid;
        bool ok = true;
        F0R(i, 12) {
            sort(all(adj[i]));
            adj[i].erase(unique(all(adj[i])), adj[i].end());
            if(adj[i].empty()) continue;
            if(adj[i].size() > 2) {
                ok = false;
                break;
            }
            if(adj[i].size()==1) {
                od++;
                odid = i;
            }
        }
        ok &= (od == 2);
        if(!ok) continue;
        string res;
        auto dfs = [&] (auto dfs, int u, int p =-1) -> void {
            res += (u+'a');
            trav(v, adj[u]) if(v != p) dfs(dfs, v, u);
        };
        dfs(dfs, odid);
        // cout << res << "\n";
        aho.add_string(res, x);
        reverse(all(res));
        aho.add_string(res, x);
    }    
    aho.push_links();
    aho.dfs(1);
    int cc = aho.tot_nodes;
    // F0R(i, cc+1) cout << aho.states[i].tcost << " "; 

    assert(cc<N);
    F0R(i, 1<<ALPHA) F0R(j, cc+1) dp[i][j] = -mod;
    dp[0][1] = 0;

    F0R(i, (1<<ALPHA)-1) F0R(k, 12) if(~i>>k&1) F0R(j, cc+1) if(dp[i][j] >= 0) {
        int ns = aho.next_state(j, k);
        int val = aho.states[ns].tcost;
        if(dp[i|(1<<k)][ns] < dp[i][j]+val) {
            dp[i|(1<<k)][ns] = dp[i][j]+val;
            par1[i|(1<<k)][ns] = k;
            par2[i|(1<<k)][ns] = j;
        }
    }

    int ad = (1<<ALPHA)-1, pcc, valpc=-mod;
    F0R(j, cc+1) if(valpc < dp[ad][j]) {
        pcc = j;
        valpc = dp[ad][j];
    }
    // cout << valpc << "\n";
    string res;
    while(ad) {
        int k = par1[ad][pcc];
        int j = par2[ad][pcc];
        res += (k+'a');
        ad ^= 1<<k;
        pcc = j;
    }
    reverse(all(res));
    cout << res << "\n";
    return 0; 
}   
