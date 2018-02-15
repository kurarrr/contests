// https://beta.atcoder.jp/contests/agc015/submissions/1989567
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 100005;

int main(){
  string s; cin >> s;
  ll N = s.size();
  ll ans = 0;
  rep(i,N){
    if(s[i]=='U') ans += i;
    else ans += (N-i-1);
  }
  ans = N * (N-1) + ans;
  cout << ans << endl;
  return 0;
}

