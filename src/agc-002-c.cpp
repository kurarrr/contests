// https://beta.atcoder.jp/contests/agc002/submissions/1995822
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 100005;

ll a[MAX_N];

int main(){
  ll N,L; cin >> N >> L;
  ll re = 0LL; int r = 0;
  rep(i,N) scanf("%lld",a+i);
  rep(i,N-1){
    ll t = a[i] + a[i+1];
    if(t>re){
      re = t;
      r = i;
    }
  }
  if(re<L) cout << "Impossible" << endl;
  else{
    cout << "Possible" << endl;
    REP(i,1,r+1) cout << i << endl;
    RREP(i,N-1,r+1) cout << i << endl;
  }
  return 0;
}
