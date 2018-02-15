// https://beta.atcoder.jp/contests/arc083/submissions/2014830
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

const int MAX_N = 302;

using PP = pair<ll,P>;

ll a[MAX_N][MAX_N],b[MAX_N][MAX_N];

int main(){
  int N;
  cin >> N;
  rep(i,N) rep(j,N) scanf("%lld",&a[i][j]);
  bool conf = true;
  rep(i,N) conf &= (a[i][i]==0LL);
  rep(i,N-1) REP(j,i+1,N) conf &= (a[i][j]==a[j][i]);
  if(!conf){
    cout << "-1" << endl;
    return 0;
  }
  rep(i,N) rep(j,N) b[i][j] = a[i][j];
  rep(i,N) rep(j,N) rep(k,N) b[i][j] = b[j][i] = min(b[i][j],b[i][k]+b[j][k]);
  ll ans = 0LL;
  rep(i,N-1) REP(j,i+1,N){
    if(b[i][j]!=a[i][j]){
      cout << "-1" << endl;
      return 0;
    }else{
      bool pls = true;
      rep(k,N){
        if(k==j||k==i) continue;
        // 迂回路が存在するか?
        pls &= (b[i][k]+b[k][j]!=b[i][j]);
      }
      if(pls) ans += b[i][j];
    }
  }
  cout << ans << endl;
  return 0;
}
