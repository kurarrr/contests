#ifdef DEBUG_IS_VALID
#define DEB 1 
#define _LIBCPP_DEBUG 0
#else
#define DEB 0
#define NDEBUG
#endif

#include <bits/stdc++.h>
using namespace std;

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define fi first
#define se second
#pragma GCC optimize ("-O3")

using namespace std;

#define DUMPOUT cout
#define dump(...) if(DEB) DUMPOUT<<"  "<<#__VA_ARGS__<<" :["<<__LINE__<<":"<<__FUNCTION__<<"]"<<endl<<"    "; if(DEB) dump_func(__VA_ARGS__)
template<typename T1,typename T2>ostream& operator << (ostream& os, pair<T1,T2> p){cout << "(" << p.first << ", " << p.second << ")"; return os;}
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) { os << "{"; for (int i = 0; i<vec.size(); i++) os << vec[i] << (i + 1 == vec.size() ? "" : ", "); os << "}"; return os; }
template<typename T>ostream& operator << (ostream& os, set<T>& st){cout << "{"; for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : ""); cout << "}"; return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : ""); cout << "}"; return os; }

void dump_func(){DUMPOUT << endl;}
template <class Head, class... Tail>void dump_func(Head&& head, Tail&&... tail){ DUMPOUT << head; if (sizeof...(Tail) == 0) { DUMPOUT << " "; } else { DUMPOUT << ", "; } dump_func(std::move(tail)...);}
template<class T> inline bool chmax(T& a,T const& b){if(a>=b) return false; a=b; return true;}
template<class T> inline bool chmin(T& a,T const& b){if(a<=b) return false; a=b; return true;}
void solve();
int main(void) {
  std::cout << std::fixed << std::setprecision(15);
  solve();
	return 0;
}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vp = vector<Pl>;
using vvp = vector<vp>;

const int INF = (1<<30)-10;
const long long LINF=1LL<<59;

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
using Node = ll;
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

void solve(){
  ll N,M;
  cin >> N >> M ;
  Graph g(N+1);
  rep(i,M){
    ll a,b;
    cin >> a >> b ;
    g[b].pb(Edge(1LL,a));
  }
  auto dist = dijkstra(g,0);
  REP(i,1,N+1){
    if(dist[i]<=3) cout << "Yes" << endl;
    else cout << "No" << endl;
  }
  return;
}