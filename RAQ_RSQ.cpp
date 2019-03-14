// #define DEBUG_IS_VALID 

#ifdef DEBUG_IS_VALID
#define DEB 1 
#define _LIBCPP_DEBUG 0
#else
#define DEB 0
#define NDEBUG
#endif

#include "bits/stdc++.h"

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


template <typename T> class RARS {
  const int n;
  FenwickTree<T> bit1, bit2;

public:
  /// @brief
  /// 長さ count の列を作り，全ての要素を 0 で初期化する．
  /// @complexity $O(n)$
  RARS(int count) : n(count), bit1(n + 1), bit2(n + 1) { ; }
  /// @brief
  /// 区間 [l, r) 番目の要素に値 value を加える．
  /// @complexity $O(\\log(n))$
  void update(int l, int r, const T &val) {
    assert(0 <= l && l <= r && r <= n);
    bit1.add(l, -val * l);
    bit2.add(l, val);
    bit1.add(r, val * r);
    bit2.add(r, -val);
  }
  /// @brief
  /// 区間 [l, r) 番目の範囲の和を求める．
  /// @complexity $O(\\log(n))$
  T query(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return bit1.sum(l + 1, r + 1) + bit2.sum(r + 1) * r - bit2.sum(l + 1) * l;
  }
  using value_type = T;
  using update_type = T;
};


void _main(){
  int n, q, com, s, t, x;
  scanf("%d%d", &n, &q);
  RARS<ll> rars(n+1);
  while (q--) {
    scanf("%d", &com);
    if (com) {
      scanf("%d%d", &s, &t);
      printf("%lld\n", rars.query(s, t + 1));
    }
    else {
      scanf("%d%d%d", &s, &t, &x);
      rars.update(s, t + 1, ll(x));
    }
  }
}