// https://beta.atcoder.jp/contests/arc064/submissions/2047607
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
using Pl = pair<ll,int>;

template<typename T> T inf;
template<> constexpr int inf<int> = 1<<30;
template<> constexpr ll inf<ll> = 1LL<<60;
template<> constexpr double inf<double> = 1e30;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 1003;

using Cost = double;
using Node = int;
struct Edge{
  Cost cost; Node to;
  Edge(Cost cost,Node to)
    :cost(cost),to(to){}
};
using Graph = vector<vector<Edge>>;

vector<Cost> dijkstra
(Graph &graph, Node start, Cost zero = 0LL)
{
  using Pcn = pair<Cost,Node>;
  priority_queue<Pcn,vector<Pcn>,greater<Pcn>> que;
  vector<Cost> dist(graph.size(),inf<Cost>);
  dist[start] = zero;
  que.push(Pcn(zero,start));
  while(!que.empty()){
    Pcn p = que.top(); que.pop();
    Node v = p.second; //行き先
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

Graph graph;

double x[MAX_N],y[MAX_N],r[MAX_N];

int main(){
  double x1,y1,x2,y2;
  cin >> x1 >> y1 >> x2 >> y2;
  int N; cin >> N;
  x[0] = x1; y[0] = y1; r[0] = 0;
  x[N+1] = x2; y[N+1] = y2; r[N+1] = 0;
  rep(i,N){
    scanf("%lf%lf%lf",x+i+1,y+i+1,r+i+1);
  }
  graph.resize(N+2);
  rep(i,N+1) REP(j,i+1,N+2){
    double c = max(0.0,hypot(x[i]-x[j],y[i]-y[j])-(r[i]+r[j]));
    graph[i].pb(Edge(c,j));
    graph[j].pb(Edge(c,i));
  }
  vector<Cost> dist;
  dist = move(dijkstra(graph,0));
  printf("%.10lf\n",dist[N+1]);
  return 0;
}
