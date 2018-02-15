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
const int MAX_N=1001;

int a[MAX_N][MAX_N];
int d[MAX_N][MAX_N];
priority_queue<pair<ll,P>> que;
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};

int main(){
  int H,W;
  cin >> H >> W ;
  rep(y,H) rep(x,W){
    ll temp;
    scanf("%lld",&temp);
    a[y][x]=temp;
    que.push({temp,{y,x}});
  }
  fill(d[0],d[MAX_N-1],1);
  while(!que.empty()){
    pair<ll,P> p=que.top();
    int y=p.second.first,x=p.second.second;
    ll cost=p.first;
    que.pop();
    //cout << y << "," << x << ":" << cost << endl;
    ll cnt=0;
    rep(i,4){
      if((y+dy[i]<0 || y+dy[i]>H-1)||(x+dx[i]<0 || x+dx[i]>W-1)) continue;
      if(a[y+dy[i]][x+dx[i]]>a[y][x]) d[y][x]=(d[y][x]+d[y+dy[i]][x+dx[i]])%mod;
    }
    //cout << y << "," << x << ":" << d[y][x] << endl;
  }
  ll sum=0;
  rep(y,H) rep(x,W) sum = (sum+d[y][x]) % mod;
  printf("%lld\n",sum);

  //printf("%f",double型)

  return 0;
}