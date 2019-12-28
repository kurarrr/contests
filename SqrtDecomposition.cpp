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
const double EPS=1e-5,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<59; 

const int sqrtN = 512;
struct SqrtDecomposition {
  int N, K;
  vector<ll> data;
  vector<bool> lazyFlag;
  vector<ll> lazyUpdate;
  SqrtDecomposition(int n) : N(n) {
    K = (N + sqrtN - 1) / sqrtN;
    data.assign(K * sqrtN, 0);
    lazyFlag.assign(K, false);
    lazyUpdate.assign(K, 0);
  }
  void eval(int k) {
    if (lazyFlag[k]) {
      lazyFlag[k] = false;
      for (int i = k * sqrtN; i < (k + 1) * sqrtN; ++i) {
        data[i] = lazyUpdate[k];
      }
    }
  }
  // update [s, t)
  void update(int s, int t, ll x) {
    for (int k = 0; k < K; ++k) {
      int l = k * sqrtN, r = (k + 1) * sqrtN;
      if (r <= s || t <= l)
        continue;
      if (s <= l && r <= t) {
        lazyFlag[k] = true;
        lazyUpdate[k] = x;
      } else {
        eval(k);
        for (int i = max(s, l); i < min(t, r); ++i) {
          data[i] = x;
        }
      }
    }
  }
  ll find(int i) {
    int k = i / sqrtN;
    eval(k);
    return data[i];
  }
};

void _main(){
  int N,M; cin >> N >> M ;
  vl t(M),l(M),r(M);
  rep(i,M) cin >> t[i] >> l[i] >> r[i] ;
  SqrtDecomposition sq(262144);
  // SqrtDecomposition sq(N+1);
  rep(i,M){
    sq.update(l[i],r[i]+1,t[i]);
  }
  ll ans = 0;
  rep(i,N){
    ans += ll(sq.find(i+1));
  }

  cout << ans << endl;
}