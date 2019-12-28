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
#define fi first
#define se second
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
void solve();
int main(void) {
  std::cout << std::fixed << std::setprecision(15);
  solve();
	return 0;
}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vp = vector<Pl>;
using vvp = vector<vp>;

const int INF = (1<<30)-10;
const long long LINF=1LL<<59;

ll N, H;
vl a, b;

ll solve2rec(ll cur, int idx, int s, int rest){
  if(idx == N) return 0;
  if(((s>>idx) & 1LL) == 0LL) return solve2rec(cur, idx+1, s, rest);
  ll res = 0;
  // attend
  ll nxt = cur + b[idx];
  if(nxt >= H) res += (1LL<<(rest-1));
  else res += solve2rec(nxt, idx+1, s, rest - 1);
  // not attend
  res += solve2rec(cur, idx+1, s, rest - 1);
  return res;
}

ll solve2(int s){
  ll scr = 0;
  ll cnt = 0;
  rep(i, N){
    // B must attend
    if(((s>>i) & 1) == 0){
      scr += b[i];
      cnt++;
    }
  }
  if(scr >= H) return (1LL << (N - cnt)); // arbitrary
  return solve2rec(scr, 0LL, s, N - cnt);
}

ll solve1(){
  ll res = 0;
  {
    // sort desc order of b
    vi idx(N);
    iota(ALL(idx), 0);
    sort(ALL(idx), [&](int l, int r){ return b[l] > b[r];});
    vl temp(N);
    rep(i,N) temp[idx[i]] = a[i];
    a = temp;
    rep(i,N) temp[idx[i]] = b[i];
    b = temp;
  }
  rep(s, 1<<N){
    ll scr = 0;
    rep(i, N) if((s>>i) & 1LL) scr += a[i];
    if(scr < H) continue;
    res += solve2(s); 
  }
  return res;
}

void solve(){
  auto solve = [&](){
    cin >> N >> H;
    a.resize(N);
    b.resize(N);
    rep(i,N) cin >> a[i] ;
    rep(i,N) cin >> b[i] ;
    return solve1();
  };
  int t; cin >> t ;
  rep(i,t) cout << "Case #" << i+1 << ": " << solve() << endl;
}