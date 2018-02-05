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
 
map<int,int> mp;
int N;
ll memo[1<<17];
 
ll calc(int S){
  if(memo[S]!=-1) return memo[S];
  memo[S]=0;
  rep(i,N){
    int comb=1<<i;
    if(!(comb&S)) continue;
    if((S&(~comb))&mp[comb]) continue; //辺がある場合
    memo[S]+=calc(S&(~comb));
  }
  return memo[S];
}
 
 
int main(){
  int M;
  cin >> N >> M ;
  fill(memo,memo+(1<<16),-1);
  int x,y;
  rep(i,M){
    cin >> x >> y ;
    x = 1 << (x-1);
    y = 1 << (y-1);
    if(EXIST(mp,x)) mp[x]=(mp[x]|y);
    else mp[x]=y;
  }
  memo[0]=1;
  cout << calc((1<<N)-1) << endl;
 
  return 0;
}