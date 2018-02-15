// https://beta.atcoder.jp/contests/arc061/submissions/2016609

#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;
using Pl = pair<int,ll>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;
const int MAX_N = 100005;

class Edge{
  public:
    int cost; ll to;
    Edge(int cost,ll to)
      :cost(cost),to(to){}
};

void dijkstra(ll start,unordered_map<ll,vector<Edge>> &graph,unordered_map<ll,int> &dist){
  priority_queue<Pl,vector<Pl>,greater<Pl>> que;
  dist[start] = 0;
  que.push(Pl(0,start));
  while(!que.empty()){
    Pl p=que.top(); que.pop();
    ll v=p.second; //行き先
    if(dist[v]==0&&v!=0LL) dist[v] = INF;
    if(dist[v]<p.first) continue;
    for(Edge e: graph[v]){
      if(dist[e.to]==0&&e.to!=0LL) dist[e.to] = INF;
      if(dist[v]+e.cost<dist[e.to]){
        dist[e.to]=dist[v]+e.cost;
        que.push(Pl(dist[e.to],e.to));
      }
    }
  }
  return ;
}

void add_edge(ll p,ll q,ll c,unordered_map<ll,vector<Edge>> &graph){
  ll p0,pc,q0,qc;
  p0 = ll(p); q0 = ll(q);
  pc = p0 | (c<<30);
  qc = q0 | (c<<30);
  graph[p0].pb(Edge(1,pc));
  graph[pc].pb(Edge(1,p0));
  graph[pc].pb(Edge(0,qc));
  graph[qc].pb(Edge(0,pc));
  graph[qc].pb(Edge(1,q0));
  graph[q0].pb(Edge(1,qc));
}

int main(){
  ll N,M; cin >> N >> M;
  unordered_map<ll,vector<Edge>> graph;
  unordered_map<ll,int> dist;
  rep(i,M){
    ll p,q,c; scanf("%lld%lld%lld",&p,&q,&c);
    p--; q--;
    add_edge(p,q,c,graph);
  }
  dijkstra(0LL,graph,dist);
  ll ans;
  if(dist[ll(N-1)]!=0 && dist[ll(N-1)]!=INF){
    ans = dist[ll(N-1)]/2LL;
  }else{
    ans = -1LL;
  }
  cout << ans << endl;
  return 0;
}
