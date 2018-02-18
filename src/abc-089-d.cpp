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
const int MAX_N = 51;

template<typename T> T inf;
template<> constexpr int inf<int> = 1<<30;
template<> constexpr ll inf<ll> = 1LL<<60;
template<> constexpr double inf<double> = 1e30;

using Cost = int;
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

string s[MAX_N];

int main(){
  int H,W; cin >> H >> W;
  rep(i,H) cin >> s[i];
  int N = H*W;
  Graph graph(N);
  int cnt = -1;
  rep(i,H) rep(j,W){
    if(s[i][j]=='.') cnt++;
    else continue;
    for(int k = -1; k <= 1;k += 2) if(i+k>=0 && i+k<H) if(s[i+k][j]=='.'){
      graph[W*i+j].pb(Edge(1,W*(i+k)+j));
      // cout << W*i+j << " to " << W*(i+k)+j << endl;
    }
    for(int k = -1; k <= 1;k += 2) if(j+k>=0 && j+k<W) if(s[i][j+k]=='.'){
      graph[W*i+j].pb(Edge(1,W*i+j+k));
      // cout << W*i+j << " to " << W*(i)+j+k << endl;
    }
  }
  auto dist = move(dijkstra(graph,0));
  rep(i,H) rep(j,W){
    // cout << i << " " << j << " -> " << graph[W*i+j].size() << endl;
  }
  if(dist[N-1]==inf<int>) cout << "-1" << endl;
  else cout << cnt - dist[N-1] << endl;
  return 0;
}