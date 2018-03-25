#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define show_table(n, k, table) rep(i,n){ rep(j,k) cout << table[i][j] << " "; cout << endl;}

using namespace std;

template<class T> inline void chmax(T& a,T const& b){a=max(a,b);}
template<class T> inline void chmin(T& a,T const& b){a=min(a,b);}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 100005;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N; cin >> N;
  vvi graph(N);
  REP(i,1,N){
    int p; cin >> p; p--; graph[i].pb(p); graph[p].pb(i);
  }
  vi x(N),a(N);
  rep(i,N) cin >> x[i];
  bitset<5003> dp;
  function<bool(int,int)> solve = [&](int u,int p){
    for(auto v:graph[u]){
      if(v==p) continue;
      if(!solve(v,u)) return false;
    }
    dp.reset();
    dp[0] = 1;
    int ss = 0;
    for(auto v:graph[u]){
      if(v==p) continue;
      dp = (dp << x[v])|(dp << a[v]);
      ss += x[v] + a[v];
    }
    rrep(j,x[u]){
      if(dp[j]){
        a[u] = ss - j;
        // cout <<" u:" << u+1 << " a:"<< a[u] << " ss:" << ss << endl;
        return true;
      }
    }
    return false;
  };
  cout << (solve(0,-1) ? "POSSIBLE" : "IMPOSSIBLE") << endl;
  return 0;
}
