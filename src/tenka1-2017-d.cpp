// https://beta.atcoder.jp/contests/tenka1-2017/submissions/2015031
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

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 100005;
int a[MAX_N];
ll b[MAX_N];

int main(){
  int N,K; cin >> N >> K;
  rep(i,N) scanf("%d%lld",a+i,b+i);
  ll ans = 0LL ,temp = 0LL;
  rep(i,N) if((a[i]|K)==K) ans += b[i];
  rep(i,30){
    if((K&(1<<i))==0) continue;
    int t = (K ^ (1<<i))|((1<<i)-1);
    temp = 0LL;
    rep(i,N) if((a[i]|t)==t) temp += b[i];
    ans = max(ans,temp);
  }
  cout << ans << endl;
  return 0;
}
