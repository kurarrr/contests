#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define show_table(n, k, table) rep(i,n){ rep(j,k) cout << table[i][j] << " "; cout << endl;}

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
const int MAX_N = 200005;

ll dp[MAX_N][2],H[MAX_N];

int main(){
  int N; ll P; scanf("%d%lld",&N,&P);
  rep(i,N) scanf("%lld",H+i);
  dp[0][0] = LINF; dp[0][1] = 0;
  rep(i,N-1){
    dp[i+1][1] = min(min(dp[i][0],dp[i][1])+P,dp[i][1]+max(0LL,H[i+1]-H[i]));
    dp[i+1][0] = min(min(dp[i][0],dp[i][1])+P,dp[i][0]+max(0LL,H[i]-H[i+1]));
    // dp[i+1][1] = min(dp[i][1]+min(P,max(0LL,H[i+1]-H[i])),dp[i][0]+P);
    // dp[i+1][0] = min(min(dp[i][0],dp[i][1])+P,dp[i][0]+max(0LL,H[i]-H[i+1]));
  }
  show_table(N,2,dp);
  cout << min(dp[N-1][0],dp[N-1][1]) << endl;
  return 0;
}