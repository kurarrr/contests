// https://beta.atcoder.jp/contests/arc085/submissions/2014894
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

const int MAX_N = 2003;
int a[MAX_N],dp[MAX_N];

int main(){
  int N,Z,W; cin >> N >> Z >> W;
  rep(i,N) scanf("%d",a+i);
  if(N!=1) cout << max(abs(a[N-1]-W),abs(a[N-1]-a[N-2])) << endl;
  else cout << abs(a[0]-W) << endl;
  return 0;
}
