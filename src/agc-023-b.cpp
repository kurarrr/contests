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

string s[302];
bool ok[604];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N; cin >> N;
  rep(i,N) cin >> s[i];
  int ans = 0;
  rep(i,N){
    // from (i,0)
    fill(ok,ok+604,true);
    // ok := i行はokか
    rep(k,N-1) REP(l,k+1,N){
      ok[(i+k)] &= (s[(i+k)%N][l] == s[(i+l)%N][k]);
    }
    rep(j,N-i){
      // (i+j, j)
      if(j!=0){
        rep(k,N-1){
          // 追加判定
          ok[(i+j+k)] &= (s[(i+j+k)%N][(j+N-1)%N] == s[(i+j+N-1)%N][(j+k)%N]);
        }
      }
      bool is_ok = true;
      rep(k,N-1){
        is_ok &= ok[i+j+k];
      }
      if(is_ok) ans++;
    }
  }
  REP(i,1,N){
    // from (0,i)
    fill(ok,ok+604,true);
    // ok := i行はokか
    rep(k,N-1) REP(l,k+1,N){
      ok[k] &= (s[k][(i+l)%N] == s[l][(i+k)%N]);
    }
    rep(j,N-i){
      // (j, i+j)
      if(j!=0){
        rep(k,N-1){
          // 追加判定
          ok[(j+k)] &= (s[(j+k)%N][(i+j+N-1)%N] == s[(j+N-1)%N][(i+j+k)%N]);
          // dump(i+j+k,ok[i+j+k]);
        }
      }
      bool is_ok = true;
      rep(k,N-1){
        is_ok &= ok[j+k];
      }
      if(is_ok) ans++;
      dump(j,ans);
    }
  }
  cout << ans << endl;
  return 0;
}
