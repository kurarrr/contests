// https://beta.atcoder.jp/contests/ddcc2017-qual/submissions/2074545

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
const int MAX_N = 202;

string s[MAX_N];

int main(){
  int H,W,A,B; cin >> H >> W >> A >> B;
  rep(i,H) cin >> s[i];
  int ans = A + B;
  int cnt,cnthw,cnth,cntw;
  cnt = cntw = cnth = cnthw = 0;
  rep(i,H) rep(j,W) if(s[i][j]=='S') cnt++;
  rep(i,H/2) rep(j,W/2){
    if(s[i][j]=='S'&&s[H-1-i][j]=='S'&&s[i][W-1-j]=='S'&&s[H-1-i][W-1-j]=='S'){
      s[i][j] = s[H-1-i][j] = s[i][W-1-j] = s[H-1-i][W-1-j] = '.';
      cnthw++;
    }
  }
  rep(i,H){
    rep(j,W/2){
      if(s[i][j]=='S'&&s[i][W-1-j]=='S') cntw++;
    }
  }
  rep(i,H/2){
    rep(j,W){
      if(s[i][j]=='S'&&s[H-1-i][j]=='S') cnth++;
    }
  }
  if(cnthw>0){
    if(cnt>4*cnthw) ans += cnthw * (A+B+max(A,B));
    else ans += cnthw * (A+B+max(A,B)) - (A+B);
  }
  cnt -= 4*cnthw;
  int temp = 0;
  if(cnt>2*cnth) temp = max(temp,cnth*A);
  else temp = max(temp,(cnth-1)*A);
  if(cnt>2*cntw) temp = max(temp,cntw*B);
  else temp = max(temp,(cntw-1)*B);
  cout << ans + temp << endl;
  return 0;
}
