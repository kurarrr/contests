// https://beta.atcoder.jp/contests/tdpc/submissions/2113886

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
const int MAX_N = 1000006;

int main(){
  using vl = vector<ll>;
  using vvl = vector<vl>;
  int N; ll K; string s; cin >> s >> K;
  N = s.size();
  vvl dp(N+1,vl(26,0));
  rrep(i,N-1){
    rep(j,26){
      if(j==int(s[i]-'a')){
        rep(k,26) dp[i][j] = min(dp[i][j] + dp[i+1][k],K+1);
        dp[i][j] = min(dp[i][j]+1,K+1);
      }else{
        dp[i][j] = dp[i+1][j];
      }
    }
  }
  // rep(i,N){
  //   rep(j,26) printf("%3lld ",dp[i][j]);
  //   cout << "" << endl;
  // }
  int i = 0;
  while(true){
    // cout << i << " " << ans << endl ;
    if(K==0){
      cout << endl;
      return 0;
    }
    bool update = false;
    rep(j,26){
      if(K<=dp[i][j]){
        cout << char('a'+j);
        while(s[i]!=char('a'+j)) i++;
        i++;
        K--;
        update = true;
        break;
      }else{
        K -= dp[i][j];
      }
    }
    if(update) continue;
    if(K>=0){
      cout << "Eel" << endl;
      return 0;
    }
  }
  return 0;
}