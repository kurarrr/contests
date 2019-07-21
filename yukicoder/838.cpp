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

const int INF = 1<<29;
const long long LINF=1LL<<59;

void solve(){
  ll N; cin >> N ;
  vl y(N), s(N+1);
  rep(i,N) cin >> y[i] ;
  sort(ALL(y));
  if(N==2){
    cout << y[1]-y[0] << endl;
    return;
  }
  ll ans = LINF;
  vector<vvl> dp(N,vvl(3,vl(3,LINF)));
  dp[1][0][1] = y[1] - y[0];
  auto cost = [&](int i, int l){
    ll c;
    if(i+1==N && l==0) return LINF;
    if(l==0) c = y[i+1] - y[i];
    if(l==1) c = 0;
    if(l==2) c = y[i] - y[i-1];
    return c;
  };
  REP(i,2,N){
    rep(l,3) chmin(dp[i][1][l], dp[i-1][0][1] + cost(i,l));
    rep(l,2) chmin(dp[i][2][l], dp[i-1][1][2] + cost(i,l));
    chmin(dp[i][0][1],dp[i-1][1][0]+cost(i,1));
    chmin(dp[i][1][2],dp[i-1][1][1]+cost(i,2));
    chmin(dp[i][1][2],dp[i-1][2][1]+cost(i,2));
    chmin(dp[i][0][1],dp[i-1][2][0]+cost(i,1));
  }
  cout << dp[N-1][1][2] << endl;
}