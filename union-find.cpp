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
#define INF 1<<25
#define pb push_back
 
typedef long long ll;
 
using namespace std;

void init(int par[],int rank[],int N){
  rep(i,N){
    par[i]=i;
    rank[i]=0;
  }
  return ;
}

int find(int par[],int x){
  if(par[x]==x) return x;
  else return par[x]=find(par,par[x]);
}

void unite(int par[],int rank[],int x,int y){
  x=find(par,x);
  y=find(par,y);
  if(x==y)  return ;
  if(rank[x]<rank[y]){
    par[x]=y;
  }else{
    par[y]=x;
    if(rank[x]==rank[y])  ++rank[x];
  }
  return ;
}

bool same(int par[],int x,int y){
  if(par[x]==par[y])  return true;
  else  return false;
}

int main(){
  int N,K,L;
  cin >> N >> K >> L ;
  int p[K+1],q[K+1],r[L+1],s[L+1];
  int par1[N+1],rank1[N+1],par2[N+1],rank2[N+1];
  init(par1,rank1,N);
  init(par2,rank2,N);
  int a,b;
  rep(i,K){
    cin >> a >> b ;
    unite(par1,rank1,a-1,b-1);
  }
  rep(i,L){
    cin >> a >> b ;
    unite(par2,rank2,a-1,b-1);
  }
  map<pair<int,int>,int> mp;
  rep(i,N){
    a=find(par1,i);
    b=find(par2,i);
    if(mp.find({a,b})!=mp.end()){
      mp[{a,b}]++;
    }else{
      mp[{a,b}]=1;
    }
  }
  rep(i,N)  cout << mp[{find(par1,i),find(par2,i)}] << " ";
  cout << endl;
  return 0;
}