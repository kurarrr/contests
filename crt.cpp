#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#pragma GCC optimize ("-O3")

using namespace std;

#define DEBUG_IS_VALID

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
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<59; 

inline long long mod_func(long long a, long long m) {
    return (a % m + m) % m;
}

long long extGcd(long long a, long long b, long long &p, long long &q) {  
    if (b == 0) { p = 1; q = 0; return a; }  
    long long d = extGcd(b, a%b, q, p);  
    q -= a/b * p;  
    return d;  
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
pair<long long, long long> ChineseRem(const vector<long long> &b, const vector<long long> &m) {
  long long r = 0, M = 1;
  for (int i = 0; i < (int)b.size(); ++i) {
    long long p, q;
    long long d = extGcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
    if ((b[i] - r) % d != 0) return make_pair(0, -1);
    long long tmp = (b[i] - r) / d * p % (m[i]/d);
    r += M * tmp;
    M *= m[i]/d;
  }
  return make_pair(mod_func(r, M), M);
}

void _main(){
  vl b(29),m(29);
  iota(m.begin(),m.end(),1);
  rep(i,29) cin >> b[i] ;
  auto p = ChineseRem(b,m);
  if(p.first==0 && p.second==-1){
    cout << "invalid" << endl;
    return;
  }
  ll N = p.first;
  auto dig_sum = [&](ll k){
    ll res = 0;
    ll n = N;
    while(n!=0LL) res += n%k, n /= k;
    return res;
  };
  bool ok = true;
  rep(i,29){
    ok &= (dig_sum(ll(i+2))==b[i]);
  }
  if(N<=1e12 && ok) cout << N << endl;
  else cout << "invalid" << endl;
}