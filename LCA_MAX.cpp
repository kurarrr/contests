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
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 100005;


class LCA {
  // 森のu-v間最大辺を求める
public:
  int size, log_size;
  vector<bool> used;
  vector<vector<int>> parent,cost;
  vector<int> depth;
  template <typename Edge>
  void dfs(const vector<vector<Edge>> &g, int v, int p, int d,int c) {
    used[v] = true; parent[0][v] = p; depth[v] = d; cost[0][v] = c;
    for (const Edge &e: g[v]) {
      if (e.to != p) dfs(g, e.to, v, d + 1, e.cost);
    }
  }
  template <typename Edge>
  LCA(const vector<vector<Edge>> &g) : size(g.size()), log_size(0), depth(size, 0) {
    for (int v = size; v > 0; v /= 2) ++log_size;
    parent.assign(log_size, vector<int>(size, 0));
    cost.assign(log_size, vector<int>(size, 0));
    used.assign(size,false);
    for(int i = 0; i < size; i++) if(!used[i]) dfs(g, i, -1, 0, -1);
    for (int k = 0; k < log_size - 1; ++k) {
      for (int v = 0; v < size; ++v) {
        if (parent[k][v] < 0) parent[k + 1][v] = -1;
        else parent[k + 1][v] = parent[k][parent[k][v]];
        if(parent[k][v]>0) cost[k+1][v] = max(cost[k][v],cost[k][parent[k][v]]);
      }
    }
  }
  int query(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int res = 0;
    for (int k = 0; k < log_size; ++k)
      if (((depth[v] - depth[u]) >> k) & 1){
        res = max(res,cost[k][v]);
        v = parent[k][v];
      }
    if (u == v) return res;
    for (int k = log_size - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v] && cost[k][u] != cost[k][v]) {
        res = max(res,cost[k][u]);
        res = max(res,cost[k][v]);
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    res = max(res,max(cost[0][u],cost[0][v]));
    return res;
  }
};

struct Edge {
  int to; int cost;
  Edge(int t) : to(t) {}
  Edge(int t,int c) : to(t),cost(c) {}
};

using Graph = vector<vector<Edge>>;

void add_edge(Graph &g,int a,int b,int c){
  g[a].pb(Edge(b,c)); g[b].pb(Edge(a,c));
}


struct UnionFindTree{
  int par[MAX_N],rank[MAX_N],size[MAX_N];
  UnionFindTree(int N){
    fill(rank,rank+N,0);
    fill(size,size+N,1);
    rep(i,N) par[i]=i;
  }
  int find(int x){
    if(par[x]==x) return x;
    else  return par[x]=find(par[x]);
  }
  void unite(int x,int y){
    x=find(x);
    y=find(y);
    if(x==y)  return ;
    if(rank[x]<rank[y]){
      par[x]=y;
    }else{
      par[y]=x;
      if(rank[x]==rank[y])  ++rank[x];
    }
    size[x]=size[y]=size[x]+size[y];
  }
  bool same(int x,int y){
    return find(x)==find(y);
  }
};

int main(){
  int N,M; cin >> N >> M;
  Graph graph(N);
  UnionFindTree uft(N);

  REP(i,1,M+1){
    int a,b; scanf("%d%d",&a,&b);
    a--; b--;
    if(!uft.same(a,b)) add_edge(graph,a,b,i);
    uft.unite(a,b);
  }
  LCA lca(graph);
  
  int Q; cin >> Q;
  rep(i,Q){
    int a,b; scanf("%d%d",&a,&b);
    a--; b--;
    if(!uft.same(a,b)) cout << "-1" << endl;
    else cout << lca.query(a,b) << endl;
  }
  return 0;
}