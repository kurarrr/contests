// https://beta.atcoder.jp/contests/yahoo-procon2018-qual/submissions/2083392

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

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 33;

ll dp[20][(1<<18)];
ll x[20],c[20],v[20],s[20],cost[(1<<18)],val[(1<<18)];
int N;

inline bool contain(int bit,int i){
  return (bit>>i)&1;
}

int main(){
  cin >> N;
  Pl vc[20];
  rep(i,N) cin >> x[i];
  rep(i,N) cin >> c[i];
  rep(i,N) cin >> v[i];
  s[0] = 0LL;
  rep(i,N) s[i+1] = s[i] + x[i];
  rep(i,N) rep(j,1<<N) dp[i][j] = 0LL;
  fill(cost,cost+(1<<18),0LL);
  fill(val,val+(1<<18),0LL);
  
  rep(j,1<<N){
    rep(k,N) if(contain(j,k)) cost[j] += c[k], val[j] += v[k];
  }
  rep(i,N){
    rep(j,1<<N) if(cost[j]<=s[i]) dp[i][j] = max(dp[i][j],val[j]);
  }

  rep(i,N){
    rep(j,1<<N){
      if(__builtin_popcount(j)>N-i) continue;
      rep(k,N) if(contain(j,k)) dp[i][j] = max(dp[i][j],dp[i][j^(1<<k)]);
    }
  }

  map<P,ll> memo;
  function<ll(int,int)> solve = [&](int a,int b){
    if(memo.count(P(a,b))) return memo[P(a,b)];
    if(a==N) return 0LL;
    ll res = dp[a][b];
    ll temp = LINF;
    rep(i,N) if(contain(b,i)) temp = min(temp,solve(a+1,b^(1<<i)));
    return memo[P(a,b)] = max(res,temp);
  };
  cout << solve(0,(1<<N)-1) << endl;
  return 0;
}
