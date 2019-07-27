#include "../../template/template.cpp"

template <typename M> // Mは 型type, 単位元id(), 演算op() を持つモノイド
class DynamicSegmentTree {
  using T = typename M::type;
  struct node {
    long long pos;
    T val, all;
    node *l, *r;
    node(int p, T v)
      : pos(p), val(v), all(v), l(nullptr), r(nullptr) {}
  };
  private:
    const long long n;
    node *root;
  public:
    DynamicSegmentTree(long long n)
      :n(1LL << (long long)ceil(log2(n))), root(nullptr) {}
    void update(int p, T val) {
      // update : tree[p] = val
      root = change(root, p, val, 0, n);
    }
    T query(long long l, long long r) {
      // res : op[l,r)
      return query(l, r, root, 0, n);
    }
  private:
    T value(node *t) {
      return t ? t->all : M::id();
    }
    T query(long long l, long long r, node* t, long long lb, long long ub) {
      if (!t || ub <= l || r <= lb) return M::id();
      if (l <= lb && ub <= r) return t->all;
      long long c = (lb + ub) / 2;
      T res = query(l, r, t->l, lb, c);
      if (l <= t->pos && t->pos < r) res = M::op(res, t->val);
      return M::op(res, query(l, r, t->r, c, ub));
    }
    node *change(node* t, long long p, T val, long long lb, long long ub) {
      if (!t) return new node(p, val);
      if (t->pos == p) {
        t->val = val;
        t->all = M::op(value(t->l), M::op(t->val, value(t->r)));
        return t;
      }
      long long c = (lb + ub) / 2;
      if (p < c) {
        if (p > t->pos) swap(p, t->pos), swap(val, t->val);
        t->l = change(t->l, p, val, lb, c);
      }
      else {
        if (p < t->pos) swap(p, t->pos), swap(val, t->val);
        t->r = change(t->r, p, val, c, ub);
      }
      t->all = M::op(value(t->l), M::op(t->val, value(t->r)));
      return t;
    }
};

struct SUM{
  using type = ll;
  static type id(){return 0LL;}
  static type op(const type &a ,const type &b){return a+b;}
};

void solve(){
  int N; scanf("%d",&N);
  DynamicSegmentTree<SUM> tree(1e9+1);
  ll ans = 0;
  rep(i,N){
    ll p,q,r;
    scanf("%lld %lld %lld",&p,&q,&r);
    if(p==0){
      ll t = tree.query(q,q+1);
      tree.update(q,t+r);
    }else{
      ll t = tree.query(q,r+1);
      ans += t;
    }
  }
  cout << ans << endl;
}