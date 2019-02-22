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
template<typename T>ostream& operator << (ostream& os, set<T>& st){cout << "{"; for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : ""); cout << "}"; return os;}
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
    DynamicSegmentTree(long long n) :
        n(1LL << (long long)ceil(log2(n))), root(nullptr) {}
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

void _main(){
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