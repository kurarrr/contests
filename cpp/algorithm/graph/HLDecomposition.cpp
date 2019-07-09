// https://atcoder.jp/contests/abc133/submissions/6310832
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

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vp = vector<Pl>;
using vvp = vector<vp>;

const int INF = 1<<29;
const long long LINF=1LL<<59;

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


void solve(long long N, long long Q, std::vector<long long> a, std::vector<long long> b, std::vector<long long> c, std::vector<long long> d, std::vector<long long> x, std::vector<long long> y, std::vector<long long> u, std::vector<long long> v){
  vvi g(N);
  rep(i,N-1){
    a[i]--; b[i]--; c[i]--;
    g[a[i]].pb(b[i]); g[b[i]].pb(a[i]);
  }
  HLDecomposition hld(g);
  vl ans(Q);
  {
    rep(q,Q){
      u[q]--; v[q]--; x[q]--;
    }
    FenwickTree<ll> fw(N+2);
    rep(i,N-1){
      int eid = hld.edge_id(a[i],b[i]);
      fw.add(eid, d[i]);
    }
    ll t; 
    auto qry = [&](int u,int v){
      t += fw.sum(u, v+1);
    };
    rep(q,Q){
      t = 0;
      hld.for_each_edge(u[q],v[q],qry);
      ans[q] += t;
    }
  }
  vvi cquery(N-1),cedge(N-1);
  rep(q,Q) cquery[x[q]].pb(q);
  rep(i,N-1) cedge[c[i]].pb(i);
  {
    FenwickTree<ll> cnt(N+2), num(N+2);
    rep(i,N-1){
      for(auto& j:cedge[i]){
        int eid = hld.edge_id(a[j],b[j]);
        cnt.add(eid, 1LL);
        num.add(eid, d[j]);
      }
      ll ct, nt;
      auto qry = [&](int u,int v){
        ct += cnt.sum(u,v+1);
        nt += num.sum(u,v+1);
      };
      for(auto& q:cquery[i]){
        ct = nt = 0;
        int eid = hld.edge_id(u[q],v[q]);
        hld.for_each_edge(u[q],v[q],qry);
        dump(u[q],v[q], ct,nt);
        ans[q] += y[q] * ct - nt;
      }
      for(auto& j:cedge[i]){
        int eid = hld.edge_id(a[j],b[j]);
        cnt.add(eid, -1LL);
        num.add(eid, -d[j]);
      }
    }
  }
  rep(q,Q) cout << ans[q] << endl;
}

int main(){
  long long N;
  scanf("%lld",&N);
  long long Q;
  scanf("%lld",&Q);
  std::vector<long long> a(N-1);
  std::vector<long long> b(N-1);
  std::vector<long long> c(N-1);
  std::vector<long long> d(N-1);
  for(int i = 0 ; i < N-1 ; i++){
    scanf("%lld",&a[i]);
    scanf("%lld",&b[i]);
    scanf("%lld",&c[i]);
    scanf("%lld",&d[i]);
  }
  std::vector<long long> x(Q);
  std::vector<long long> y(Q);
  std::vector<long long> u(Q);
  std::vector<long long> v(Q);
  for(int i = 0 ; i < Q ; i++){
    scanf("%lld",&x[i]);
    scanf("%lld",&y[i]);
    scanf("%lld",&u[i]);
    scanf("%lld",&v[i]);
  }
  solve(N, Q, std::move(a), std::move(b), std::move(c), std::move(d), std::move(x), std::move(y), std::move(u), std::move(v));
  return 0;
}
