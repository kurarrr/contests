#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#pragma GCC optimize ("-O3")

using namespace std;

#define DEBUG_IS_VALID

#ifdef DEBUG_IS_VALID
#define DEB 1 
#else
#define DEB 0
#endif
#define DUMPOUT cout
#define dump(...) if(DEB) DUMPOUT<<"  "<<#__VA_ARGS__<<" :["<<__LINE__<<":"<<__FUNCTION__<<"]"<<endl<<"    "; if(DEB) dump_func(__VA_ARGS__)
template<typename T1,typename T2>ostream& operator << (ostream& os, pair<T1,T2> p){cout << "(" << p.first << ", " << p.second << ")"; return os;}
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) { os << "{"; for (int i = 0; i<vec.size(); i++) os << vec[i] << (i + 1 == vec.size() ? "" : ", "); os << "}"; return os; }
template<typename T>ostream& operator << (ostream& os, set<T>& st){for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : ""); cout << "}"; return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : ""); cout << "}"; return os; }

void dump_func(){DUMPOUT << endl;}
template <class Head, class... Tail>void dump_func(Head&& head, Tail&&... tail){ DUMPOUT << head; if (sizeof...(Tail) == 0) { DUMPOUT << " "; } else { DUMPOUT << ", "; } dump_func(std::move(tail)...);}
template<class T> inline bool chmax(T& a,T const& b){if(a>=b) return false; a=b; return true;}
template<class T> inline bool chmin(T& a,T const& b){if(a<=b) return false; a=b; return true;}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;

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
using Graph = vector<vector<Edge>>;

vector<Cost> dijkstra
(Graph &graph, Node start, Cost zero = 0LL)
{
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
