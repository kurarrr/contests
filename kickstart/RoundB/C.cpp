#ifdef DEBUG_IS_VALID
#define DEB 1 
#define _LIBCPP_DEBUG 0
#else
#define DEB 0
#define NDEBUG
#endif

#include <bits/stdc++.h>

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#pragma GCC optimize ("-O3")

using namespace std;

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
  auto solve = [&](){
    ll N,S;
    cin >> N >> S ;
    vl a(N);
    rep(i,N){
      cin >> a[i] ;
    }
    vl b = a;
    sort(ALL(b));
    b.erase(unique(ALL(b)),b.end());
    ll sz = b.size();
    rep(i,N){
      a[i] = ll(lower_bound(ALL(b),a[i])-b.begin());
    }
    ll ans = 0;
    rep(i,N){
      vl cnt(sz);
      ll temp = 0;
      REP(j,i+1,N+1){
        // select [i,j)
        if(cnt[a[j-1]]==-1) continue;
        cnt[a[j-1]]++;
        temp++;
        if(cnt[a[j-1]]==S+1){
          cnt[a[j-1]] = -1;
          temp -= S+1;
        }
        chmax(ans,temp);
      }
    }
    return ans;
  };
  int t; cin >> t ;
  rep(i,t) cout << "Case #" << i+1 << ": " << solve() << endl;
}