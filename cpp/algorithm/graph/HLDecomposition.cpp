// https://atcoder.jp/contests/abc133/submissions/6310832

#include "../../template/template.cpp"
#include "../data_structure/FenwickTree.cpp"

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
