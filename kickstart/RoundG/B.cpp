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
#define fi first
#define se second
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
void solve();
int main(void) {
  std::cout << std::fixed << std::setprecision(15);
  solve();
	return 0;
}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vp = vector<Pl>;
using vvp = vector<vp>;

const int INF = (1<<30)-10;
const long long LINF=1LL<<59;

void solve(){
  auto solve = [&](){
    ll N,M;
    cin >> N >> M;
    vl a(N);
    rep(i,N) cin >> a[i] ;
    ll bit = 52;
    // using T = tuple<ll,ll,ll>;
    // using vt = vector<T>;
    // using vvt = vector<vt>;
    // vvt dp(bit+1, vt(2, {0LL, LINF, (1LL << bit)}));
    // dp[bit][0] = {1, 0, 0};
    // for(ll i = bit-1; i >= 0; i--){
    //   ll x = (1LL<<i);
    //   ll s = 0;
    //   rep(j,N) s += ((a[j]&x)^x);
    //   ll d,e,f;
    //   // dump(s);
    //   tie(d, e, f) = dp[i+1][1];
    //   chmax(dp[i][1], {ll(f + s <= M), e ^ x, -(f + s)});
    //   tie(d, e, f) = dp[i+1][0];
    //   chmax(dp[i][1], {ll(f + s <= M), e ^ x, f + s});
    //   // select 0
    //   s = 0;
    //   rep(j,N) s += (a[j]&x);
    //   tie(d, e, f) = dp[i+1][1];
    //   chmax(dp[i][1],{ll(f + s <= M), e, f + s});
    //   tie(d, e, f) = dp[i+1][0];
    //   chmax(dp[i][0],{ll(f + s <= M), e, f + s});
    //   // dump(get<0>(dp[i][0]), get<1>(dp[i][0]), get<2>(dp[i][0]));
    //   // dump(get<0>(dp[i][1]), get<1>(dp[i][1]), get<2>(dp[i][1]));
    // }
    // if(get<0>(dp[0][1])) ans = get<1>(dp[0][1]);
    // else ans = -1;
    vl s1(bit+1);
    vl s2(bit+1);
    ll base = 0;
    ll ans = 0;
    rep(b, bit+1){
      ll x = (1LL << b);
      rep(j,N){
        s1[b] += ((a[j] & x) ^ x);
        s2[b] += (a[j] & x);
      }
      base += min(s1[b], s2[b]);
    }
    if(base > M){ ans = -1; return ans; }
    ll res = M - base;
    for(ll b = bit; b >= 0; b--){
      ll x = (1LL << b);
      if(s1[b] <= s2[b]) ans ^= x;
      else{
        ll dif = s1[b] - s2[b];
        if(res < dif) continue;
        ans ^= x;
        res -= dif; 
      }
    }
    return ans;
  };
  int t; cin >> t ;
  rep(i,t) cout << "Case #" << i+1 << ": " << solve() << endl;
}