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
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) { os << "{"; for (int i = 0; i<vec.size(); i++) os << vec[i] << (i + 1 == vec.size() ? "" : ", "); os << "}"; return os; }
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
  int N; cin >> N;
  vi x(N),y(N);
  rep(i,N) cin >> x[i];
  rep(i,N) cin >> y[i];
  ll ans = 0LL;
  vi edge;
  RREP(p,51,1){
    vvl g(51,vl(51,LINF));
    rep(i,51) g[i][i] = 0LL;
    // pの辺を貼る必要があるか?
    for(int i:edge){
      rep(u,51) g[u][u%i] = 0LL;
    }
    // p抜きのグラフを構築する
    REP(i,1,p){
      rep(u,51) chmin(g[u][u%i],1LL<<i);
    }
    // Warshall-Floyd
    rep(i,51) rep(j,51) rep(k,51) chmin(g[i][j],g[i][k]+g[k][j]);
    bool check = true, clear = true;
    rep(i,N) check &= (g[x[i]][y[i]] != LINF), clear &= (g[x[i]][y[i]] == 0LL);
    if(clear) break;
    if(!check){
      if(p==51){
        cout << "-1" << endl;
        return 0;
      }else{
        edge.pb(p);
      }
    }
  }
  for(int i:edge) ans |= (1LL << i);
  dump(edge);
  cout << ans << endl;
  return 0;
}
