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

struct BiconnectedGraph{
  using PInt = pair<int, int>;
  int n, k;
  // k := the size of T
  vector<vector<int> > G, T, C;
  // G    := original graph
  // T    := compressed graph
  // C[u] := components \subeq V(G) | belongs to u \in V(T)
  vector<int> ord, low, belong;
  // belong[u] := (the node in T which u\in G belongs to)
  vector<PInt> B;
  BiconnectedGraph(){}
  BiconnectedGraph(const vector<vector<int>>& graph)
  :n(graph.size()), G(graph), C(graph.size()), T(graph.size()), k(0)
  {
    ord.resize(n);
    low.resize(n);
    belong.resize(n);
    fill(ord.begin(),ord.end(),-1);
    fill(belong.begin(),belong.end(),-1);
    for(int v = 0; v < n; v++){
      if(ord[v]>=0) continue;
      dfs(v,-1,k);
    }
    k = 0;
    for(int i = 0; i < (int)B.size(); i++){
      add_component(B[i].first,k);
      add_component(B[i].second,k);
    }
    for(int v=0;v<n;v++) add_component(v,k);
    for(int i=0;i<(int)B.size();i++){
      int u = belong[B[i].first], v = belong[B[i].second];
      T[u].push_back(v);
      T[v].push_back(u);
    }
    T.resize(k);
    C.resize(k);
  }

  bool is_bridge(int u,int v){
    if(ord[u] > ord[v]) swap(u,v);
    return ord[u] < low[v];
  }

  void dfs(int v,int p,int &k){
    ord[v] = low[v] = k;
    ++k;
    for(int u:G[v]){
      if(u == p) continue;
      if(ord[u] >= 0){
        low[v] = min(low[v],ord[u]);
      }else{
        dfs(u,v,k);
        low[v] = min(low[v],low[u]);
      }
      if(is_bridge(u,v)) B.push_back(PInt(u,v));
    }
  }

  void fill_component(int c,int v){
    C[c].push_back(v);
    belong[v]=c;
    for(int u:G[v]){
      if(belong[u]>=0||is_bridge(u,v)) continue;
      fill_component(c,u);
    }
  }

  void add_component(int v,int &k){
    if(belong[v]>=0) return;
    fill_component(k++,v);
  }
};

struct HLDecomposition {
  int n, pos;
  vector<vector<int> > graph;
  // NOTE: graph should be connected
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
    // q := (区間で実行されるquery)
    // f := (2項間のquery)
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


template <class Monoid> class SegmentTree{
  private:
    using T = typename Monoid::type;
    int sz, N;
    vector<T> dat;
  public:
    SegmentTree(const vector<T> &vec){
      sz = vec.size(); N = 1; while(N<sz) N<<=1;
      dat.resize(2*N);
      fill(dat.begin(),dat.end(),Monoid::id());
      copy(vec.begin(),vec.end(),dat.begin()+N-1);
      for(int i=N-2;i>=0;i--) dat[i]=Monoid::op(dat[2*i+1],dat[2*i+2]);
    }
    SegmentTree(const int n){
      sz = n; N = 1; while(N<n) N<<=1;
      dat.resize(2*N);
      fill(dat.begin(),dat.end(),Monoid::id());
      for(int i=N-2;i>=0;i--) dat[i]=Monoid::op(dat[2*i+1],dat[2*i+2]);
    }
    void update(int i,T val){
      assert(0<=i && i<sz);
      dat[i+=N-1] = val;
      while(i>0){
        i=(i-1)/2;
        dat[i]=Monoid::op(dat[2*i+1],dat[2*i+2]);
      }
      return;
    }
    T query(int a,int b){ // op[a,b)
      return query(a,b,0,0,N);}
    T query(int a,int b,int k,int l,int r){
      assert(0<=l && l<=r && r<2*N);
      if(r<=a || b<=l) return Monoid::id();
      else if(a<=l && r<=b) return dat[k];
      else{
        T lval=query(a,b,2*k+1,l,(l+r)/2);
        T rval=query(a,b,2*k+2,(l+r)/2,r);
        return Monoid::op(lval,rval);
      }
    }
};

struct RMQ{
  using type = Pl;
  static type id(){return Pl(-LINF,-LINF);}
  static type op(const type &a ,const type &b){return max(a,b);}
};

int main(){
  ll N, M, Q;
  cin >> N >> M >> Q ;
  vvi g(N);
  rep(i,M){
    int a,b; cin >> a >> b ;
    a--; b--;
    g[a].pb(b); g[b].pb(a);
  }
  BiconnectedGraph bic(g);
  ll sz = bic.k;
  HLDecomposition hld(bic.T);
  dump(hld.vid);
  SegmentTree<RMQ> rmq(sz+2);
  // note: RMQ's order should be hld-order
  vector<priority_queue<ll>> que(sz);
  // same index with rmq
  dump(bic.k);
  dump(bic.C);
  dump(bic.T);
  Pl t = {-LINF, -LINF};
  auto qry = [&](int u, int v){
    chmax(t,rmq.query(u, v+1));
  };
  rep(q,Q){
    ll a,b,c;
    cin >> a >> b >> c ;
    if(a==1){
      b--;
      int num = bic.belong[b]; // index in bic.T
      num = hld.vid[num]; // index in hld
      if(num<0){
        cout << "hoge" << endl;
      }
      if(que[num].empty() || c > que[num].top()){
        rmq.update(num, Pl(c, num));
      }
      que[num].push(c);
    }else{
      t = {-LINF, -LINF};
      int u, v;
      u = bic.belong[b-1];
      v = bic.belong[c-1];
      hld.for_each(u, v, qry);
      cout << (t.first != -LINF ? t.first : -1) << endl;
      if(t.first != -LINF){
        int num = t.second;
        que[num].pop();
        if(!que[num].empty()) rmq.update(num, Pl(que[num].top(), num));
        else rmq.update(num, Pl(-LINF,-LINF));
      }
    }
  }
  return 0;
}
