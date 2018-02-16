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

void solve(){
  ll x,n,m,s; cin >> x;
  if(!x){
    cout << "1 1" << endl;
    return;
  }
  for(n = 1LL; n <= ll(1e5); n++){
    if(n*n-x<=0) continue;
    s = sqrt(n*n-x);
    if(s*s!=n*n-x) continue;
    m = n/s;
    if(s==n/m){
      cout << n << " " << m << endl;
      return ;
    }
  }
  cout << "-1" << endl;
}

int main(){
  int N; cin >> N;
  rep(i,N) solve();
  return 0;
}