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
  int N,M; cin >> N >> M ;
  vector<string> s(N+2);
  s[0] = s[N+1] = string(M+2,'#');
  rep(i,N){
    cin >> s[i+1] ;
    s[i+1] = "#"+s[i+1]+"#";
  }
  ll ans = 0;
  auto rotate = [&](){
    vector<string> nxt(M+2,string(N+2,'.'));
    rep(i,N+2) rep(j,M+2) nxt[M+1-j][i] = s[i][j];
    swap(s,nxt);
    swap(N,M);
  };
  rep(k,4){
    vvl a(N+2,vl(M+2)),asum(N+2,vl(M+2,-1));
    rep(i,N+2) rep(j,M+2){
      if(s[i][j]!='.') a[i][j] = -1;
      else a[i][j] = a[i][j-1] + 1;
    }
    rep(i,N+1) rep(j,M+2){
      if(s[i][j]!='.') asum[i+1][j] = 0;
      else asum[i+1][j] = asum[i][j] + a[i][j];
    }
    REP(i,1,N+1) REP(j,1,M+1) if(s[i][j]=='.') ans += asum[i][j];
    dump(ans);
    rotate();
  }
  cout << ans << endl;
  return 0;
}
