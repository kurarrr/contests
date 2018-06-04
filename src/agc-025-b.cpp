#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back

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
template<typename T>ostream& operator << (ostream& os, set<T>& st){for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : "\n"); return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : "}\n"); return os; }

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
const ll lmod = 998244353,LINF=1LL<<60; 

vector<ll> fact;

void init(ll N){
  fact.resize(N+1);
  fact[0]=1;
  rep(i,N) fact[i+1]=((i+1)*fact[i])%lmod;
}

ll ppow(ll a,ll b){
  // aのb乗を求める
  ll res = 1;
  while(b){
    if(b%2) res=(res*a)%lmod;
    a=(a*a)%lmod;
    b>>=1;
  }
  return res;
}

ll imod(ll n){
  // nのmodの逆元を求める
  ll P=lmod;
  return ppow(n,P-2);
}

ll comb_mod(ll n,ll k){
  //nまで埋めた階乗テーブルを渡す
  if(k>n) return 0;
  else return (fact[n] * imod(fact[k]) % lmod) * imod(fact[n-k]) % lmod ;
  //nCk % mod を返す
}


int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  ll N,A,B,K;
  cin >> N >> A >> B >> K;
  ll ans = 0LL;
  init(N+2);
  for(ll a = 0; a <= N; a++){
    ll b = K - a * A;
    if(b<0) break;
    if(b%B!=0LL) continue;
    else b /= B;
    ans = (ans + comb_mod(N,a) * comb_mod(N,b)) % lmod;
  }
  cout << ans << endl;
  return 0;
}
