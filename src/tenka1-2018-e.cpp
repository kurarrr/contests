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
  // int N; cin >> N ;
  int h,w; cin >> h >> w ;
  vector<string> s(h),t(h+w,string(h+w,'.'));
  rep(i,h) cin >> s[i] ;
  rep(i,h) rep(j,w) t[i+j][i-j+w] = s[i][j];
  vvl ssum(h+w,vl(h+w+1));
  rep(i,h+w) rep(j,h+w) ssum[i][j+1] = ssum[i][j]+int(t[i][j]=='#');
  vvl ssum2(h+w+1,vl(h+w));
  rep(i,h+w) rep(j,h+w) ssum2[i+1][j] = ssum2[i][j]+int(t[i][j]=='#');
  ll ans = 0;
  ll a2 = 0;
  rep(i,h+w){
    rep(j,h+w-1) REP(k,j+1,h+w){
      if(t[i][j]=='.'||t[i][k]=='.') continue;
      int d = k-j;
      if(i-d>=0){
        ans += ssum[i-d][k+1] - ssum[i-d][j];
        a2 += int(t[i-d][j]=='#') + int(t[i-d][k]=='#');
      }
      if(i+d<h+w){
        ans += ssum[i+d][k+1] - ssum[i+d][j];
        a2 += int(t[i+d][j]=='#') + int(t[i+d][k]=='#');
      }
    }
  }
  rep(i,h+w){
    rep(j,h+w-1) REP(k,j+1,h+w){
      if(t[j][i]=='.'||t[k][i]=='.') continue;
      int d = k-j;
      if(i-d>=0){
        ans += ssum2[k+1][i-d] - ssum2[j][i-d];
      }
      if(i+d<h+w){
        ans += ssum2[k+1][i+d] - ssum2[j][i+d];
      }
    }
  }
  cout << ans - a2 << endl;
  return 0;
}
