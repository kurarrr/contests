#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<deque>
#include<algorithm>
#include<utility>
#include<memory>
#include<cmath>
#include<stack>
#include<tuple>
#include<numeric>
#include<cassert>

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back
#define DEBUG false

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<int,ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60;
const int MAX_K = 100005;
const ll lmod = 1e9+7;

int K;

class Edge{
  public:
    ll cost;int to;
    Edge(ll cost,int to)
      :cost(cost),to(to){}
};
vector<Edge> e[MAX_K];
ll d1[MAX_K];

void dijkstra(int start,vector<Edge> graph[],ll d[]){
  priority_queue<Pl,vector<Pl>,greater<Pl>> que;
  fill(d,d+MAX_K,LINF);
  d[start] = 0LL;
  que.push(Pl(0LL,start));
  while(!que.empty()){
    P p=que.top(); que.pop();
    int v=p.second; //行き先
    if(d[v]<p.first)  continue;
    rep(i,graph[v].size()){
      edge e=graph[v][i];
      if(d[v]+e.cost<d[e.to]){
        d[e.to]=d[v]+e.cost;
        que.push(P(d[e.to],e.to));
      }
    }
  }
  return ;
}



int main(){
  cin >> K ;
  rep(i,K){
    e[i].pb(Edge(1LL,(i+1)%K));
  }
  REP(i,1,K){
    e[i].pb(Edge(0LL,(i*10)%K));
  }
  dijkstra(1,e,d1);
  cout << d1[0] + 1LL << endl;
  return 0;
}
