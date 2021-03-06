#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

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
template<typename T>ostream& operator << (ostream& os, set<T>& st){for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : "\n"); return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : "}\n"); return os; }

void dump_func(){DUMPOUT << endl;}
template <class Head, class... Tail>void dump_func(Head&& head, Tail&&... tail){ DUMPOUT << head; if (sizeof...(Tail) == 0) { DUMPOUT << " "; } else { DUMPOUT << ", "; } dump_func(std::move(tail)...);}
template<class T> inline void chmax(T& a,T const& b){a=max(a,b);}
template<class T> inline void chmin(T& a,T const& b){a=min(a,b);}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60; 

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  ll H,W,N,M; cin >> H >> W >> N >> M;
  vector<string> a(N); rep(i,N) cin >> a[i];
  vi x_dec, y_dec;
  rep(i,N) rep(j,M){
    x_dec.pb(i); x_dec.pb(H-N+i+1);
    y_dec.pb(j); y_dec.pb(W-M+j+1);
  }
  sort(ALL(x_dec)); x_dec.erase(unique(x_dec.begin(),x_dec.end()),x_dec.end());
  sort(ALL(y_dec)); y_dec.erase(unique(y_dec.begin(),y_dec.end()),y_dec.end());
  int mx = x_dec.size(); int my = y_dec.size();
  map<ll,int> x_enc, y_enc;
  rep(i,mx) x_enc[x_dec[i]] = i;
  rep(j,my) y_enc[y_dec[j]] = j;

  vvi s(mx+1,vi(my+1));
  rep(i,N) rep(j,M){
    if(a[i][j]=='.') continue;
    int x1 = x_enc[i];
    int y1 = y_enc[j];
    int x2 = x_enc[H-N+i+1];
    int y2 = y_enc[W-M+j+1];
    s[x1][y1]++; s[x2][y1]--; s[x1][y2]--; s[x2][y2]++;
  }
  rep(i,mx-1) rep(j,my) s[i][j+1] += s[i][j];
  rep(i,mx) rep(j,my-1) s[i+1][j] += s[i][j];
  ll ans = 0LL;
  dump(x_dec,y_dec);
  dump(s);
  rep(i,mx-1) rep(j,my-1){
    if(s[i][j]!=0) ans += ll(x_dec[i+1] - x_dec[i]) * ll(y_dec[j+1] - y_dec[j]);
  }
  cout << ans << endl; 
  return 0;
}
