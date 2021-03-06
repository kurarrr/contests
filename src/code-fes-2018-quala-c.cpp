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
template<typename T>ostream& operator << (ostream& os, set<T>& st){for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : ""); cout << "}"; return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : ""); cout << "}"; return os; }

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

const int mod=1e9+7,INF=1<<29;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<59; 

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  ll N,K; cin >> N >> K ;
  vl a(N);
  rep(i,N){
    cin >> a[i] ;
  }
  K = min(K,60*N);
  vvl dp1(N+1,vl(K+1)),dp2(N+1,vl(K+1));
  dp1[0][0] = 1LL;
  REP(i,0,N){
    rep(j,K+1){
      ll temp = a[i];
      int k;
      for(k = 0; k < j+1; k++){
        // a_iをk回操作する
        if(temp==0LL) break;
        (dp1[i+1][j] += dp1[i][j-k]) %= lmod;
        temp /= 2;
      }
      temp = a[i];
      for(k = 0; k < j+1; k++){
        // a_iをk回操作する
        (dp2[i+1][j] += dp2[i][j-k]) %= lmod;
        if(temp==0LL) break;
        temp /= 2;
      }
      dump(j,k,temp);
      if(temp!=0LL) continue;
      if(j-k>=0) (dp2[i+1][j] += dp1[i][j-k]) %= lmod;
    }
  }
  dump(dp1,dp2);
  ll ans = dp1[N][K];
  rep(k,K+1) (ans += dp2[N][k]) %= lmod;
  cout << ans << endl;
  return 0;
}