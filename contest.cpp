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

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 100005;

vector<ll> fact;

void init(ll N){
  fact.resize(N+1);
  fact[0]=1;
  rep(i,N)  fact[i+1]=((i+1)*fact[i])%mod;
}

ll ppow(ll a,ll b){
  // aのb乗を求める
  ll res = 1;
  while(b){
    if(b%2) res=(res*a)%mod;
    a=(a*a)%mod;
    b>>=1;
  }
  return res;
}

ll imod(ll n){
  // nのmodの逆元を求める
  ll P=mod;
  return ppow(n,P-2);
}

ll comb_mod(ll n,ll k){
  //nまで埋めた階乗テーブルを渡す
  return (fact[n] * imod(fact[k]) % mod) * imod(fact[n-k]) % mod ;
  //nCk % mod を返す
}

int main(){
  ll N,X,Y,Z; cin >> N >> X >> Y >> Z;
   
  return 0;
}