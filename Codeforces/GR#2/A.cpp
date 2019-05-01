#ifdef DEBUG_IS_VALID
#define DEB 1 
#define _LIBCPP_DEBUG 0
#else
#define DEB 0
#define NDEBUG
#endif

#include <bits/stdc++.h>

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

void _main(){
  ll N;
  cin >> N ;
  vvl node(N);
  vl c(N),mi(N),ma(N);
  rep(i,N){
    cin >> c[i] ;
    c[i]--; node[c[i]].pb(i);
  }
  rep(i,N){
    if(node[i].size()){
      mi[i] = *min_element(ALL(node[i]));
      ma[i] = *max_element(ALL(node[i]));
    }else{
      mi[i] = LINF;
      ma[i] = -LINF;
    }
  }
  vl mi1(N+1,LINF),mi2(N+1,LINF),ma1(N+1,-LINF),ma2(N+1,-LINF);
  rep(i,N){
    mi1[i+1] = min(mi1[i],mi[i]);
    ma1[i+1] = max(ma1[i],ma[i]);
  }
  rrep(i,N-1){
    mi2[i] = min(mi2[i+1],mi[i]);
    ma2[i] = max(ma2[i+1],ma[i]);
  }
  ll ans = 0;
  rep(i,N){
    ll m1 = min(mi1[c[i]],mi2[c[i]+1]);
    ll m2 = max(ma1[c[i]],ma2[c[i]+1]);
    chmax(ans,abs(i-m1));
    chmax(ans,abs(i-m2));
  }
  cout << ans << endl;
}