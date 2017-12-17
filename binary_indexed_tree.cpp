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
const int mod=1e9+7;
const int INF=1<<30;
const int MAX_N=100000;

struct bit{
  //binary indexed tree
  ll ary[MAX_N+1];
  int n=0;
  void init(int N){
    n=N;
    rep(i,N)  ary[i]=0;
    return ;
  }
  ll sum(int i){//i以下の和を求める
    ll res=0;
    while(i>0){
      res+=ary[i];
      i -= i & -i;
    }
    return res;
  }
  void add(int i,ll a){//i番目の数にaを加える
    while(i<=n){
      ary[i]+=a;
      i += i & -i;
    }
    return ;
  }
};

bit b;

int main(){
  int N;
  cin >> N ;
  vector<P> v;
  rep(i,N){
    ll w,h;
    cin >> w >> h ;
    v.pb({w,h});
  }
  sort(ALL(v));
  
  return 0;
}