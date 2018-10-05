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

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int H,W; cin >> H >> W ;
  vvl a(H,vl(W));
  rep(i,H) rep(j,W) cin >> a[i][j] ;
  int N = H + W;
  vector<vvl> dp(N-1,vvl(H,vl(H,-1)));
  dp[0][0][0] = a[0][0];
  rep(i,N-2) rep(x1,H) rep(x2,H){
    if(dp[i][x1][x2]==-1) continue;
    rep(s,2) rep(t,2){
      int nx1,ny1,nx2,ny2;
      nx1 = x1+s;
      ny1 = i+1-nx1;
      nx2 = x2+t;
      ny2 = i+1-nx2;
      if(!(nx1<H && ny1<W && nx2<H && ny2<W)) continue;
      if(nx1==nx2 && ny1==ny2) chmax(dp[i+1][nx1][nx2],dp[i][x1][x2]+a[nx1][ny2]);
      else chmax(dp[i+1][nx1][nx2],dp[i][x1][x2]+a[nx1][ny1]+a[nx2][ny2]);
    }
  }
  dump(dp);
  cout << dp[N-2][H-1][H-1] << endl;
  return 0;
}
