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
const int MAX_N = 200005;

ll a[MAX_N],b[MAX_N];

int main(){
  int N; scanf("%d",&N);
  rep(i,N) scanf("%lld",a+i);
  rep(i,N) scanf("%lld",b+i);
  vl a_2(N),b_2(N);
  ll ans = 0LL;
  rep(k,30){
    ll cnt = 0;
    rep(i,N) if((a[i]&(1LL<<k))!=0LL) cnt += ll(N);
    rep(i,N) if((b[i]&(1LL<<k))!=0LL) cnt += ll(N);
    if(k!=0){
      rep(i,N) a_2[i] = a[i] & ((1LL<<k)-1LL);
      rep(i,N) b_2[i] = b[i] & ((1LL<<k)-1LL);
      sort(ALL(a_2)); sort(ALL(b_2));
      rep(i,N){
        ll num = ll(N) - ll(lower_bound(b_2.begin(),b_2.end(),(1LL<<k)-a_2[i]) - b_2.begin()); 
        dump(num);
        cnt += num;
      }
    }
    if(cnt%2) ans ^= (1<<k);
  }
  cout << ans << endl;
  return 0;
}
