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


struct HLDecomposition {
  int n, pos;
  vector<vector<int> > graph;
  vector<int> vid, head, sub, par, dep, inv, type;
  // vid[u]  := the ordeing of u on decomposition
  // sub[u]  := #(vertices of u-root subtree)
  // head[u] := the head of the line on decomposition
  // type[u] := the order of connected components

  HLDecomposition(){}
  HLDecomposition(const vector<vector<int>>& g, vector<int> rs = {0})
  :n(g.size()), pos(0), graph(g), vid(g.size(),-1), head(g.size()), sub(g.size(),1),
    par(g.size(), -1), dep(g.size(), 0), inv(g.size()), type(g.size())
  {
    int c = 0;
    for(int r:rs){
      dfs_sz(r);
      head[r] = r;
      dfs_hld(r, c++);
    }
  }
 
  void dfs_sz(int v) {
    for(int &u : graph[v]){
      if(u == par[v]) continue;
      par[u] = v;
      dep[u] = dep[v] + 1;
      dfs_sz(u);
      sub[v] += sub[u];
      if(sub[u] > sub[graph[v][0]]) swap(u,graph[v][0]);
      // sub[graph[v][0]] is largest 
    }
  }
 
  void dfs_hld(int v,int c) {
    vid[v] = pos++;
    inv[vid[v]] = v;
    type[v] = c;
    for(int u : graph[v]){
      if(u==par[v]) continue;
      head[u] = ( u == graph[v][0] ? head[v] : u);
      dfs_hld(u,c);
    }
  }
 
  // for_each(vertex)
  // [l,r] <- attention!!
  template<typename F>
  void for_each(int u, int v, const F& f) {
    while(1){
      if(vid[u] > vid[v]) swap(u,v); // vid[u] <= vid[v]
      f(max(vid[head[v]],vid[u]), vid[v]);
      if(head[u] != head[v]) v = par[head[v]];
      else break;
    }
  }
 
  template<typename T,typename Q,typename F>
  T for_each(int u,int v,T ti,const Q &q,const F &f){
    T l = ti, r = ti;
    while(1){
      if(vid[u] > vid[v]){
        swap(u,v);
        swap(l,r);
      }
      l = f(l, q(max(vid[head[v]], vid[u]), vid[v]));
      if(head[u] != head[v]) v = par[head[v]];
      else break;
    }
    return f(l,r);
  }
 
  // for_each(edge)
  // [l,r] <- attention!!
  template<typename F>
  void for_each_edge(int u, int v,const F& f) {
    while(1){
      if(vid[u] > vid[v]) swap(u,v);
      if(head[u] != head[v]){
        f(vid[head[v]], vid[v]);
        v = par[head[v]];
      }else{
        if(u!=v) f(vid[u]+1, vid[v]);
        break;
      }
    }
  }

  int edge_id(int u, int v){
    // vid of the farther one of {u, v}
    int ch = dep[u] > dep[v] ? u : v;
    return vid[ch];
  }
 
  int lca(int u,int v){
    while(1){
      if(vid[u] > vid[v]) swap(u,v);
      if(head[u]==head[v]) return u;
      v = par[head[v]];
    }
  }
 
  int distance(int u,int v){
    return dep[u] + dep[v] - 2 * dep[lca(u,v)];
  }
};

template <typename T> class FenwickTree {
  const int n;
  std::vector<T> data;

  public:
  /// @brief
  /// 長さ count の Fenwick Tree を作り，全ての要素を 0 で初期化する．
  /// @complexity $O(n)$
  FenwickTree(int count) : n(count), data(count, 0) { ; }

  /// @brief
  /// pos 番目の要素に値 value を加える．
  /// @complexity $O(\\log(n))$
  void add(int pos, const T &value) {
    assert(0 <= pos && pos < n);
    for (int i = pos; i < n; i |= i + 1) data[i] += value;
  }

  /// @brief
  /// 区間 [0, pos) 番目の範囲の和を求める．(pos = 0 のときは 0 を返す．)
  /// @complexity $O(\\log(n))$
  T sum(int pos) const {
    assert(0 <= pos && pos <= n);
    T res = 0;
    for (int i = pos - 1; i >= 0; i = (i & (i + 1)) - 1) {
      res += data[i];
    }
    return res;
  }

  /// @brief
  /// 区間 [l, r) 番目の範囲の和を求める．(l = r のときは 0 を返す．)
  /// @complexity $O(\\log(n))$
  T sum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) + (-sum(l));
  }
  using value_type = T;
  using update_type = T;
};

const int INF = 1<<29;
const long long LINF=1LL<<59;

void solve(){
  ll N; cin >> N ;
  vvi g(N);
  rep(i,N-1){
    int u,v; cin >> u >> v ;
    u--; v--;
    g[u].pb(v); g[v].pb(u);
  }
  HLDecomposition hld(g);
  FenwickTree<ll> fw(N+1);
  auto add_query = [&](int l,int r){
    fw.add(l,1LL);
    fw.add(r+1,-1LL);
  };
  ll Q; cin >> Q ;
  rep(q,Q){
    int a,b; cin >> a >> b ;
    a--; b--;
    hld.for_each(a,b,add_query);
  }
  ll ans = 0;
  rep(i,N){
    ll s = fw.sum(i+1);
    ans += s * (s+1)/2LL;
  }
  cout << ans << endl;
}