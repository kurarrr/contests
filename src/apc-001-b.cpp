// https://beta.atcoder.jp/contests/apc001/submissions/2063627

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
const int MAX_N = 200005;

ll a[MAX_N],b[MAX_N];

int main(){
  int N; cin >> N;
  rep(i,N) scanf("%lld",a+i);
  rep(i,N) scanf("%lld",b+i);
  ll pls,mns; pls = mns = 0LL;
  rep(i,N){
    if(a[i]>b[i]) pls += a[i] - b[i];
    else mns += (b[i] - a[i]) /2; 
  }
  if(pls<=mns) cout << "Yes" << endl;
  else cout << "No" << endl;
  return 0;
}
