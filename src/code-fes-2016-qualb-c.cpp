// https://beta.atcoder.jp/contests/code-festival-2016-qualb/submissions/2013644

#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 100005;

ll p[MAX_N],q[MAX_N],psum[MAX_N];

int main(){
  int W,H; cin >> W >> H;
  rep(i,W) scanf("%lld",p+i);
  rep(i,H) scanf("%lld",q+i);
  sort(p,p+W);
  psum[0] = p[0];
  REP(i,1,W) psum[i] = psum[i-1] + p[i];
  ll ans = 0LL;
  ans += psum[W-1];
  rep(i,H){
    int ind = int(upper_bound(p,p+W,q[i]) - p);
    ans += q[i];
    if(ind!=0) ans += psum[ind-1] + q[i] * (W-ind);
    else ans += q[i] * W;
  }
  cout << ans << endl;
  return 0;
}
