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

template <typename T>
class FenwickTree {
  const int n;
  vector<T> data;
public:
  FenwickTree(int n) : n(n), data(n, 0) {}
  void add(int i, T value) {
    for (; i < n; i |= i + 1) data[i] += value;
  }
  T sum(int i) const {
    // sum of [0,i]
    T res = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) res += data[i];
    return res;
  }
  // sum of [l,r)
  T sum(int l, int r) const { return sum(r - 1) - sum(l - 1); }
};

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N; cin >> N;
  vi b(N+1),w(N+1);
  rep(i,2*N){
    int a; char c; cin >> c >> a;
    if(c=='B') b[a] = i;
    else w[a] = i;
    // 1-indexed
  }
  vvl dp(N+1,vl(N+1,LINF)),costb(N+1,vl(N+1)),costw(N+1,vl(N+1));
  // costb[i,j] := Bをi個,Wをj個前から並べた時Bのi+1をi+j+1に持ってくるコスト
  // costw[i,j] := Bをi個,Wをj個前から並べた時Wのj+1をi+j+1に持ってくるコスト
  {
    FenwickTree<ll> cnt_b(2*N+1);
    RREP(i,N-1,0){
      FenwickTree<ll> cnt_w(2*N+1);
      RREP(j,N,0){
        // b[i+1]より左にあるiより大なB,jより大なW
        if(i!=N) costb[i][j] = (cnt_b.sum(0,b[i+1]) + cnt_w.sum(0,b[i+1]));
        if(j!=0) cnt_w.add(w[j],1);
      }
      if(i!=0) cnt_b.add(b[i+1],1);
    }
    dump(costb);
  }
  {
    FenwickTree<ll> cnt_w(2*N+1);
    RREP(j,N-1,0){
      FenwickTree<ll> cnt_b(2*N+1);
      RREP(i,N,0){
        // w[j+1]より左にあるiより大なB,jより大なW
        if(j!=N) costw[i][j] = (cnt_b.sum(0,w[j+1]) + cnt_w.sum(0,w[j+1]));
        if(i!=0) cnt_b.add(b[i],1);
      }
      if(j!=0) cnt_w.add(w[j+1],1);
    }
    dump(costw);
  }
  
  dp[0][0] = 0;
  rep(i,N) dp[i+1][0] = dp[i][0] + costb[i][0];
  rep(j,N) dp[0][j+1] = dp[0][j] + costw[0][j];
  rep(i,N) rep(j,N){
    dp[i+1][j+1] = min(dp[i+1][j]+costw[i+1][j],dp[i][j+1]+costb[i][j+1]);
  }
  dump(dp);
  cout << dp[N][N] << endl;
  return 0;
}
