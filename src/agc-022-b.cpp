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

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N; cin >> N;
  if(N==3){
    cout << "2 5 63" << endl;
    return 0;
  }else if(N==4){
    cout << "2 5 20 63" << endl;
    return 0;
  }
  int a,b;
  if(N%2==1){
    a = min((N/4-1)*4+3,9999);
    b = N - a;
  }else{
    a = min((N-1)/4*4,10000);
    b = N - a;
  }
  REP(i,1,a+1) cout << 3*i << " ";
  int cnt = 0, x = 2;
  while(true){
    if(x%3==0){
      x += 2; continue;
    }else{
      cout << x << (cnt != b-1 ? " ": "") ;
      if(cnt == b-1) break;
      else cnt++;
      x += 2;
    }
  }
  return 0;
}
