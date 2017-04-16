//http://poj.org/problem?id=3617

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

int main(){
  int N;
  cin >> N ;
  char a[N];
  rep(i,N)  cin >> a[i] ;
  int first=0,last=N-1,cnt=0;
  string ans="";
  while(first<=last){
    bool left=true;
    for(int i=0;i<=last-first;i++){
      if(a[first+i]<a[last-i]){
        left=true; break;
      }else if(a[first+i]>a[last-i]){
        left=false; break;
      }
    }
    if(left) putchar(a[first++]);
    else putchar(a[last--]);
    if((++cnt)%80==0) printf("\n");
  }

  return 0;
}