#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 41;

vector<int> graph[40];
bool ok1[1<<20],ok2[1<<20];
int ok3[1<<20],dp[1<<20];

int main() {
  int N,M; cin >> N >> M;
  rep(i,M){
    int a,b; cin >> a >> b;
    a--; b--; graph[a].pb(b); graph[b].pb(a);
  }
  int n1 = (N+1)/2; int n2 = N/2;
  fill(ok1,ok1+(1<<n1),true);
  rep(i,n1) for(auto u:graph[i]) if(u<n1) ok1[(1<<i)|(1<<u)] = false;
  rep(i,1<<n1) if(!ok1[i]) rep(j,n1) ok1[i|(1<<j)] = false;
  
  fill(ok2,ok2+(1<<n2),true);
  REP(i,n1,N) for(auto u:graph[i]) if(u>=n1) ok2[(1<<(i-n1))|(1<<(u-n1))] = false;
  rep(i,1<<n2) if(!ok2[i]) rep(j,n2) ok2[i|(1<<j)] = false;

  ok3[0] = (1<<n2) - 1;
  rep(i,n1){
    ok3[1<<i] = (1<<n2) - 1;
    for(auto u:graph[i]) if(u>=n1) ok3[1<<i] ^= (1<<(u-n1));
  }
  rep(i,1<<n1) rep(j,n1) ok3[i|(1<<j)] = ok3[i]&ok3[1<<j];

  rep(i,1<<n2){
    if(ok2[i]){
      int cnt = 0;
      rep(j,n2) if(i&(1<<j)) cnt++;
      dp[i] = cnt;
    }else{
      dp[i] = 0;
    }
  }
  rep(i,1<<n2) rep(j,n2) dp[i|(1<<j)] = max(dp[i|(1<<j)],dp[i]);

  int ans = 0;
  rep(i,1<<n1){
    if(!ok1[i]) continue;
    int cnt = 0;
    rep(j,n1) if(i&(1<<j)) cnt++;
    ans = max(ans,cnt + dp[ok3[i]]);
  }
  cout << ans << endl;
  return 0;
}