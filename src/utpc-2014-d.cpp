#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,n,0)
#define pb push_back
#define show_table(n, k, table) rep(i,n){ rep(j,k) cout << table[i][j] << " "; cout << endl;}

using namespace std;

template<class T> inline void chmax(T& a,T const& b){a=max(a,b);}
template<class T> inline void chmin(T& a,T const& b){a=min(a,b);}

using ll = long long;
using P = pair<int,int>;
using Pl = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll lmod = 1e9+7,LINF=1LL<<60;
const int MAX_N = 1003;

int rx[3],ry[3],px[MAX_N],py[MAX_N],s[MAX_N],t[MAX_N];
bool dp[MAX_N][MAX_N];
 
bool is_ok(int x1,int y1,int x2,int y2,int d){
  return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) <= d*d;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  int N,M; cin >> M;
  rep(i,M) cin >> rx[i] >> ry[i];
  cin >> N; int i2 = 0;
  rep(i,N){
    cin >> px[i2] >> py[i2] >> s[i2] >> t[i2];
    if(i>0 && px[i2]==px[i2-1] && py[i2]==py[i2-1]) t[i2-1] = t[i2];
    else i2++;
  }
  N = i2;
  bool ans;
  if(M==1){
    ans = (N==1) && is_ok(rx[0],ry[0],px[0],py[0],s[0]);
  }else if(M==2&&N==1){
    ans = is_ok(rx[0],ry[0],px[0],py[0],s[0])||is_ok(rx[0],ry[0],px[1],py[1],s[0]);
  }else if(M==2){
    ans = false;
    rep(i,2){
      ans |= is_ok(rx[i],ry[i],px[0],py[0],s[0]) && is_ok(rx[1-i],ry[1-i],px[1],py[1],s[1]);
    }
    rep(i,N-2) ans &= is_ok(px[i],py[i],px[i+2],py[i+2],s[i+2]-t[i]);
  }else if(N==1){
    ans = false;
    rep(i,3) ans |= is_ok(rx[i],ry[i],px[0],py[0],s[0]);
  }
  if(M!=3 || N==1){
    cout << (ans ? "YES" : "NO") << endl;
    return 0;
  }
  rep(i,N) rep(j,N) dp[i][j] = false;
  vi x(N+3),y(N+3),ss(N+3),tt(N+3);
  rep(i,3) x[i] = rx[i], y[i] = ry[i];
  rep(i,N) x[i+3] = px[i], y[i+3] = py[i];
  rep(i,N) ss[i+3] = s[i], tt[i+3] = t[i];
  rep(i,3) rep(j,3) rep(k,3){
    if(i==j||j==k||k==i) continue;
    // i -> p0,  j -> p1, k -> 初期位置
    if(is_ok(x[i],y[i],x[3],y[3],ss[3])&&is_ok(x[j],y[j],x[4],y[4],ss[4])) dp[4][k] = true;
  }
  REP(i,4,N+2){
    rep(j,i-1){
      if(!dp[i][j]) continue;
      // cout << i << " " << j << endl;
      dp[i+1][j] |= is_ok(x[i-1],y[i-1],x[i+1],y[i+1],ss[i+1]-tt[i-1]);
      // cout << i+1 << " " << j << " " << is_ok(x[i-1],y[i-1],x[i+1],y[i+1],ss[i+1]-tt[i-1]) << endl;
      dp[i+1][i-1] |= is_ok(x[j],y[j],x[i+1],y[i+1],ss[i+1]-tt[j]);
      // cout << i+1 << " " << i-1 << " " << is_ok(x[j],y[j],x[i+1],y[i+1],ss[i+1]-tt[j]) << endl;
    }
  }
  ans = false;
  rep(j,N+2) ans |= dp[N+2][j];
  cout << (ans ? "YES" : "NO") << endl;
  return 0;
}