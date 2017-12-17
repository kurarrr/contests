#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<utility>
#include<memory>
#include<cmath>
 
#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;
 
typedef long long ll;
typedef pair<int,int> P;
const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const int MAX_N=13;
const ll LINF=100000000000000000;
vector<ll> fact;

ll D,L;

void init(ll N){
  fact.resize(N+1);
  fact[0]=1;
  rep(i,N)  fact[i+1]=((i+1)*fact[i])%mod;
}

ll pow(ll a,ll b){
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
  return pow(n,P-2);
}

ll comb_mod(ll n,ll k){
  //nまで埋めた階乗テーブルを渡す
  return (fact[n] * imod(fact[k]) % mod) * imod(fact[n-k]) % mod ;
  //nCk % mod を返す
}

ll calc(ll x,ll y,ll k){
  if(x*y<D+L) return 0;
  ll res= (comb_mod(x*y,D)*comb_mod(x*y-D,L))*k%mod;
  //cout << x << "," << y << ":" << res << endl;
  return res;
}

int main(){
  ll R,C,X,Y;
  cin >> R >> C >> X >> Y >> D >> L ;
  init(X*Y);
  if(D+L==X*Y){
    cout << ((R-X+1)*(C-Y+1)%mod)*comb_mod(X*Y,D)%mod << endl;
  }else{
    ll res=0;
    res+=calc(X,Y,1);
    res-=(calc(X-1,Y,2)+calc(X,Y-1,2));
    res+=(calc(X-1,Y-1,4)+calc(X-2,Y,1)+calc(X,Y-2,1));
    res-=(calc(X-1,Y-2,2)+calc(X-2,Y-1,2));
    res+=calc(X-2,Y-2,1);
    res*=((R-X+1)*(C-Y+1));
    while(res<0) res+=mod;
    res %= mod;
    cout << res << endl;
  }
  return 0;
}
