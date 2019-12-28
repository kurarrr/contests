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
const int MAX_N = 41;

class MaximumMatching {
  /*
    Maximum Matching in General Graphs
    - O(nm \log_{\max\{2, 1 + m/n\}} n) time
    - O(n + m) space
    Note: each vertex is 1-indexed.
  */

  public:
    struct Edge {
      int from, to;
      Edge(){}
      Edge(int from,int to)
      :from(from),to(to){}
    };

    MaximumMatching(int N, const vector<Edge>& raw_edges) : N(N) {
      ofs.assign(N + 2, 0);
      for (auto& e : raw_edges) ++ofs[e.from + 1], ++ofs[e.to + 1];
      for (int i = 1; i <= N + 1; ++i) ofs[i] += ofs[i - 1];
      edges.resize(2 * raw_edges.size());
      for (auto& e : raw_edges) {
        edges[ofs[e.from]++] = {e.from, e.to};
        edges[ofs[e.to]++] = {e.to, e.from};
      }
      for (int i = N + 1; i > 0; --i) ofs[i] = ofs[i - 1];
      ofs[0] = 0;
    }

    int maximum_matching() {
      vector<int> label(N + 1, -1), mate(N + 1, 0), first(N + 1, 0);
      vector<int> que(N);
      int qh = 0, qt = 0;

      auto enqueue = [&] (int v) { que[qt++] = v; };
      auto dequeue = [&] { return que[qh++]; };
      auto encode = [&] (int eid) { return (N + 1) + eid; };
      auto decode = [&] (int h) { return h - (N + 1); };

      function< int(int) > find_first = [&] (int v) {
        return label[first[v]] < 0 ? first[v] : first[v] = find_first(first[v]);
      };

      function< void(int, int) > rematch = [&] (int v, int w) {
        auto t = mate[v]; mate[v] = w;
        if (mate[t] != v) return;
        if (label[v] <= N) {
          mate[t] = label[v];
          rematch(label[v], t);
        } else {
          auto& e = edges[decode(label[v])];
          int x = e.from, y = e.to;
          rematch(x, y); rematch(y, x);
        }
      };

      auto contract = [&] (int x, int y, int eid) {
        int r = find_first(x), s = find_first(y);
        if (r == s) return;
        auto h = encode(eid);
        label[r] = label[s] = -h;
        int join = -1; // mate[lca]
        while (1) {
          if (s != 0) swap(r, s);
          r = find_first(label[mate[r]]);
          if (label[r] == -h) {
            join = r;
            break;
          } else label[r] = -h;
        }
        for (auto v : { first[x], first[y] }) {
          for (; v != join; v = first[label[mate[v]]]) {
            label[v] = h;
            first[v] = join;
            enqueue(v);
          }
        }
      };

      auto augmented = [&] (int u) {
        label[u] = first[u] = 0;
        for (qh = qt = 0, enqueue(u); qh < qt; ) {
          auto x = dequeue();
          for (int eid = ofs[x]; eid < ofs[x + 1]; ++eid) {
            auto y = edges[eid].to;
            if (mate[y] == 0 && y != u) {
              mate[y] = x;
              rematch(x, y);
              return true;
            } else if (label[y] >= 0) {
              contract(x, y, eid);
            } else if (label[mate[y]] < 0) {
              label[mate[y]] = x;
              first[mate[y]] = y;
              enqueue(mate[y]);
            }
          }
        }
        return false;
      };

      int match = 0;
      for (int u = 1; u <= N; ++u) if (mate[u] == 0 && augmented(u)) {
        match += 1;
        if (N - 2 * match <= 1) break;
        if (10 * qt < N) {
          label[0] = -1;
          for (int qi = 0; qi < qt; ++qi) {
            label[que[qi]] = label[mate[que[qi]]] = -1;
          }
        } else fill(label.begin(), label.end(), -1);
      }

      /*
      vector< pair<int, int> > matching(match);
      match = 0;
      rep(u, 1, N + 1) if (mate[u] > u) {
        matching[match++] = {u, mate[u]};
      }
      */

      return match;
    }

  private:
    int N;
    vector<int> ofs;
    vector<Edge> edges;
};

using Edge = MaximumMatching::Edge;

int main() {
  set<P> anti_graph;
  int N,M; cin >> N >> M;
  rep(i,M){
    int a,b; cin >> a >> b;
    anti_graph.insert(P(a,b)); anti_graph.insert(P(b,a));
  }
  vector<Edge> edges;
  REP(i,1,N) REP(j,i+1,N+1){
    if(!anti_graph.count(P(i,j))){
      edges.pb(Edge(i,j));
      edges.pb(Edge(j,i));
    }
  }
  cout << edges.size() << endl;

  auto mm = MaximumMatching(N,edges);
  cout << mm.maximum_matching() << endl;
}