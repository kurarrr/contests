// https://beta.atcoder.jp/contests/code-thanks-festival-2017-open/submissions/2073621
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

ll dp[2][MAX_N*2];
int a[MAX_N];

int main(){
  int N,K; cin >> N >> K;
  rep(i,N) scanf("%d",a+i);
  sort(a,a+N);
  dp[0][0] = 1LL;
  int now = 1,prev = 0;
  rep(i,N){
    ll k = 1; while(k<=a[i]) k <<= 1;
    rep(j,k) dp[now][j] = 0;
    rep(j,k){
      (dp[now][j] += dp[prev][j]) %= lmod;
      (dp[now][j^a[i]] += dp[prev][j]) %= lmod;
      // cout << (j^a[i]) << "," << dp[i+1][j^a[i]] << endl;
    }
    swap(now,prev);
  }
  cout << dp[prev][K] << endl;
  return 0;
}
