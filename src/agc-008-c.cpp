// https://beta.atcoder.jp/contests/agc008/submissions/2071536

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
const int MAX_N = 100005;

int main(){
  ll i,o,t,j,l,s,z;
  cin >> i >> o >> t >> j >> l >> s >> z;
  ll ans = o + (i/2)*2 + (l/2)*2 + (j/2)*2;
  if(i>0&&l>0&&j>0) ans = max(ans,o+3+(i-1)/2*2+(l-1)/2*2+(j-1)/2*2);
  cout << ans << endl;
  return 0;
}
