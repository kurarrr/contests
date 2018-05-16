#include "bits/stdc++.h"
// Wrong Answer

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
  vl a(N);
  bool all_minus = true;
  rep(i,N){
    cin >> a[i];
    all_minus &= (a[i] < 0LL);
  }
  if(all_minus){
    int argma; ll ma = -LINF;
    rep(i,N){
      if(a[i]>ma) ma = a[i], argma = i;
    }
    cout << ma << endl;
    cout << N-1 << endl;
    rep(i,argma) cout << "1" << endl;
    RREP(i,N-argma,2) cout << i << endl;
    return 0;
  }
  ll even = 0LL, odd = 0LL;
  for(int i = 0; i < N; i += 2){
    if(a[i]>0LL) even += a[i]; 
  }
  for(int i = 1; i < N; i += 2){
    if(a[i]>0LL) odd += a[i]; 
  }
  vi ans;
  bool is_even = true;
  if(even<odd) is_even = false;
  cout << (is_even ? even : odd) << endl;
  while(true){
    bool update = false;
    for(int i = (is_even ? 0 : 1); i < a.size() ; i += 2){
      if(a[i] < 0){
        ans.pb(i+1);
        if(i==0||i==a.size()-1) a.erase(a.begin()+i);
        else{
          a.erase(a.begin()+i-1);
          a.erase(a.begin()+i);
        }
        update = true;
        break;
      }
    }
    if(!update) break;
  }
  dump(ans,a,is_even);
  if(!is_even){
    if(a.size()%2==1) ans.pb(a.size()); 
    ans.pb(1);
    rep(i,(a.size())/2-1) ans.pb(2);
  }else{
    if(a.size()%2==0) ans.pb(a.size());
    rep(i,(a.size()-1)/2) ans.pb(2);
  }
  dump(ans);
  cout << ans.size() << endl;
  for(int i:ans) cout << i << endl;
  return 0;
}
