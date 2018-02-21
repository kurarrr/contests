#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

template<class T> void chmax(T& a,const T& b){a=max(a,b);}
template<class T> void chmin(T& a,const T& b){a=min(a,b);}

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 2003;

ll dp[MAX_N][MAX_N];
vector<int> graph[MAX_N];
int part[MAX_N];

int main(){
  int N,K;
  cin >> N >> K;
  rep(i,N-1){
    int a,b; cin >> a >> b;
    graph[a].pb(b); graph[b].pb(a);
  }
  rep(i,N) rep(j,K+1) dp[i][j] = 0LL;
  rep(i,N) dp[i][0] = 1LL;
  fill(part,part+N,1);
  function<void(int,int)> dfs = [&](int u,int p){
    for(auto v:graph[u]){
      if(v==p) continue;
      dfs(v,u);
      part[u] += part[v];
      // 元々の部分木 -> part[u]-part[v]-1
      // 新しい部分木 -> part[v]
      vector<ll> table(part[u]+1,0);
      rep(j,part[u]-part[v]){
        rep(l,part[v]+1){
          (table[j+l] += dp[u][j] * dp[v][l]) %= lmod;
        }
      }
      rep(j,part[u]) dp[u][j] = table[j];
    }
    dp[u][part[u]] = 1LL;
    return ;
  };
  dfs(0,-1);
  cout << dp[0][K] << endl;
  // rep(i,N){ rep(j,K+1) cout << dp[i][j] << " "; cout << endl;}
  return 0;
}