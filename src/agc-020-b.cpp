// https://beta.atcoder.jp/contests/agc020/submissions/1976398
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
#define DEBUG false

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<int,ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60;
const int MAX_N = 100005;
const ll lmod = 1e9+7;

ll a[MAX_N],dp[MAX_N][2];

int main(){
  int K; cin >> K ;
  rep(i,K) scanf("%lld",a+K-1-i);
  bool possible = (a[0]==2LL);
  dp[0][0] = dp[0][1] = 2LL;
  a[K] = 1LL;
  rep(i,K){
    // min
    dp[i+1][0] = dp[i][0];
    // max
    dp[i+1][1] = (dp[i][1] + a[i] - 1LL);
    dp[i+1][0] = ((dp[i+1][0] + a[i+1] - 1LL) / a[i+1]) * a[i+1];
    dp[i+1][1] = (dp[i+1][1] / a[i+1] ) * a[i+1];
    // cout << dp[i+1][0] << ", " << dp[i+1][1] << endl;
    possible &= ((dp[i+1][0] > 0) && (dp[i+1][0] <= dp[i+1][1]));
    if(!possible){
      cout << "-1" << endl;
      return 0;
    }
  }
  cout << dp[K][0] << " " << dp[K][1] << endl;
  return 0;
}
