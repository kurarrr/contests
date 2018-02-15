// https://beta.atcoder.jp/contests/abc014/submissions/2074370

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
  int size, log_size;
  vector<vector<int>> parent;
  vector<int> depth;
  template <typename Edge>
  void dfs(const vector<vector<Edge>> &g, int v, int p, int d) {
    parent[0][v] = p; depth[v] = d;
    for (const Edge &e: g[v]) {
      if (e.to != p) dfs(g, e.to, v, d + 1);
    }
  }
public:
  template <typename Edge>
  LCA(const vector<vector<Edge>> &g, int root) : size(g.size()), log_size(0), depth(size, 0) {
    for (int v = size; v > 0; v /= 2) ++log_size;
    parent.assign(log_size, vector<int>(size, 0));
    dfs(g, root, -1, 0);
    for (int k = 0; k < log_size - 1; ++k) {
      for (int v = 0; v < size; ++v) {
        if (parent[k][v] < 0) parent[k + 1][v] = -1;
        else parent[k + 1][v] = parent[k][parent[k][v]];
      }
    }
  }
  int query(int u, int v) {
    int ui = u, vi = v;
    if (depth[u] > depth[v]) swap(u, v);
    for (int k = 0; k < log_size; ++k)
      if (((depth[v] - depth[u]) >> k) & 1) v = parent[k][v];
    if (u == v) return abs(depth[vi] - depth[ui]);
    for (int k = log_size - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    // LCA = parent[0][u]
    return depth[vi] + depth[ui] - 2 * depth[parent[0][u]];
  }
};

struct Edge {
  int to;
  Edge(int t) : to(t) {}
};

using Graph = vector<vector<Edge>>;
Graph graph;

void add_edge(Graph &g, int from, int to) {
  g[from].push_back(Edge(to));
  g[to].push_back(Edge(from));
}

int main(){
  int N; cin >> N;
  graph.resize(N);
  rep(i,N-1){
    int a,b; scanf("%d%d",&a,&b);
    a--; b--;
    add_edge(graph,a,b);
  }
  LCA lca(graph,0);
  int Q; cin >> Q;
  rep(i,Q){
    int a,b; scanf("%d%d",&a,&b);
    a--; b--;
    cout << lca.query(a,b) + 1 << endl;
  }
  return 0;
}
