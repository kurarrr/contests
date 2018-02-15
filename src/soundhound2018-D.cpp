// https://beta.atcoder.jp/contests/soundhound2018/submissions/2076231

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
const int MAX_N = 50004;

using vl = vector<ll>;
using vll = vector<vl>;

int W,H;

vl update(const vl& dp,const vl& p,const vl& f){
  vl res(W,0LL),a(W,0LL),b(W,0LL);
  // a[i] := [0,i) で得られる利益
  rep(i,W-1) a[i+1] = max(a[i]+p[i]-2*f[i],p[i]-f[i]);
  // b[i] := (i,W-1] で得られる利益
  RREP(i,W-1,1) b[i-1] = max(b[i]+p[i]-2*f[i],p[i]-f[i]);
  
  ll ma = -LINF;
  rep(i,W){
    ma = max(ma+p[i]-f[i],dp[i]+p[i]-f[i]+max(a[i]-f[i],0LL));
    res[i] = ma + max(b[i]-f[i],0LL);
  }
  // res[0] = dp[0] + p[0] - f[0] + max(b[0]-f[0],0LL);
  // REP(i,0,W-1){
  //   res[i+1] = max(dp[i+1]+p[i+1]-f[i+1]+max(a[i+1]-f[i+1],0LL),
  //               res[i]+p[i+1]-f[i+1]-max(b[i]-f[i],0LL))
  //               + max(b[i+1]-f[i+1],0LL);
  // }
  return res;
}

int main(){
  scanf("%d%d",&H,&W);
  vll dp(H+1,vl(W)),p(H,vl(W)),f(H,vl(W));
  rep(i,H) rep(j,W) scanf("%lld",&p[i][j]);
  rep(i,H) rep(j,W) scanf("%lld",&f[i][j]);
  REP(j,1,W) dp[0][j] = -LINF;
  dp[0][0] = 0LL;
  rep(i,H){
    auto d1 = move(update(dp[i],p[i],f[i]));
    reverse(ALL(dp[i]));
    reverse(ALL(p[i]));
    reverse(ALL(f[i]));
    auto d2 = move(update(dp[i],p[i],f[i]));
    reverse(ALL(d2));
    rep(j,W) dp[i+1][j] = -LINF;
    rep(j,W) dp[i+1][j] = max(d1[j],d2[j]);
  }
  rep(j,W) cout << dp[H][j] << endl;
  return 0;
}
