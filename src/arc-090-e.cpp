// https://beta.atcoder.jp/contests/arc090/submissions/2038656
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

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;
const int MAX_N = 100005;

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
(Graph &graph, Node start, ll pat[], Cost zero = 0LL)
{
  using Pcn = pair<Cost,Node>;
  priority_queue<Pcn,vector<Pcn>,greater<Pcn>> que;
  vector<Cost> dist(graph.size(),inf<Cost>);
  dist[start] = zero;
  pat[start] = 1LL;
  que.push(Pcn(zero,start));
  while(!que.empty()){
    Pcn p = que.top(); que.pop();
    Node v = p.second; //行き先
    if(dist[v] < p.first)  continue;
    for(Edge e : graph[v]){
      if(dist[v]+e.cost < dist[e.to]){
        dist[e.to] = dist[v]+e.cost;
        // 最小値を更新したら今までのパターンを消す
        pat[e.to] = 0LL;
        que.push(Pcn(dist[e.to],e.to));
      }
      if(dist[v]+e.cost == dist[e.to]){
        // 最小値を見つけたらパターンを足す
        (pat[e.to] += pat[v]) %= lmod;
      }
    }
  }
  return dist;
}

Graph graph;
ll patS[MAX_N],patT[MAX_N];

int main(){
  int N,M; scanf("%d%d",&N,&M);
  graph.resize(N);
  int S,T; scanf("%d%d",&S,&T); S--; T--;
  rep(i,M){
    int l,r; ll dd; scanf("%d%d%lld",&l,&r,&dd);
    l--; r--; graph[l].pb(Edge(dd,r)); graph[r].pb(Edge(dd,l));
  }
  auto distS = move(dijkstra(graph,S,patS));
  auto distT = move(dijkstra(graph,T,patT));
  ll ans = patS[T] * patS[T] % lmod;
  ll len = distS[T];
  rep(i,N){
    if(distS[i]+distT[i]==len && distS[i]*2LL==len){
      (ans += (lmod - patS[i]*patS[i]%lmod*patT[i]%lmod*patT[i]%lmod)) %= lmod;
    }
  }
  rep(i,N) for(auto e:graph[i]){
    int j = e.to; ll c = e.cost;
    if(distS[i]+c+distT[j]==len && distS[i]*2LL<len && distT[j]*2LL<len){
      (ans += (lmod - patS[i]*patS[i]%lmod*patT[j]%lmod*patT[j]%lmod)) %= lmod;
    }
  }
  cout << ans << endl;
  return 0;
}
