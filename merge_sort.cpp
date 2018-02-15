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
const int MAX_T=2000;
const ll LINF=100000000000000000;

int cnt=0;

void merge_(int ary[], int p, int q, int r){
  //ソート済みのary[p..q-1],ary[q..r-1]を結合する
  int x[q-p+1],y[r-q+1];
  rep(i,q-p) x[i]=ary[p+i];
  rep(i,r-q) y[i]=ary[q+i];
  x[q-p]=y[r-q]=INF;
  int li=0,ri=0;
  rep(i,r-p){
    if(x[li]<=y[ri]){
      ary[p+i]=x[li++];
    }else{
      ary[p+i]=y[ri++];
      cnt+=(q-p-li); //反転数をカウント
    }
  }
}

void merge_sort(int ary[], int p, int r){
  if(abs(r-p)>1){
    int q=(p+r)/2;
    merge_sort(ary,p,q);
    merge_sort(ary,q,r);
    merge_(ary,p,q,r);
  }
}

int main(){
  int a[10]={9,8,7,6,5,4,3,2,1,0};
  merge_sort(a,0,10);
  rep(i,10) cout << a[i] << ",";
  cout << endl << cnt << endl;
  return 0;
}
