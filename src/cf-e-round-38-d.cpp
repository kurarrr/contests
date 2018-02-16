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
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 200005;

template<typename T> T inf;
template<> constexpr int inf<int> = 1<<30;
template<> constexpr ll inf<ll> = 1LL<<60;

using Cost = ll;
using Node = int;
struct Edge{
  Cost cost; Node to;
  Edge(Cost cost,Node to)
    :cost(cost),to(to){}
};
using Graph = vector<vector<Edge>>;

vector<Cost> dijkstra
(Graph &graph, vector<Cost> cost)
{
  using Pcn = pair<Cost,Node>;
  priority_queue<Pcn,vector<Pcn>,greater<Pcn>> que;
  vector<Cost> dist(graph.size(),inf<Cost>);
  for(int i = 0;i < graph.size(); i++){
    dist[i] = cost[i];
    que.push(Pcn(cost[i],i));
  }
  while(!que.empty()){
    Pcn p = que.top(); que.pop();
    Node v = p.second;
    if(dist[v] < p.first)  continue;
    for(Edge e : graph[v]){
      if(dist[v]+e.cost < dist[e.to]){
        dist[e.to] = dist[v]+e.cost;
        que.push(Pcn(dist[e.to],e.to));
      }
    }
  }
  return dist;
}

int main(){
  int N,M; cin >> N >> M;
  Graph g(N);
  rep(i,M){
    int u,v; ll c; scanf("%d%d%lld",&u,&v,&c);
    u--; v--;
    g[u].pb(Edge(2LL*c,v)); g[v].pb(Edge(2LL*c,u));
  }
  vector<Cost> co(N);
  rep(i,N) scanf("%lld",&co[i]);
  auto dist = move(dijkstra(g,co));
  rep(i,N) cout << dist[i] << " ";
  cout << "" << endl;
  return 0;
}