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

struct UnionFindTree{
  vector<int> par,rank,size;
  UnionFindTree(int N){
    par = rank = vector<int>(N,0);
    size = vector<int>(N,1);
    for(int i = 0; i < N; i++) par[i] = i;
  }
  int find(int x){
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
  }
  void unite(int x,int y){
    x = find(x);
    y = find(y);
    if(x == y)  return ;
    if(rank[x] < rank[y]){
      par[x] = y;
    }else{
      par[y] = x;
      if(rank[x] == rank[y]) ++rank[x];
    }
    size[x] = size[y] = size[x] + size[y];
  }
  bool same(int x,int y){
    return find(x) == find(y);
  }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  ll N,M,Q; cin >> N >> M >> Q ;
  ll sp_sz;
  if(M%7==0) sp_sz = M;
  else sp_sz = 7 * M;
  vector<bool> is_black(sp_sz,false);
  rep(i,Q){
    int a; cin >> a ;
    for(int x = a; x < sp_sz ; x += M){
      is_black[x] = true;
    }
  }
  UnionFindTree uft(sp_sz*2);
  vi dx = {-1,0,1,0};
  vi dy = {0,-1,0,1};
  rep(i,sp_sz){
    if(is_black[i]) continue;
    rep(j,4){
      int x = i + dx[j]*7 + dy[j];
      if(x<0 || x>=sp_sz) continue;
      if((j%2==1)&&(i/7!=x/7)) continue;
      if(is_black[x]) continue;
      uft.unite(i,x);
      uft.unite(i+sp_sz,x+sp_sz);
    }
  }
  ll sz1,sz2;
  sz1 = sz2 = 0;
  rep(i,sp_sz){
    if(is_black[i]) continue;
    if(uft.par[i]==i) sz1++;
  }
  REP(i,sp_sz-7,sp_sz){
    if(is_black[i]||is_black[(i+7)%sp_sz]) continue;
    uft.unite(i,i+7);
  }
  rep(i,2*sp_sz){
    if(is_black[i%sp_sz]) continue;
    if(uft.par[i]==i) sz2++; 
  }
  dump(is_black);
  dump(sz1,sz2);
  ll diff = sz1 * 2 - sz2;
  ll temp = 7LL*N/sp_sz;
  cout << sz1 * temp - diff * (temp-1) << endl;
  return 0;
}
