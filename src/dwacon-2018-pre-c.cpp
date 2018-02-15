// https://beta.atcoder.jp/contests/dwacon2018-prelims/submissions/1995148

#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 102, MAX_SUM = 1003;

ll part_dp[MAX_SUM][MAX_N],dp[MAX_N][MAX_SUM];

void prepare(){
  REP(i,1,MAX_SUM) part_dp[i][1] = 1LL;
  rep(i,MAX_N) part_dp[0][i] = 1LL;
  REP(i,1,MAX_SUM) REP(j,2,MAX_N){
    if(j>i) part_dp[i][j] = part_dp[i][i];
    else part_dp[i][j] = (part_dp[i-j][j] + part_dp[i][j-1]) % lmod;
  }
}

ll solve(vector<int> &kill,int death){
  int depth[MAX_N];
  fill(depth,depth+MAX_N,0);
  int prev = kill[0], N = kill.size(), cnt = 0;
  depth[cnt]++;
  if(N>1){
    REP(i,1,N){
      if(kill[i]==prev) depth[cnt]++;
      else{
        prev = kill[i];
        cnt++;
        depth[cnt]++;
      }
    }
  }
  cnt++;
  fill(dp[0],dp[MAX_N-1],0LL);
  dp[0][0] = 1LL;
  REP(j,1,cnt+1) REP(i,0,death+1){
    rep(k,i+1) (dp[j][i] += dp[j-1][i-k] * part_dp[k][depth[j-1]]) %= lmod;
    // cout << j << "," << i << " " << dp[j][i] << endl;
  }
  // cout << dp[cnt][death] << endl;
  return dp[cnt][death];
}

int main(){
  vector<int> a,b;
  int N,M; cin >> N >> M;
  int a_sum = 0,b_sum = 0;
  rep(i,N){
    int k; scanf("%d",&k);
    a.pb(k);
    a_sum += k;
  }
  rep(i,M){
    int k; scanf("%d",&k);
    b.pb(k);
    b_sum += k;
  }
  prepare();
  cout << solve(a,b_sum) * solve(b,a_sum) % lmod << endl;
  return 0;
}
