// https://beta.atcoder.jp/contests/arc067/submissions/2048741

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
const int MAX_N = 1003;

vector<ll> fact;

void init(ll N){
  fact.resize(N+1);
  fact[0]=1;
  rep(i,N)  fact[i+1]=((i+1)*fact[i])%lmod;
}

ll ppow(ll a,ll b){
  // aのb乗を求める
  ll res = 1;
  while(b){
    if(b%2) res=(res*a)%lmod;
    a=(a*a)%lmod;
    b>>=1;
  }
  return res;
}

ll imod(ll n){
  // nのmodの逆元を求める
  ll P=lmod;
  return ppow(n,P-2);
}

ll comb_mod(ll n,ll k){
  //nまで埋めた階乗テーブルを渡す
  return (fact[n] * imod(fact[k]) % lmod) * imod(fact[n-k]) % lmod ;
  //nCk % mod を返す
}

int N,a,b,c,d;
ll dp[MAX_N][MAX_N];

int main(){
  cin >> N >> a >> b >> c >> d;
  init(N+2);
  dp[0][0] = 1LL;
  REP(i,1,b-a+2){
    rep(j,N+1){
      dp[i][j] += dp[i-1][j];
      int e = a+i-1;
      for(int f=c; f<=d && e*f<=j;f++){
        dp[i][j] += dp[i-1][j-e*f]*fact[N-j+e*f]%lmod*imod(fact[f]*fact[N-j]%lmod*ppow(fact[e],f)%lmod);
        dp[i][j] %= lmod;
      }
    }
  }
  // rep(i,4){
  //   rep(j,10) cout << dp[i][j] << " ";
  //   cout << "" << endl;
  // }
  cout << dp[b-a+1][N] << endl;
  return 0;
}
