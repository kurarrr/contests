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
const int MAX_N=50;
const ll LINF=100000000000000000;

struct bit{
  //binary indexed tree
  ll array[MAX_N+1][MAX_N+1];
  int n=0;
  explicit bit(int N){
    n=N;
    rep(j,N) rep(i,N) array[j][i]=0;
    return;
  }
  ll sqrsum(int lx,int rx,int ty,int by){
    //lx<=x<=rx,ty<=y<=byの領域の和を求める
    ll res=0;
    REP(j,ty,by+1) res+=(sum(rx,j)-sum(lx-1,j));
    return res;
  }

  ll sum(int i,int j){
    //j行めのi以下の和を求める
    ll res=0;
    while(i>0){
      res+=array[j][i];
      i -= i & -i;
    }
    return res;
  }
  void add(int i,int j,ll a){
    //j行i列の数にaを加える
    while(i<=n){
      array[j][i]+=a;
      i += i & -i;
    }
    return ;
  }
};

bit b(MAX_N);

int main(){
  int N; ll d;
  cin >> N ;
  rep(j,N) rep(i,N){
    scanf("%lld",&d);
    b.add(i+1,j+1,d);
  }
  int Q;
  cin >> Q ;
  rep(k,Q){
    int P;
    ll res=0;
    scanf("%d",&P);
    REP(w,1,min(N+1,P+1)){
      int h=min(P/w,N);
      if(h<1) continue;
      //cout << w << "," << h << endl;
      REP(j,1,N-h+2){
        REP(i,1,N-w+2){
          res=max(res,b.sqrsum(i,i+w-1,j,j+h-1));
          //cout << i << "," << i+w-1 << "," << j << "," << j+h-1 << ":" << res << endl;
        }
      }
    }
    cout << res << endl;
  }
  

  return 0;
}
