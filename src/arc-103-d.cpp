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
  int N; cin >> N ;
  vl x(N),y(N);
  rep(i,N) cin >> x[i] >> y[i] ;
  bool is_even = ((x[0]+y[0]) % 2 == 0);
  bool ok = true;
  rep(i,N) ok &= (is_even == ((x[i]+y[i])%2)==0);
  if(!ok){
    cout << "-1" << endl;
    return 0;
  }
  int ma_sz = 30;
  ll ma = (1LL<<ma_sz);
  if(is_even){
    cout << ma_sz + 2 << endl;
    ll temp = 1;
    cout << "1 ";
    rep(i,ma_sz+1){
      cout << temp << ((i!=ma_sz) ? " " : "\n");
      temp <<= 1;
    }
  }else{
    cout << ma_sz + 1 << endl;
    ll temp = 1;
    rep(i,ma_sz+1){
      cout << temp << ((i!=ma_sz) ?  " " :  "\n");
      temp <<= 1;
    }
  }
  vl dx = {-1,0,1,0};
  vl dy = {0,-1,0,1};
  string di = "RULD";
  string ans;
  function<void(ll,ll,int)> solve = [&](ll xs,ll ys,int sz){
    dump(xs,ys,sz);
    if(xs==0LL && ys==0LL && sz<=-1) return;
    ll mma = LINF;
    int arg = -1;
    if(is_even && sz==-1) sz++;
    rep(i,4) arg = (chmin(mma,abs(xs+dx[i]*(1LL<<sz))+abs(ys+dy[i]*(1LL<<sz))) ? i : arg);
    solve(xs+dx[arg]*(1LL<<sz),ys+dy[arg]*(1LL<<sz),sz-1);
    ans += di[arg];
    return ;
  };
  rep(i,N){
    ans = "";
    solve(x[i],y[i],ma_sz);
    cout << ans << endl;
  }
  return 0;
}
