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
const int mod=1e9+7;
const int INF=1<<30;

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

ll comb_mod(ll n,ll k,ll fact[]){
  //nまで埋めた階乗テーブルを渡す
  return (fact[n] * imod(fact[k]) % mod) * imod(fact[n-k]) % mod ;
  //nCk % mod を返す
}

int main(){
  int H,W,A,B;
  cin >> H >> W >> A >> B ;
  ll fact[H+W+1];
  fact[0]=1;
  rep(i,H+W)  fact[i+1]=((i+1)*fact[i])%mod;
  
  ll ans=0;
  for(ll x=0; x<W-B; x++){
    ans=(ans+(comb_mod(H-A+B-1+x,H-A-1,fact) * comb_mod(W+A-B-2-x,A-1,fact) % mod))%mod;
  }
  cout << ans << endl;

  return 0;
}