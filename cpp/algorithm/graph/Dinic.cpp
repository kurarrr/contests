#include "../../template/template.cpp"
using Flow = ll;

struct Edge {
  int to, from;
  Flow cap;
  Edge(int from, int to, Flow f) : from(from), to(to), cap(f) {}
};

using Graph = vector<vector<Edge>>;

struct Dinic {
  int n, s, t;
  std::vector<int> level, prog, que;
  std::vector<std::vector<Flow>> cap, flow;
  std::vector<std::vector<int>> g;
  Flow inf;
  Dinic(const Graph &graph)
  : n(graph.size()),
    cap(n, std::vector<Flow>(n)),
    flow(n, std::vector<Flow>(n)),
    g(n, std::vector<int>()),
    inf(std::numeric_limits<Flow>::max() / 8)
  {
    for (int i = 0; i < n; i++) {
      for (auto &e : graph[i]) {
        int u = e.from, v = e.to;
        Flow c = e.cap;
        cap[u][v] += c;
        cap[v][u] += c;
        flow[v][u] += c;
        g[u].push_back(v);
        g[v].push_back(u);
      }
    }
  }
  inline Flow residue(int u, int v) { return cap[u][v] - flow[u][v]; }
  Flow solve(int s_, int t_) {
    this->t = t_, this->s = s_;
    que.resize(n + 1);
    Flow res = 0;
    while (levelize()) {
      prog.assign(n, 0);
      res += augment(s, inf);
    }
    return res;
  }
  bool levelize() {
    int l = 0, r = 0;
    level.assign(n, -1);
    level[s] = 0;
    que[r++] = s;
    while (l != r) {
      int v = que[l++];
      if (v == t) break;
      for (const int &d : g[v])
        if (level[d] == -1 && residue(v, d) != 0) {
          level[d] = level[v] + 1;
          que[r++] = d;
        }
    }
    return level[t] != -1;
  }
  Flow augment(int v, Flow lim) {
    Flow res = 0;
    if (v == t) return lim;
    for (int &i = prog[v]; i < (int)g[v].size(); i++) {
      const int &d = g[v][i];
      if (residue(v, d) == 0 || level[v] >= level[d]) continue;
      const Flow aug = augment(d, std::min(lim, residue(v, d)));
      flow[v][d] += aug;
      flow[d][v] -= aug;
      res += aug;
      lim -= aug;
      if (lim == 0) break;
    }
    return res;
  }
};

void solve(){
  int N; cin >> N ;
  Graph g(N+2);
  ll a[MAX_N];
  ll _sum = 0;
  rep(i,N){
    scanf("%lld",a+i);
    if(a[i]>0) _sum += a[i];
  }
  const int S = N,T = N+1;
  rep(i,N){
    if(a[i]<0){
      g[S].pb(Edge(S,i,-a[i]));

    }else{
      g[i].pb(Edge(i,T,a[i]));
    }
  }
  rep(i,N){
    int num1 = i+1;
    for(int num2 = num1*2; num2 <= N; num2 += num1){
      g[num1-1].pb(Edge(num1-1,num2-1,LINF));
    }
  }
  Dinic dn(g);
  cout << _sum - dn.solve(S,T) << endl;
  return 0;
}