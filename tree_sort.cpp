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
const int MAX_N=100001;
 
vector<int> edge[MAX_N];
ll memo[MAX_N][2];
int depth[MAX_N];
 
int s=0;
 
void dfs(int x){//xを根として木の深さを探索
  depth[x]=s;
  s++;
  for(int i :edge[x]){
    if(depth[i]==-1)  dfs(i);
  }
  s--;
  return;
}
 
ll draw(int x,int y){ //xをy(0->白、1->黒)に塗る通り数
  if(memo[x][y]>0) return memo[x][y];
  ll res=1;
  
  for(int i :edge[x]){
    if(depth[x]<depth[i]){
      if(y) (res*=draw(i,0))%=mod;
      else  (res*=(draw(i,0)+draw(i,1)))%=mod;
    }
  }
  //cout << x << "," << y << "," << res << endl;
  return memo[x][y]=res;
}
 
int main(){
  int N;
  cin >> N ;
  rep(i,N-1){
    int a,b;
    scanf("%d%d",&a,&b);
    a--; b--;
    edge[a].pb(b);
    edge[b].pb(a);
  }
  fill(memo[0],memo[MAX_N-1],-1);
  fill(depth,depth+N,-1);
  dfs(0);
  printf("%lld\n",(draw(0,0)+draw(0,1))%mod);
  return 0;
}