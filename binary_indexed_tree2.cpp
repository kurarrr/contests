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
const int MAX_N=1000003;
 
struct bit{//binary indexed tree 最大値を求める版
  ll array[MAX_N+1];
  int n=0;
  void init(int N){
    n=N;
    rep(i,N)  array[i]=0;
    return ;
  }
  ll maxim(int i){//i以下の値の最大値を求める
    ll res=0LL;
    while(i>0){
      res=max(res,array[i]);
      i -= i& -i;
    }
    return res;
  }
  void update(int i,ll a){//i番目の数を更新する
    while(i<=n){
      array[i]=max(array[i],a);
      i += i & -i;
    }
    return ;
  }
};
 
bit b;
 
int main(){
  b.init(MAX_N);
  int N;
  cin >> N ;
  vector<P> v,temp;
  rep(i,N){
    ll w,h;
    cin >> w >> h ;
    v.pb({w,-h});
  }
  sort(ALL(v));
  rep(i,N)  v[i].second=(-1)*v[i].second;;
  //rep(i,N)  cout << v[i].first << ":" << v[i].second << endl;
 
  rep(i,N){
    // if(i!=0 && v[i-1].first!=v[i].first){
    //   rep(j,temp.size())  b.update(temp[j].first,temp[j].second);
    // }
    ll val=b.maxim(v[i].second-1);
    b.update(v[i].second,val+1);
    //temp.pb({v[i].second,ans+1});
    
  }
  cout << b.maxim(100003) << endl;
  return 0;
}