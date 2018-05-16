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

bool passed[16][16][4][16][16];

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int a,b,h,w; cin >> a >> b >> h >> w;
  string s[16];
  rep(i,h) cin >> s[i];
  using T = tuple<int,int,int,int,int>;
  // y,x,向き(北東南西),a,b
  int dx[4] = {0,1,0,-1};
  int dy[4] = {-1,0,1,0};
  queue<T> que;
  que.push(T(1,1,2,0,0));
  rep(i,16) rep(j,16) rep(k,4) rep(l,16) rep(m,16) passed[i][j][k][l][m] = false;
  int cnt = 0;
  passed[1][1][2][0][0] = true;
  while(!que.empty()){
    int y,x,m,aa,bb;
    if(cnt==1000000) break;
    que.pop();
    if(y==h-2 && x==w-2 && aa==a && bb==b){
      cout << "Yes" << endl;
      return 0;
    }
    if((s[y+dy[m]][x+dx[m]]!='#') && (!passed[y+dy[m]][x+dx[m]][m][aa][bb])){
      que.push(T(y+dy[m],x+dx[m],m,aa,bb));
      passed[y+dy[m]][x+dx[m]][m][aa][bb] = true;
    }
    int usea = (m-1+4)%4;
    if(aa<a && (s[y+dy[usea]][x+dx[usea]]!='#') && (!passed[y+dy[usea]][x+dx[usea]][usea][aa+1][bb])){
      que.push(T(y+dy[usea],x+dx[usea],usea,aa+1,bb));
      passed[y+dy[usea]][x+dx[usea]][usea][aa+1][bb] = true;
    }
    int useb = (m+1)%4;
    if(bb<b && (s[y+dy[useb]][x+dx[useb]]!='#') && (!passed[y+dy[useb]][x+dx[useb]][useb][aa][bb+1])){
      que.push(T(y+dy[useb],x+dx[useb],useb,aa,bb+1));
      passed[y+dy[useb]][x+dx[useb]][useb][aa][bb+1] = true;
    }
  }
  dump(que.size());
  dump(cnt);
  cout << "No" << endl;
  return 0;
}