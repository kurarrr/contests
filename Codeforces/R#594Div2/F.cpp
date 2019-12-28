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
  cin.tie(0); ios::sync_with_stdio(false);
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
  ll T, N, M;
  cin >> T ;
  auto sub = [&](const vl& va, const vl& vb){
    cout << "Yes" << endl;
    cout << va.size() << " " << vb.size() << endl;
    rep(i, va.size()) cout << va[i]+1 << (i != va.size()-1 ? " " : "\n");
    rep(i, vb.size()) cout << vb[i]+1 << (i != vb.size()-1 ? " " : "\n");
  };
  rep(t, T){
    cin >> N >> M ;
    vvl g(2 * N);
    ll sz = 2 * N;
    rep(i, M){
      ll a, b;
      cin >> a >> b ;
      a--; b--;
      b += N;
      g[a].pb(b);
      g[b].pb(a);
    }
    vector<bool> pass(N, false);
    function<void(ll)> dfs = [&](ll u){
      pass[u % N] = true;
      for(auto v: g[u]){
        if(pass[v % N]) continue;
        pass[v % N] = true;
        dfs((v+N) % sz);
      }
    };
    dfs(0);
    ll cnt = 0;
    rep(i, N) cnt += ll(pass[i]);
    if(cnt != 0 && cnt != N){
      vl ans_a, ans_b;
      rep(i, N){
        if(pass[i]) ans_a.pb(i);
        else ans_b.pb(i);
      }
      sub(ans_a, ans_b);
      continue;
    }
    rep(i, N) pass[i] = false;
    dfs(N);
    cnt = 0;
    rep(i, N) cnt += ll(pass[i]);
    if(cnt != 0 && cnt != N){
      vl ans_a, ans_b;
      rep(i, N){
        if(pass[i]) ans_b.pb(i);
        else ans_a.pb(i);
      }
      sub(ans_a, ans_b);
      continue;
    }
    cout << "No" << endl;
  }
}