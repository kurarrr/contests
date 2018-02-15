// https://beta.atcoder.jp/contests/agc015/submissions/1990401
#include "bits/stdc++.h"

#define ALL(g) (g).begin(),(g).end()
#define REP(i, x, n) for(int i = x; i < n; i++)
#define rep(i,n) REP(i,0,n)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define pb push_back

using namespace std;

using ll = long long;
using P = pair<int,int>;

const int mod=1e9+7,INF=1<<30;
const double EPS=1e-12,PI=3.1415926535897932384626;
const ll LINF=1LL<<60, lmod = 1e9+7;

const int MAX_N = 2003;

int a[MAX_N][MAX_N],node[MAX_N][MAX_N],edgex[MAX_N][MAX_N],edgey[MAX_N][MAX_N];
string S[MAX_N];

int main(){
  int N,M,Q; cin >> N >> M >> Q ;
  fill(node[0],node[MAX_N-1],0);
  fill(edgex[0],edgex[MAX_N-1],0);
  fill(edgey[0],edgey[MAX_N-1],0);
  rep(i,N) cin >> S[i];
  rep(i,N) rep(j,M) a[i+1][j+1] = int(S[i][j]=='1');
  REP(i,1,N+1) REP(j,1,M+1) node[i][j] = a[i][j] + node[i-1][j] + node[i][j-1] - node[i-1][j-1];
  REP(i,1,N+1) REP(j,1,M+1){
    edgex[i][j] = (a[i][j]&a[i-1][j]) + edgex[i-1][j] + edgex[i][j-1] - edgex[i-1][j-1];
    edgey[i][j] = (a[i][j]&a[i][j-1]) + edgey[i-1][j] + edgey[i][j-1] - edgey[i-1][j-1];
  }
  // rep(i,N+1){
  //   rep(j,M+1) cout << edge[i][j] << " ";
  //   cout << "" << endl;
  // }
  rep(i,Q){
    int x1,y1,x2,y2;
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    int n = node[x2][y2] - node[x1-1][y2] - node[x2][y1-1] + node[x1-1][y1-1];
    int ex = edgex[x2][y2] - edgex[x1][y2] - edgex[x2][y1-1] + edgex[x1][y1-1];
    int ey = edgey[x2][y2] - edgey[x1-1][y2] - edgey[x2][y1] + edgey[x1-1][y1];
    // cout << n << " "<< ex << " " << ey << endl;
    cout << n - (ex + ey) << endl;
  }
  return 0;
}
