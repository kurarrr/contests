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

int main(){
  ll N; string s;
  cin >> N ;
  cin >> s ;
  vl right(N+1);
  vi ans;
  int now = 0;
  rrep(i,N-1){
    if(s[i]!='0'){
      now = N-i;
    }
    right[i] = now;
  }
  ll ma = LINF;
  rep(i,N){
    if(right[i]!=N-i) continue;
    ll nxt = max(ll(i),right[i]);
    if(nxt<ma){
      ans.clear();
      ans.pb(i);
      ma = nxt;
    }else if(nxt==ma) ans.pb(i);
  }
  dump(right);
  dump(ma);
  dump(ans);
  vector<string> temp;
  for(auto i:ans){
    string x(ma,'0'); // s[0,i)+s[i,N)
    int now = 0;
    int l = i-1; int r = N-1;
    int tal = ma-1;
    while(l>=0 || r>=i){
      int u = (l>=0 ? int(s[l]-'0'):0);
      int v = (r>=i ? int(s[r]-'0'):0);
      dump(tal);
      x[tal--] = char('0'+((u+v+now)%10));
      if(u+v+now>=10) now=1;
      else now = 0;
      dump(l,r,u,v);
      l--; r--;
    }
    if(now) x = "1"+x;
    temp.pb(x); 
  }
  sort(ALL(temp));
  cout << temp[0] << endl;
  dump(temp);
  return 0;
}
