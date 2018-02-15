// https://beta.atcoder.jp/contests/arc089/submissions/2007205
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define RREP(i, x, n) for(int i = x; i >= n; i--)
#define rrep(i, n) RREP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 2003;

int N,K,c[MAX_N][MAX_N],s[MAX_N][MAX_N];

void prepare(){
  REP(x,1,2*K+2)
    REP(y,1,2*K+2) s[x][y] = c[x][y] + s[x-1][y] + s[x][y-1] - s[x-1][y-1];
  // REP(x,1,2*K+1){
  //   REP(y,1,2*K+1) cout << c[x][y] << " ";
  //   cout << "" << endl;
  // }
}

int query(int x1,int y1,int x2,int y2){
  // return sum(x1<=x<=x2,y1<=y<=y2)
  if(x1>x2||y1>y2) return 0;
  else return s[x2][y2] - s[x1-1][y2] - s[x2][y1-1] + s[x1-1][y1-1];
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  cin >> N >> K;
  fill(c[0],c[MAX_N-1],0);
  rep(i,N){
    int x,y; char cc;
    cin >> x >> y >> cc;
    if(cc=='B') x += K;
    x %= (2*K); y %= (2*K);
    c[x+1][y+1]++;
  }
  prepare();
  int ans = -INF;
  REP(x,1,K+1) REP(y,1,K+1){
    int temp = query(x,y,x+K-1,y+K-1) + query(x+K,y+K,2*K,2*K) + query(1,1,x-1,y-1)
               + query(x+K,1,2*K,y-1) + query(1,y+K,x-1,2*K);
    ans = max(ans,max(temp,N-temp));
  }
  cout << ans << endl;
  return 0;
}
