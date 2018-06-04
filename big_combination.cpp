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
  if(k>n) return 0LL;
  else return (fact[n] * imod(fact[k]) % mod) * imod(fact[n-k]) % mod ;
  //nCk % mod を返す
}

int main(){
  return 0;
}
