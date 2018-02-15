// https://beta.atcoder.jp/contests/cf17-final-open/submissions/2014064
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

const int MAX_N = 52;

int main(){
  int N,a[MAX_N];
  cin >> N;
  rep(i,N) cin >> a[i];
  if(N>=25){
    cout << "0" << endl;
    return 0;
  }
  int b[MAX_N];
  fill(b,b+13,0);
  if(N>=19&&N<=24){
    b[0]++;
    rep(i,N) b[a[i]]++;
    int _max = -INF;
    rep(i,13) _max = max(_max,b[i]);
    if(_max>=3||b[0]>=2) cout << "0" << endl;
    else cout << "1" << endl;
    return 0;
  }
  int ans = -INF;
  rep(i,1<<N){
    int ind = 0;
    b[ind++] = 0;
    rep(j,N){
      if(((1<<j)&i)!=0) b[ind++] = 24-a[j];
      else b[ind++] = a[j];
    }
    sort(b,b+N+1);
    int diff = 24 - b[N];
    rep(j,N) diff = min(diff,b[j+1]-b[j]);
    ans = max(ans,diff);
  }
  cout << ans << endl;
  return 0;
}
