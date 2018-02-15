// https://beta.atcoder.jp/contests/agc001/submissions/1991926
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
  ll N,X,ans;
  cin >> N >> X;
  ans = N;
  ll a = max(X,N-X);
  ll b = min(X,N-X);
  while(b!=0){
    if(a%b!=0LL) ans += 2*(a/b)*b;
    else ans += (2*(a/b)-1)*b;
    ll a1 = max(a%b,b);
    ll b1 = min(a%b,b);
    a = a1; b = b1;
  }
  cout << ans << endl;
  return 0;
}
