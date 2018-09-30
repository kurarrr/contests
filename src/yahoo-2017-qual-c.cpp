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
template<typename T>ostream& operator << (ostream& os, set<T>& st){for(auto itr = st.begin(); itr != st.end(); itr++) cout << *itr << (next(itr)!=st.end() ? ", " : ""); cout << "}"; return os;}
template<typename T1,typename T2>ostream& operator << (ostream& os, map<T1,T2> mp){cout << "{"; for(auto itr = mp.begin(); itr != mp.end(); itr++) cout << "(" << (itr->first) << ", " << (itr->second) << ")" << (next(itr)!=mp.end() ? "," : ""); cout << "}"; return os; }

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

string prefix(string a1,string a2){
  int sz = min(a1.size(),a2.size());
  string pre = a1;
  if(sz<pre.size()) pre.erase(sz,pre.size());
  rep(j,sz){
    if(pre[j]==a2[j]) continue;
    pre.erase(j,sz);
    break;
  }
  return pre;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N,K; cin >> N >> K;
  vi a(K);
  rep(i,K){
    cin >> a[i]; a[i]--;
  }
  vector<string> s(N),s2;
  rep(i,N){
    cin >> s[i];
  }
  sort(ALL(a));
  string pre = s[a[0]];
  REP(i,1,K){
    // 共通接頭辞
    int sz = min(pre.size(),s[a[i]].size());
    if(sz<pre.size()) pre.erase(sz,pre.size());
    rep(j,sz){
      if(pre[j]==s[a[i]][j]) continue;
      pre.erase(j,sz);
      break;
    }
  }
  int now = 0;
  rep(i,N){
    if(now!=K && i==a[now]){
      now++;
    }else{
      s2.pb(s[i]);
    }
  }
  s2.pb(pre);
  if(s2.size()==1){
    cout << "" << endl;
    return 0;
  }
  sort(ALL(s2));
  int arg_pre = -1;
  rep(i,s2.size()){
    if(s2[i]==pre){
      if(arg_pre==-1) arg_pre = i;
      else arg_pre = -2;
    }
  }
  if(arg_pre==-2){
    cout << "-1" << endl;
    return 0;
  }
  string a1,a2;
  if(arg_pre!=0) a1 = s2[arg_pre-1];
  else a1 = "11";
  string a3 = prefix(pre,a1);
  if(arg_pre!=s2.size()-1) a2 = s2[arg_pre+1];
  else a2 = "22";
  string a4 = prefix(pre,a2);
  if(a3==pre || a4==pre){
    cout << "-1" << endl;
    return 0;
  }
  string ans;
  if(a3.size()>a4.size()) ans = a3;
  else ans = a4;
  ans.pb(pre[ans.size()]);
  cout << ans << endl;
  return 0;
}
