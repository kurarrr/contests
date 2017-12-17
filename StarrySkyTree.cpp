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
const int MAX_T=100001;

struct SegTree{
  //StarrySkyTree
  //MAX_Nは2Nの長さ
  int N;
  vector<int> dat,add;
  //要素、区間に一様に足される値、要素数
  //add配列がないとraddがO(N)かかる
  explicit SegTree(int n){
    N=1;
    while(N<n) N*=2;
    dat.resize(2*N-1);
    add.resize(2*N-1);
    //fill 0
  }
  int rmax(int a,int b){
    return rmax(a,b,0,0,N);
  }
  int rmax(int a,int b,int k,int l,int r){
    //ノードkに対応する区間[l,r)を与える
    //query(a,b,0,0,n)で[a,b)のmaxを与える
    if(r<=a || b<=l) return 0;
    else if(a<=l && r<=b) return dat[k];
    else{
      int lc=rmax(a,b,2*k+1,l,(l+r)/2);
      int rc=rmax(a,b,2*k+2,(l+r)/2,r);
      return max(lc,rc)+add[k]; //RMQ
    }
  }
  void radd(int a,int b,int x){
    //[a,b)にxを加算
    return radd(a,b,x,0,0,N);
  }
  void radd(int a,int b,int x,int k,int l,int r){
    if(r<=a || b<=l){
      //nop
    }else if(a<=l && r<=b){
      add[k]+=x;
      dat[k]+=x;
    }else{
      radd(a,b,x,2*k+1,l,(l+r)/2);
      radd(a,b,x,2*k+2,(l+r)/2,r);
      dat[k]=add[k]+max(dat[2*k+1],dat[2*k+2]); //RMQ
      return;
    }
  }
};

SegTree SST(MAX_T);

int main(){
  int N;
  cin >> N ;
  int s[N],t[N],T=0;
  rep(i,N){
    cin >> s[i] >> t[i] ;
  }
  rep(i,N) SST.radd(s[i],t[i],1);
  int ans=INF;
  rep(i,N){
    SST.radd(s[i],t[i],-1);
    //cout << SST.rmax(0,T) << endl;
    ans=min(ans,SST.rmax(0,MAX_T));
    SST.radd(s[i],t[i],1);
  }
  cout << ans << endl;
  return 0;
}