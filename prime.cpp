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


// 素数
vector<ll> primes(ll n) {
  // O(n loglog(n))
  // res: sz ~ O(n/log(n))
  vector<bool> is_prime(n,true);
  is_prime[0] = is_prime[1] = false;
  vector<ll> res;
  for(ll i = 2; i <= n; i++){
    if(!is_prime[i]) continue;
    for(ll j = 2; j*i <= n; j++) is_prime[j*i] = false;
    res.push_back(i);
  }
  return res;
}

// 約数の列挙
vector<ll> divisors(ll n) {
  vector<ll> res;
  for(int i=1; i*i<=n; i++) {
    if(n % i == 0) {
      res.push_back(i);
      if(n / i != i) res.push_back(n/i);
    }
  }
  return res;
}

// 素因数の列挙
vector<ll> prime_factors(ll n) {
  vector<ll> res;
  for(ll i=2; i*i<=n; i++) {
    if(n % i == 0) {
      res.push_back(i);
      while(n % i == 0) n /= i;
    }
  }
  if(n != 1) res.push_back(n);
  return res;
}

void _main() {
  int t; cin >> t ;
  auto p = primes(ll(1e3+1));
  rep(i,t){
    ll n; cin >> n ;
    vl ans;
    int sz = min(int(sqrt(double(n)))+1,int(p.size()));
    rep(j,sz) REP(k,j,sz){
      ll s = p[j];
      ll t = p[k];
      ll temp2 = n-ll(s*s)-ll(t*t);
      ll temp = ll(sqrt(double(temp2)));
      if(temp*temp!=temp2) continue;
      if(!is_prime[temp]) continue;
      if(!(s*s+t*t+temp*temp==n)) continue;
      vl x = {s,t,temp};
      sort(ALL(x));
      ans.pb(x[0]*ll(1e6)+x[1]*ll(1e3)+x[2]);
    }
    sort(ALL(ans));
    ans.erase(unique(ALL(ans)),ans.end());
    cout << ans.size() << endl;
  }
}
