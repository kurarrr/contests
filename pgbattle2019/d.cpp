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
  ll N;
  cin >> N ;
  vl x(N), y(N), z(N), idx(N);
  rep(i,N) cin >> x[i] >> y[i] >> z[i] ;
  iota(ALL(idx), 0LL);
  sort(ALL(idx), [&](ll l,ll r){return z[l]<z[r];});
  set<Pl> st;
  vector<bool> ans(N);
  ll cur_z = -LINF;
  vl cur;
  for(auto i:idx){
    dump(x[i],y[i],z[i]);
    if(cur_z != z[i]){
      // insert
      cur_z = z[i];
      dump(st);
      dump(cur);
      for(auto j:cur){
        auto itr = st.lower_bound(Pl(y[j],-x[j]));
        bool skip;
        if(itr==st.begin()){
          skip = false;
        }else{
          itr--;
          ll x2,y2;
          tie(y2,x2) = *itr; x2 = -x2;
          skip = (x2<=x[j] && y2<=y[j]);
          itr++;
        }
        if(skip) continue;
        while(itr != st.end()){
          ll x2,y2;
          tie(y2,x2) = *itr; x2 = -x2;
          assert(y2>=y[j]);
          if(x2<x[j]) break;
          auto temp = itr;
          itr++;
          st.erase(temp);
        }
        st.insert({y[j],-x[j]});
      }
      cur.clear();
      cur.pb(i);
    }else{
      cur.pb(i);
    }

    auto itr2 = st.lower_bound(Pl(y[i],-x[i]));
    dump(st);
    dump(y[i],x[i]);
    if(itr2==st.begin()){
      ans[i] = false;
    }else{
      itr2--;
      ll x2,y2;
      tie(y2,x2) = *itr2; x2 = -x2;
      ans[i] = (x2<x[i] && y2<y[i]);
    }
  }
  rep(i,N) cout << (ans[i] ? "Yes" : "No") << endl;
  return;
}