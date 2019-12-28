#include "../../template/template.cpp"
#include "./utils.cpp"

using Cost = ll;
using Node = int;
struct Edge{
  Cost cost; Node to;
  Edge(Cost cost,Node to)
    :cost(cost),to(to){}
};
ostream& operator << (ostream& os, const Edge& e){
  cout << "{" << e.cost << ", " << e.to <<  "}"; return os;
}
using Graph = vector<vector<Edge>>;
struct BellmanFord{
  bool minus_cycle = false;
  vector<long long> dist;
  int cnt, N;
  BellmanFord(const Graph& graph, Node start = 0)
  :cnt(0), N(graph.size()), dist(graph.size(),LINF){
    dist[start] = 0;
    while(cnt < N){
      bool update = false;
      for(int i = 0; i < N; i++){
        for(auto&& e:graph[i]){
          if((dist[i] + e.cost < dist[e.to])){
            dist[e.to] = dist[i] + e.cost;
            update = true;
          }
        }
      }
      if(update) cnt++;
      else break;
    }
    minus_cycle = (cnt >= N);
  }
};

void abc_137_e(){
  // https://atcoder.jp/contests/abc137/submissions/6837394
  long long N, M, p; cin >> N >> M >> p ;
  vl A(M), B(M), C(M);
  rep(i,M) cin >> A[i] >> B[i] >> C[i] ;
  vvi gt(N);
  rep(i,M){
    A[i]--; B[i]--;
    gt[A[i]].pb(B[i]);
  }
  auto r1 = reachable_from(gt, 0);
  auto r2 = reachable_to(gt, N-1);
  dump(r1,r2);
  int sz = 0;
  vi mp(N);
  rep(i,N){
    if(r1[i] && r2[i]) mp[i] = sz++;
    else mp[i] = -1;
  }
  Graph g(sz);
  rep(i,M){
    ll a = mp[A[i]]; ll b = mp[B[i]];
    if(a<0||b<0) continue;
    g[a].pb(Edge(-(C[i]-p),b));
  }
  if(!r1[0]){
    exit(1);
    return;
  }
  auto bf = BellmanFord(g);
  if(bf.minus_cycle) cout << "-1" << endl;
  else cout << max(0LL,-bf.dist[mp[N-1]]) << endl;
}

void solve(){
  abc_137_e();
}
