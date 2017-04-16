//http://poj.org/problem?id=3069

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
 
#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
 
using namespace std;

typedef long long ll;
const int mod=1e9+7;
const int INF=1<<30;
int a[2002];//その座標以下の最大ポイント
void solve(int R,int N){
  int x[N];
  rep(i,N) cin >> x[i] ;
  sort(x,x+N);
  fill(a,a+2001,-1);
  rep(i,N){
    a[x[i]]=x[i];
  }
  int now=0;
  rep(i,2001){
    if(a[i]==-1)  a[i]=now;
    else  now=a[i];
  }
  int cnt=0;
  now=(-1)*INF;
  rep(i,N){
    if(now+R<x[i]){
      now=a[x[i]+R];
      cnt++;
    }
  }
  cout << cnt << endl;
  return ;
}

int main(){
  int N,R;
  while((cin >> R >> N) && (N!=-1)){
    solve(R,N);
  }
  return 0;
}