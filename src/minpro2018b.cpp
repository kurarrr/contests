// https://beta.atcoder.jp/contests/yahoo-procon2018-qual/submissions/2081167
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
const int MAX_N = 33;

int main(){
  ll X, K;
  cin >> X >> K;
  ll a = 1LL;
  rep(i,K) a *= 10LL;
  if(X%(a)==0) cout << X+a << endl;
  else cout << (X/a+1LL)*a << endl;
  return 0;
}
