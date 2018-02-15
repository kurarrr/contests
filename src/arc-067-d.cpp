// https://beta.atcoder.jp/contests/arc067/submissions/2014228
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

ll X[MAX_N];

int main(){
  int N; ll A,B;
  cin >> N >> A >> B;
  rep(i,N) scanf("%lld",X+i);
  ll ans = 0LL;
  rep(i,N-1){
    ans += min(A*(X[i+1]-X[i]),B);
  }
  cout << ans << endl;
  return 0;
}
