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

const int MAX = 500000, MS = 2;
const long long mod[] = {999999937LL, 1000000007LL}, base = 9973;
struct RollingHash {
  int n;
  vector<long long> hs[MS], pw[MS];
  RollingHash(){}
  RollingHash(const string &s) {
    n = s.size();
    for (int i = 0; i < MS; i++) {
      hs[i].assign(n+1,0);
      pw[i].assign(n+1,0);
      hs[i][0] = 0;
      pw[i][0] = 1;
      for (int j = 0; j < n; j++) {
        pw[i][j+1] = pw[i][j]*base%mod[i];
        hs[i][j+1] = (hs[i][j]*base+s[j])%mod[i];
      }
    }
  }
  long long hash(int l, int r, int i) {
    // i-th hash[l,r)
    return ((hs[i][r]-hs[i][l]*pw[i][r-l])%mod[i]+mod[i])%mod[i];}
  bool match(int l1, int r1, int l2, int r2) {
    bool ret = 1;
    for (int i = 0; i < MS; i++) ret &= hash(l1,r1,i)==hash(l2,r2,i);
    return ret;
  }
  bool match(int l, int r, long long h[]) {
    bool ret = 1;
    for (int i = 0; i < MS; i++) ret &= hash(l,r,i)==h[i];
    return ret;
  }
};

int main(){
  ll H,W; cin >> H >> W ;
  vector<string> temp(H);
  rep(i,H) cin >> temp[i];
  vector<string> s(W,string(H,' '));
  rep(i,H) rep(j,W) s[j][i] = temp[i][j];
  ll N = W;
  vector<RollingHash> roll(N),aaa(26);
  rep(i,N) roll[i] = RollingHash(s[i]);
  rep(i,26) aaa[i] = RollingHash(string(H+1,char('a'+i)));
  ll ans = 0;
  dump(s);
  REP(h,1,(H+2)/3+1) REP(i,0,H){
    int j;
    int a,b,c;
    dump(h);
    if(i-h<0||i+2*h>H) continue;
    for(j = 0; j < W; j++){
      ll now = 0;
      dump(i,j,h);
      if(s[j][i]!=s[j][i+h-1] || s[j][i]==s[j][i-1] || s[j][i]==s[j][i+h]) continue;
      a = s[j][i]-'a'; b = s[j][i-1]-'a'; c = s[j][i+h]-'a';
      while(j<W){
        if(roll[j].hash(i,i+h,0)==aaa[a].hash(0,h,0) && roll[j].hash(i,i+h,1)==aaa[a].hash(0,h,1)
        && roll[j].hash(i-h,i,0)==aaa[b].hash(0,h,0) && roll[j].hash(i-h,i,1)==aaa[b].hash(0,h,1)
        && roll[j].hash(i+h,i+2*h,0)==aaa[c].hash(0,h,0) && roll[j].hash(i+h,i+2*h,1)==aaa[c].hash(0,h,1) ){
          j++;
          now++;
        }else{
          break;
        }
      }
      ans += now*(now+1)/2;
    }
  }
  cout << ans << endl;
  return 0;
}
