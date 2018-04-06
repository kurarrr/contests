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
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) { os << "{"; for (int i = 0; i<vec.size(); i++) os << vec[i] << (i + 1 == vec.size() ? "" : ", "); os << "}"; return os; }
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
const int MAX_N = 200005;

using sz = ll;

long long maximum_rectangle(const std::vector<sz> &h) {
  // ヒストグラム中の最大長方形
  int n = h.size();
  std::stack<sz> s;
  std::vector<sz> L(n), R(n);
  for (int i = 0; i < n; i++) {
    while (s.size() && h[s.top()] >= h[i]) s.pop();
    L[i] = s.size() ? (s.top() + 1) : 0;
    s.push(i);
  }
  while (s.size()) s.pop();
  for (int i = n - 1; i >= 0; i--) {
    while (s.size() && h[s.top()] >= h[i]) s.pop();
    R[i] = s.size() ? s.top() : n;
    s.push(i);
  }
  long long res = 0;
  for (int i = 0; i < n; i++) {
    res = std::max(res, (long long)h[i] * (R[i] - L[i]));
  }
  return res;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N; cin >> N;
  vector<sz> h(N); rep(i,N) cin >> h[i];
  cout << maximum_rectangle(h) << endl;
  return 0;
}