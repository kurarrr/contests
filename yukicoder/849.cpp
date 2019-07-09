#ifdef DEBUG_IS_VALID
#define DEB 1 
#define _LIBCPP_DEBUG 0
#else
#define DEB 0
#define NDEBUG
#endif

#include <bits/stdc++.h>
using namespace std;

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

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vp = vector<Pl>;
using vvp = vector<vp>;

const int INF = 1<<29;
const long long LINF=1LL<<59;

vl gcd2(ll a,ll b,ll c,ll d){
  if(a>c) swap(a,c), swap(b,d);
  if(a==0) return {a,b,c,d};
  // a <= c
  ll r = c/a;
  c -= a * r;
  d -= b * r;
  return gcd2(c,d,a,b);
}

int main(){
  ll a,b,c,d;
  cin >> a >> b >> c >> d ;
  auto xx = gcd2(a,b,c,d);
  a = xx[0]; b = xx[1]; c = xx[2]; d = xx[3];
  if(b<0) b = -b;
  dump(a,b,c,d);
  int N; cin >> N ;
  set<Pl> st;
  rep(i,N){
    ll x,y;
    cin >> x >> y ;
    if(c==0){
      ll g = __gcd(b,d);
      if(g!=0) y %= g;
    }else{
      ll r;
      r = x/c;
      x -= r * c; y -= r * d;
      if(b!=0){
        r = y/b;
        y -= r * b;
        (y += b) %= b;
      }
    }
    st.insert({x,y});
  }
  dump(st);
  cout << st.size() << endl;
  return 0;
}
