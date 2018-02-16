// https://beta.atcoder.jp/contests/arc058/submissions/2098604

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

int N,X[3],S,B;
ll dp[41][(1<<16)+1];

int encode(int u){
  if((u&B)==B) return (1<<(S-1));
  else return u&((1<<(S-1))-1);
}

int main(){
  cin >> N >> X[0] >> X[1] >> X[2];
  B = (1<<(X[0]+X[1]+X[2]-1))|(1<<(X[1]+X[2]-1))|(1<<(X[2]-1));
  S = X[0] + X[1] + X[2];
  dp[0][0] = 1LL;
  rep(i,N){
    rep(j,(1<<(S-1))){
      REP(k,1,11){
        (dp[i+1][encode((j<<k)|(1<<(k-1)))] += dp[i][j]) %= lmod;
      }
    }
    (dp[i+1][1<<(S-1)] += dp[i][1<<(S-1)] * 10LL) %= lmod;
  }
  cout << dp[N][(1<<(S-1))] << endl;
  return 0;
}
