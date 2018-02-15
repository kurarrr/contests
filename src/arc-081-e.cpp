// https://beta.atcoder.jp/contests/arc081/submissions/2097090
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


int main(){
  string s; cin >> s;
  int N = s.size();
  vvi c(N+1,vi(26));
  vi dp(N+2,0),temp(26,N);
  rrep(i,N-1){
    temp[int(s[i]-'a')] = i;
    c[i] = temp;
  }
  dp[N] = 1;
  rrep(i,N-1){
    int nex = INF;
    rep(j,26){
      nex = min(nex,dp[c[i][j]+1]);
    }
    dp[i] = nex + 1;
  }
  // cout << s << endl;
  // rep(i,N+2) cout << dp[i];
  // cout << "" << endl;
  string ans = "";
  int now = 0;
  rep(i,dp[0]){
    int j = 0;
    for(;j<26;j++) if(dp[c[now][j]+1]==dp[now]-1) break;
    ans += char('a'+j);
    now = c[now][j] + 1;
  }
  cout << ans << endl;
  return 0;
}
