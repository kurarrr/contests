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
  int N,M; cin >> N >> M ;
  vector<vector<bool>> graph(N,vector<bool>(N,false));
  rep(i,M){
    int a,b; cin >> a >> b ;
    a--; b--;
    graph[a][b] = graph[b][a] = true;
  }
  vvi cog(N);
  rep(i,N-1) REP(j,i+1,N){
    if(!graph[i][j]){
      cog[i].pb(j); cog[j].pb(i);
    }
  }
  vector<int> color(N,-1);
  vvi x;
  dump(cog);
  vi ss(2);
  function<int(int,int)> dfs = [&](int u,int c){
    dump(u,c);
    color[u] = c;
    ss[c]++;
    c ^= 1;
    int res = 0;
    for(auto v:cog[u]){
      if(color[v]==-1){
        int temp = dfs(v,c);
        if(temp==-1) return -1;
      }else if(color[v]!=c){
        return -1;
      }
    }
    return res;
  };
  rep(i,N){
    if(color[i]!=-1) continue;
    ss[0] = ss[1] = 0;
    int s = dfs(i,0);
    if(s<0){
      cout << "-1" << endl;
      return 0;
    }
    dump(ss);
    vi nxt(2); nxt = ss;
    x.pb(nxt);
  }
  dump(color);
  dump(x);
  bitset<700> dp;
  dp[0] = 1;
  for(auto xx : x){
    dp = (dp<<xx[0]) | (dp<<xx[1]);
  }
  for(int i=N/2;i>=0;i--){
    if(dp[i]){
      cout << i*(i-1)/2+(N-i)*(N-i-1)/2 << endl;
      break;
    }
  }
  return 0;
}