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

void _main(){
  int N,M,K; cin >> N >> M >> K ;
  vvi graph(N);
  int root;
  rep(i,N){
    int p; cin >> p ;
    if(p==0) root = i;
    else{
      p--;
      graph[p].pb(i);
      graph[i].pb(p);
    }
  }
  vi depth0(N,-1);
  function<void(int,vi&,int)> dfs = [&](int u,vi& depth,int imp){
    for(auto v:graph[u]){
      if(depth[v]!=-1) continue;
      if(v==imp) continue;
      depth[v] = depth[u] + 1;
      dfs(v,depth,imp);
    }
  };
  depth0[root] = 0;
  dfs(root,depth0,-1);
  vi ans(M);
  int rest = K - M; // 残りのoperation
  vector<bool> used(N,false);
  rep(i,M){
    dump(graph);
    int loc = -1;
    rep(j,N){
      if(used[j]) continue;
      vi d(N,-1);
      d[root] = 0;
      if(root!=j) dfs(root,d,j);
      int op = depth0[j];
      int rest2 = rest - op;
      vi s;
      rep(k,N) if(d[k]!=-1) s.pb(d[k]);
      dump(d,s);
      if(s.size()<M-i-1) continue;
      sort(ALL(s));
      dump(d,s);
      int mi(0),ma(0);
      rep(k,M-i-1) mi += s[k];
      REP(k,s.size()-(M-i-1),s.size()) ma += s[k];
      dump(j,mi,rest2,ma,M-i-1);
      if(!(mi<=rest2 && rest2<=ma)) continue;
      loc = j;
      dump(i,loc);
      rest = rest2;
      rep(k,N) if(d[k]==-1) used[k] = true;
      break;
    }
    if(loc==-1){
      cout << "-1" << endl;
      return;
    }
    ans[i] = loc;
    used[loc] = true;
    // 木を切る
    if(loc!=root){
      graph[loc].clear();
      rep(j,N){
        auto itr = find(graph[j].begin(),graph[j].end(),loc);
        if(itr!=graph[j].end()) graph[j].erase(itr,itr+1);
      }
    }
  }
  dump(ans);
  rep(i,M) cout << ans[i]+1 << (i!=M-1 ? " " : "\n");
}