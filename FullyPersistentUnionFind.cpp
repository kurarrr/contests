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
const int MAX_N = 100005;

class Array {
  public:
  Array() {}

  Array(int n) {
    h = 0;
    for (int i = 1; i < n; i *= 8) h += 3;
  }

  int *mutable_get(int k) {
    auto p = mutable_get(k, root, 0, h);
    root = p.first;
    return &p.second->value;
  }

  int operator[](int k) {
    node *res = immutable_get(k, root, 0, h);
    return res != nullptr ? res->value : -1;
  }

private:
  struct node {
    node *ch[8] = {};
    int value = -1;
  };

  int h;
  node *root = nullptr;

  node *immutable_get(int a, node *x, int l, int d) {
    if (x == nullptr) return x;
    if (d == 0) return x;
    int id = (a - l) >> (d - 3);
    return immutable_get(a, x->ch[id], l + (id << (d - 3)), d - 3);
  }

  pair<node *, node *> mutable_get(int a, node *x, int l, int d) {
    x = x != nullptr ? new node(*x) : new node();
    if (d == 0) return make_pair(x, x);
    int id = (a - l) >> (d - 3);
    auto p = mutable_get(a, x->ch[id], l + (id << (d - 3)), d - 3);
    x->ch[id] = p.first;
    return make_pair(x, p.second);
  }
};

// root: O(logN loglogN)
// merge: O(logN loglogN)
struct UnionFind {
  Array uf;

  UnionFind() : uf(0) {}

  UnionFind(int n) : uf(n) {}

  int root(int x) {
    int nd = uf[x];
    if (nd < 0) return x;
    return root(nd);
  }

  void merge(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) return;

    int *u = uf.mutable_get(x);
    int *v = uf.mutable_get(y);
    if (-*u < -*v) swap(u, v), swap(x, y);

    *u += *v;
    *v = x;
  }

  int size(int x) {
    return -uf[root(x)];
  }

  bool query(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) {
      return true;
    } else {
      return false;
    }
  }
};


int main(){
  int N,M; cin >> N >> M;

  vector<UnionFind> ufs(M+1);
  UnionFind uf(N);

  rep(i,M){
    int a,b; scanf("%d%d",&a,&b);
    a--; b--; uf.merge(a,b);
    ufs[i+1] = uf;
  }
  int Q; cin >> Q;
  rep(i,Q){
    int a,b; scanf("%d%d",&a,&b);
    a--; b--;
    if(!ufs[M].query(a,b)){
      cout << "-1" << endl;
      continue;
    }
    int l = 0, r = M, mid;
    while(abs(l-r)>1){
      mid = (l+r)/2;
      if(ufs[mid].query(a,b)) r = mid;
      else l = mid;
    }
    cout << r << endl;
  }
  return 0;
}