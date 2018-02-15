// https://beta.atcoder.jp/contests/agc003/submissions/2071397

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

int a[MAX_N],b[MAX_N];

int main(){
  int N; cin >> N;
  rep(i,N) scanf("%d",a+i);
  copy(a,a+N,b);
  sort(b,b+N);
  int ans = 0;
  rep(i,N){
    int ind = int(lower_bound(b,b+N,a[i])-b);
    if(i%2==1 && ind%2==0) ans++;
  }
  cout << ans << endl;
  return 0;
}
