#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#pragma GCC optimize ("-O3")

using namespace std;

// #define DEBUG_IS_VALID

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
void _main();
int main(){ cin.tie(0); ios::sync_with_stdio(false); _main(); return 0;}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;

const int mod=1e9+7,INF=1<<29;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<59; 

// https://yukicoder.me/submissions/235229

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