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
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 200005;

double R[1<<10],dp[1<<10][11];

double win(int p,int q){
  return 1.0/(1.0+pow(10.0,1.0*(R[q]-R[p])/400.0));
}

int main(){
  int K; cin >> K;
  rep(i,1<<K) scanf("%lf",R+i);
  rep(i,1<<K) dp[i][0] = 1.0;
  rep(i,1<<K) REP(j,1,K+1) dp[i][j] = 0.0;
  REP(j,1,K+1){
    rep(i,1<<K){
      int n = i^(1<<(j-1));
      n &= (~((1<<(j-1))-1));
      REP(k,n,n+(1<<(j-1))){
        dp[i][j] += dp[k][j-1] * win(i,k);
      }
      dp[i][j] *= dp[i][j-1];
    }
  }
  rep(i,1<<K) printf("%.10lf\n",dp[i][K]);
  return 0;
}