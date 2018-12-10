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
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<59; 

int tdp[5002][5002][2];

void _main(){
  int N,K; cin >> N >> K ;
  vi a(N),b(N);
  rep(i,N) cin >> a[i] ;
  rep(i,N) cin >> b[i] ;
  vi par(N);
  rep(i,N){
    a[i]--; b[i]--;
    par[a[i]] = b[i];
  }
  vector<bool> passed(N,false);
  vi ary(N+1);
  auto solve = [&](int s){
    vi graph;
    graph.pb(s);
    int u = par[s];
    passed[s] = true;
    while(u!=s){
      passed[u] = true;
      graph.pb(u);
      u = par[u];
    }
    int sz = graph.size();
    rep(i,sz+1) ary[i] = -INF;
    if(sz==1){
      ary[1] = s+1;
      return sz+1;
    }
    graph.pb(s);
    rep(init,2){
      rep(i,sz) rep(j,sz+1) rep(k,2) tdp[i][j][k] = -INF;
      if(init==0) tdp[0][1][0] = graph[0]+1;
      else tdp[0][1][1] = graph[1]+1;
      rep(i,sz-1) rep(j,sz){
        chmax(tdp[i+1][j+(i<sz-2||init==1)][1],tdp[i][j][1]+graph[i+2]+1);
        chmax(tdp[i+1][j][0],tdp[i][j][1]+graph[i+1]+1);
        chmax(tdp[i+1][j+(i<sz-2||init==1)][1],tdp[i][j][0]+graph[i+2]+1);
        chmax(tdp[i+1][j+1][0],tdp[i][j][0]+graph[i+1]+1);
      }
      // dump(tdp);
      rep(j,sz+1) chmax(ary[j],tdp[sz-1][j][0]);
      rep(j,sz+1) chmax(ary[j],tdp[sz-1][j][1]);
    }
    return sz+1;
  };
  vvi dp(2,vi(N+1,-INF));
  int now = 0;
  int nxt = 1;
  dp[now][0] = 0;
  int ma = 0;
  rep(i,N){
    if(passed[i]) continue;
    int sz = solve(i);
    ma += sz;
    chmin(ma,N+1);
    rep(j,ma) dp[nxt][j] = -INF;
    rep(j,ma) rep(k,sz) if(j-k>=0) chmax(dp[nxt][j],dp[now][j-k]+ary[k]);
    swap(now,nxt);
    dump(dp[now]);
  }
  int ans = -INF;
  REP(j,K,N+1) chmax(ans,dp[now][j]);
  cout << ans << endl;
}