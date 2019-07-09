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

int main(){
  ll N;
  cin >> N ;
  vvi g(N);
  rep(i,N-1){
    int a; cin >> a ;
    g[a].pb(i+1);
  }
  ll ans = 0;
  FenwickTree<ll> fw(N);
  function<void(int)> dfs = [&](int u){
    fw.add(u,1LL);
    ans += fw.sum(u);
    for(auto v:g[u]){
      dfs(v);
    }
    fw.add(u,-1LL);
  };
  dfs(0);
  cout << ans << endl;
  return 0;
}
