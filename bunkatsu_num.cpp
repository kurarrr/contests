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

vvl cut_num(1003,vl(102)); // 分割数

void init_cut_num(int N, int K){
  rep(i,N) cut_num[i][1] = 1LL;
  rep(j,K) cut_num[0][j] = 1LL;
  rep(i,N) REP(j,2,K) cut_num[i][j] = (cut_num[i][j-1] + (i-j>=0 ? cut_num[i-j][j] : 0LL)) % lmod;
}

ll solve(vi& num,ll all){
  int sz = num.size();
  vvl dp(sz+1,vl(all+1));
  dp[0][0] = 1LL;
  REP(i,1,sz+1) rep(j,all+1) REP(k,0,j+1) (dp[i][j] += dp[i-1][j-k] * cut_num[k][num[i-1]]) %= lmod;
  dump(dp);
  return dp[sz][all];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N,M; cin >> N >> M;
  vi kA(N),kB(M);
  rep(i,N) cin >> kA[i];
  rep(i,M) cin >> kB[i];
  init_cut_num(1001,101);
  vi numA,numB;
  ll now = -1LL;
  rep(i,N){
    int sz = numA.size();
    if(now==kA[i]){
      numA[sz-1]++;
    }else{
      numA.pb(1);
      now = kA[i];
    }
  }
  now = -1LL;
  rep(i,M){
    int sz = numB.size();
    if(now==kB[i]){
      numB[sz-1]++;
    }else{
      numB.pb(1);
      now = kB[i];
    }
  }
  dump(numA,numB);
  ll a = 0, b = 0;
  rep(i,N) a += kA[i];
  rep(i,M) b += kB[i];
  cout << solve(numA,b) * solve(numB,a) % lmod << endl;
  return 0;
}
