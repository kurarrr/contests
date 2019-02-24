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
  int N; cin >> N ;
  vector<vector<P>> g(N);
  rep(i,N-1){
    int s,t,w; cin >> s >> t >> w ;
    g[s].pb(P(t,w));
    g[t].pb(P(s,w));
  }
  vi dp(N);
  int root = 0;
  function<void(int,int)> dfs1 = [&](int u,int p){
    int v,d;
    for(auto&& pp:g[u]){
      tie(v,d) = pp;
      if(v==p) continue;
      dfs1(v,u);
      chmax(dp[u],dp[v]+d);
    }
  };
  dfs1(root,-1);
  function<int(int,int,int)> dfs2 = [&](int u,int p,int d_par){
    vector<P> d_child; // val,node
    d_child.pb(P(0,-1));
    int v,d;
    for(auto&& pp:g[u]){
      tie(v,d) = pp;
      if(v==p) d_child.pb(P(d_par+d,v));
      else d_child.pb(P(dp[v]+d,v));
    }
    sort(ALL(d_child));
    reverse(ALL(d_child));
    P ff,ss;
    int res = d_child[0].first + d_child[1].first;
    ff = d_child[0];
    ss = d_child[1];
    vector<P> ().swap(d_child); //destruct
    for(auto&& pp:g[u]){
      tie(v,d) = pp;
      if(v==p) continue;
      if(ff.second==v){
        chmax(res,dfs2(v,u,ss.first));
      }else{
        chmax(res,dfs2(v,u,ff.first));
      }
    }
    return res;
  };
  cout << dfs2(root,-1,0) << endl;
}