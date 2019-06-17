// https://yukicoder.me/submissions/235229

#include "bits/stdc++.h"
#include "../../template/template.cpp"

template<typename V> struct SuperMultiSet {
  int getrand(int x) { static uint32_t y = time(0); y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5); return y % x; }
  struct Node {
    V val;
    Node *lch, *rch;
    int sz;
    Node(V a) :val(a), lch(0), rch(0), sz(1) { init(); }
    void init() { }
    void push() { }
    void update() { }
  };
  SuperMultiSet() :root(NULL) {}

  Node *root;
  inline int size(Node *t) { return t ? t->sz : 0; }
  int size() { return size(root); }
  inline void push(Node *t) {
    if (t == NULL)return;
    t->push();
  }
  inline Node *update(Node *t) {
    if (!t)return NULL;
    t->sz = size(t->lch) + size(t->rch) + 1;
    t->update();
    return t;
  }
  Node *merge(Node *a, Node *b) {
    push(a); push(b);
    if (!a)return b;
    if (!b)return a;

    if (getrand(size(a) + size(b))<size(a)) {
      a->rch = merge(a->rch, b);
      return update(a);
    }
    else {
      b->lch = merge(a, b->lch);
      return update(b);
    }
  }
  template<class... T> Node *merge(Node *a, T... y) { return merge(a, merge(y...)); }
  pair<Node *, Node *>split(Node *t, int k) {//[0,k) [k,N)
    push(t);
    if (!t)return make_pair(t, t);
    if (k <= size(t->lch)) {
      pair<Node *, Node *>s = split(t->lch, k);
      t->lch = s.second;
      return make_pair(s.first, update(t));
    }
    else {
      pair<Node *, Node *>s = split(t->rch, k - size(t->lch) - 1);
      t->rch = s.first;
      return make_pair(update(t), s.second);
    }
  }
  int lower_bound(V x) { return lower_bound(root, x); }
  int lower_bound(Node *t, V x) {
    push(t);
    if (!t)return 0;
    if (t->val >= x)return lower_bound(t->lch, x);
    return lower_bound(t->rch, x) + size(t->lch) + 1;
  }
  // [l,r]番目でa,b,cに分ける(終わったらちゃんとマージすること)
  // rootは0になってる
  tuple<Node*, Node*, Node*> split3(int l, int r) {
    auto p = split(root, l);

    auto a = p.first;

    auto q = split(p.second, r - l + 1);

    auto b = q.first;
    auto c = q.second;
    root = 0;

    return make_tuple(a, b, c);
  }
  void dmp() {
    dmp(root);
    cout << endl;
  }
  void dmp(Node *t) {
    if (t == NULL)return;
    push(t);
    dmp(t->lch);
    cout << t->val << " ";
    dmp(t->rch);
  }
  void insert(V x) {
    int k = lower_bound(x);

    Node *a, *b;
    tie(a, b) = split(root, k);

    root = merge(a, new Node(x), b);
  }
  void erase(V x) {
    int k = lower_bound(x);

    Node *a, *b;
    tie(a, b) = split(root, k);

    Node *ba, *bb;
    tie(ba, bb) = split(b, 1);

    root = merge(a, bb);
  }
  V getAt(int i) {
    // k番目 (0-index)
    auto p = split(root, i);
    auto a = p.first;
    auto q = split(p.second, 1);
    Node* b = q.first;
    auto c = q.second;

    root = merge(merge(a, b), c);

    return b->val;
  }
};

int Q, K;
SuperMultiSet<ll> rbst;

void _main() {
  cin >> Q >> K;
  rep(q, Q) {
    int t; cin >> t;
    if (t == 1) {
      ll v; cin >> v;
      rbst.insert(v);
    }
    else {
      int n = rbst.size();
      if (n < K) printf("-1\n");
      else {
        ll ans = rbst.getAt(K - 1);
        rbst.erase(ans);
        printf("%lld\n", ans);
      }
    }
  }
}