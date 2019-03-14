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
const double EPS=1e-5,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<59; 

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F

int log2ceil(int n) { --n; n |= n >> 16; n |= n >> 8; n |= n >> 4; n |= n >> 2; n |= n >> 1; return n + 1;}
int log2ceil(long long n) { --n; n |= n >> 32; n |= n >> 16; n |= n >> 8; n |= n >> 4; n |= n >> 2; n |= n >> 1; return n + 1;}

template <typename Struct> class SegmentTreeLazy {
public:
  using Monoid = typename Struct::Monoid;
  using Update = typename Struct::Update;
  using value_type = typename Struct::value_type;
  using update_type = typename Struct::update_type;

private:
  const int n;
  std::vector<value_type> data;
  std::vector<update_type> lazy;
  std::vector<bool> flag;
  void lazyset(int node, const update_type &update) {
    if (node < n) {
      if (flag[node]) {
        lazy[node] = Update::op(update, lazy[node]);
      }
      else {
        lazy[node] = update;
        flag[node] = true;
      }
    }
    data[node] = Struct::evaluate(update, data[node]);
  }
  void evaluate(int node) {
    if (!flag[node]) return;
    flag[node] = false;
    lazyset(node * 2 + 0, lazy[node]);
    lazyset(node * 2 + 1, lazy[node]);
  }
  void update_sub(int l, int r, int node, int lb, int ub,
                  const update_type &update) {
    if (ub <= l || r <= lb) {
      return;
    }
    if (l <= lb && ub <= r) {
      lazyset(node, update);
      return;
    }
    evaluate(node);
    const int mid = (lb + ub) / 2;
    update_sub(l, r, node * 2 + 0, lb, mid, update);
    update_sub(l, r, node * 2 + 1, mid, ub, update);
    data[node] = Monoid::op(data[node * 2 + 0], data[node * 2 + 1]);
  }
  value_type query_sub(int l, int r, int node, int lb, int ub) {
    if (ub <= l || r <= lb) return Monoid::id();
    if (l <= lb && ub <= r) {
      return data[node];
    }
    evaluate(node);
    const int mid = (lb + ub) / 2;
    value_type lval = query_sub(l, r, node * 2 + 0, lb, mid);
    value_type rval = query_sub(l, r, node * 2 + 1, mid, ub);
    return Monoid::op(lval, rval);
  }

public:
  SegmentTreeLazy(int count, const value_type &init = Monoid::id()) :
    n(log2ceil(count)), data(n * 2), lazy(n), flag(n, false) {
    fill(begin(data) + n, end(data), init);
    for (int i = n - 1; i >= 1; i--) {
      data[i] = Monoid::op(data[i * 2 + 0], data[i * 2 + 1]);
    }
  };
  void update(int l, int r, const update_type &f) {
    update_sub(l, r, 1, 0, n, f);
  }
  value_type query(int l, int r) { return query_sub(l, r, 1, 0, n); }
};

template <typename T> struct LeftHandSide {
  using value_type = T;
  static value_type op(const value_type &l, const value_type &) { return l; }
};
struct RMQ{
  using type = ll;
  static type id(){return LINF;}
  static type op(const type &a ,const type &b){return min(a,b);}
};
struct RangeUpdateRMQ {
  using Monoid = RMQ;
  using Update = LeftHandSide<long long>;
  using value_type = ll;
  using update_type = typename Update::value_type;
  static value_type evaluate(const update_type &update, const value_type &) {
    return update;
  }
};


void _main(){
  int n, q, com, s, t, x;
  scanf("%d%d", &n, &q);
  SegmentTreeLazy<RangeUpdateRMQ> seg(n, (1LL<<31)-1);
  while (q--) {
    scanf("%d", &com);
    if (com) {
      scanf("%d%d", &s, &t);
      printf("%lld\n", seg.query(s, t + 1));
    }
    else {
      scanf("%d%d%d", &s, &t, &x);
      seg.update(s, t + 1, x);
    }
  }
}