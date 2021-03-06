#include "../../template/template.cpp"

namespace sub {
  template <typename T>
  constexpr typename std::enable_if<std::is_integral<T>::value, T>::type
  inf_sub() {
    return std::numeric_limits<T>::max() / 2 - 1000;
  }

  template <typename T>
  constexpr typename std::enable_if<std::is_floating_point<T>::value, T>::type
  inf_sub() {
    return std::min(std::numeric_limits<T>::max() / 2 - 1000, T(1e50));
  }
}  // namespace sub

/// @return Returns a large finite value representable by the numeric type T.
/// @note It is guaranteed that the return values is strictly less than std::numeric_limits<T>::max() / 2.
template <typename T> constexpr T inf() {
  static_assert(std::is_arithmetic<T>::value, "T must be arithmetic value");
  return sub::inf_sub<T>();
}

using Cost = ll;
using Node = int;
struct Edge{
  Cost cost; Node to;
  Edge(Cost cost,Node to)
    :cost(cost),to(to){}
};
ostream& operator << (ostream& os, Edge& e) {
  cout << "(" << e.cost << "," << e.to << ") "; return os;
}
using Graph = vector<vector<Edge>>;

vector<Cost> dijkstra
(Graph &graph, Node start, Cost zero = 0LL){
  using Pcn = pair<Cost,Node>;
  priority_queue<Pcn,vector<Pcn>,greater<Pcn>> que;
  vector<Cost> dist(graph.size(),inf<Cost>());
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

void add_edge(Graph& g,int u,int v,Cost c){
  g[u].pb(Edge(c,v));
  g[v].pb(Edge(c,u));
} 


int main(){
  int N,M; cin >> N >> M ;
  vvi nd_list(N);
  vi p(M),q(M),c(M);
  rep(i,M){
    int pp,qq,cc; cin >> pp >> qq >> cc ;
    pp--; qq--;
    nd_list[pp].pb(cc);
    nd_list[qq].pb(cc);
    p[i] = pp; q[i] = qq; c[i] = cc;
  }
  rep(i,N){
    nd_list[i].pb(0);
    sort(ALL(nd_list[i]));
    nd_list[i].erase(unique(ALL(nd_list[i])),nd_list[i].end());
  }
  vector<P> mp;
  rep(i,N) rep(j,nd_list[i].size()) mp.pb(P(i,nd_list[i][j]));
  map<P,int> rev_mp;
  rep(i,mp.size()) rev_mp[mp[i]] = i;
  int sz = mp.size();
  Graph g(sz);
  rep(i,N){
    int u = rev_mp[P(i,0)];
    for(auto color:nd_list[i]){
      if(color==0) continue;
      int v = rev_mp[P(i,color)];
      g[u].pb(Edge(1,v));
      g[v].pb(Edge(0,u));
    }
  }
  rep(i,M){
    int u = rev_mp[P(p[i],c[i])];
    int v = rev_mp[P(q[i],c[i])];
    g[u].pb(Edge(0,v));
    g[v].pb(Edge(0,u));
  }
  auto dist = move(dijkstra(g,rev_mp[P(0,0)]));
  auto ans = dist[rev_mp[P(N-1,0)]];
  cout << (ans!=inf<ll>() ? ans : -1) << endl;
  return 0;
}
